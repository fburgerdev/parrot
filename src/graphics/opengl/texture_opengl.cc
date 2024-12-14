#include "common.hh"
#include "texture_opengl.hh"
#include <glad/glad.hh>

namespace Parrot {
	// TextureOpenGL / ~TextureOpenGL
	TextureOpenGL::TextureOpenGL(const Texture& texture, HandleResolver resolver) {
        // generate
        glGenTextures(1, &_gpu_id);
        glBindTexture(GL_TEXTURE_2D, _gpu_id);
        //glEnable(GL_TEXTURE_2D);
        
        //TODO: implement properties...
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // load image
        resolver.useHandle<Resource<Image>>([&](const Resource<Image>& resource) {
            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGBA,
                resource.value.getWidth(), resource.value.getHeight(), 0,
                GL_RGBA, GL_UNSIGNED_BYTE,
                resource.value.getBytes()
            );
        }, texture.image);
    }
    TextureOpenGL::TextureOpenGL(TextureOpenGL&& other) noexcept
        : _gpu_id(std::exchange(other._gpu_id, 0)) {}
    TextureOpenGL::~TextureOpenGL() {
        if (_gpu_id) {
            glDeleteTextures(1, &_gpu_id);
        }
    }
    // =
    TextureOpenGL& TextureOpenGL::operator=(TextureOpenGL&& other) noexcept {
        _gpu_id = std::exchange(other._gpu_id, 0);
        return *this;
    }
    // bind, unbind
    void TextureOpenGL::bind(uint slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, _gpu_id);
    }
    void TextureOpenGL::unbind(uint slot) {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}