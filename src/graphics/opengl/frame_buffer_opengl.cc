#include "common.hh"
#include "frame_buffer_opengl.hh"
#include "core/log.hh"
#include <glad/glad.hh>

namespace Parrot {
	namespace OpenGL {
    // (constructor)
    FrameBuffer::FrameBuffer(uint width, uint height)
      : _texture(width, height, TextureFormat::RGBA),
        _depth(width, height, TextureFormat::DEPTH) {
      // create
      glGenFramebuffers(1, &_gpu_id);
      LOG_GRAPHICS_TRACE("created frame-buffer with id={}", _gpu_id);
      
      bind();
      // color
      glFramebufferTexture2D(
        GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D, _texture._gpu_id, 0
      );
      // depth
      glFramebufferTexture2D(
        GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
        GL_TEXTURE_2D, _depth._gpu_id, 0
      );

      // status
      auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
      if (status != GL_FRAMEBUFFER_COMPLETE) {
        LOG_GRAPHICS_ERROR(
          "construction of frame-buffer with id={} is incomplete, "
          "opengl error {}",
          _gpu_id, status
        );
      }
      unbind();
    }
    FrameBuffer::FrameBuffer(FrameBuffer&& other) noexcept
      : _gpu_id(std::exchange(other._gpu_id, 0)),
      _texture(std::move(other._texture)),
      _depth(std::move(other._depth)) {}
    // (destructor)
    FrameBuffer::~FrameBuffer() {
      if (_gpu_id) {
        glDeleteFramebuffers(1, &_gpu_id);
      }
    }
    // (assignment)
    FrameBuffer& FrameBuffer::operator=(FrameBuffer&& other) noexcept {
      _gpu_id = std::exchange(other._gpu_id, 0);
      _texture = std::move(other._texture);
      _depth = std::move(other._depth);
      return *this;
    }
    
    // getTexture
    const Texture& FrameBuffer::getTexture() const {
      return _texture;
    }
    // getDepthTexture
    const Texture& FrameBuffer::getDepthTexture() const {
      return _depth;
    }

    // bind / unbind
    void FrameBuffer::bind() const {
      glBindFramebuffer(GL_FRAMEBUFFER, _gpu_id);
      LOG_GRAPHICS_TRACE("bound frame-buffer with id={}", _gpu_id);
    }
    void FrameBuffer::unbind() {
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      LOG_GRAPHICS_TRACE("unbound frame-buffer");
    }
	}
}