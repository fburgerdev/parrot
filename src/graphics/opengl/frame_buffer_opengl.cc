#include "common.hh"
#include "frame_buffer_opengl.hh"
#include "core/log.hh"
#include <glad/glad.hh>

namespace Parrot {
	namespace OpenGL {
    // (constructor)
    FrameBuffer::FrameBuffer(uint width, uint height)
      : _texture(width, height) {
      // create
      glGenFramebuffers(1, &_gpu_id);
      LOG_GRAPHICS_TRACE("created frame-buffer with id={}", _gpu_id);
      
      bind();
      // color
      glFramebufferTexture2D(
        GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D, _texture._gpu_id, 0
      );
      // depth and stencil
      glGenRenderbuffers(1, &_depth_stencil_id);
      glBindRenderbuffer(GL_RENDERBUFFER, _depth_stencil_id);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
      glBindRenderbuffer(GL_RENDERBUFFER, 0);
      glFramebufferRenderbuffer(
        GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
        GL_RENDERBUFFER, _depth_stencil_id
      );

      // status
      auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
      if (status != GL_FRAMEBUFFER_COMPLETE) {
        LOG_GRAPHICS_ERROR(
          "construction of frame-buffer with id={} is incomplete", _gpu_id
        );
      }
      unbind();
    }
    FrameBuffer::FrameBuffer(FrameBuffer&& other) noexcept
      : _gpu_id(std::exchange(other._gpu_id, 0)),
      _depth_stencil_id(std::exchange(other._depth_stencil_id, 0)),
      _texture(std::move(other._texture)) {}
    // (destructor)
    FrameBuffer::~FrameBuffer() {
      if (_gpu_id) {
        glDeleteFramebuffers(1, &_gpu_id);
      }
      if (_depth_stencil_id) {
        glDeleteRenderbuffers(1, &_depth_stencil_id);
      }
    }
    // (assignment)
    FrameBuffer& FrameBuffer::operator=(FrameBuffer&& other) noexcept {
      _gpu_id = std::exchange(other._gpu_id, 0);
      _depth_stencil_id = std::exchange(other._depth_stencil_id, 0);
      _texture = std::move(other._texture);
      return *this;
    }
    // getTexture
    const Texture& FrameBuffer::getTexture() const {
      return _texture;
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