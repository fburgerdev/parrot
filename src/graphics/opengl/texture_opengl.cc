#include "common.hh"
#include "texture_opengl.hh"
#include <glad/glad.hh>

namespace Parrot {
    namespace OpenGL {
        // Texture / ~Texture
        Texture::Texture(const TextureConfig& config, HandleResolver resolver) {
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
            resolver.useHandle<Image>([&](const Image& image) {
                glTexImage2D(
                    GL_TEXTURE_2D, 0, GL_RGBA,
                    image.getWidth(), image.getHeight(), 0,
                    GL_RGBA, GL_UNSIGNED_BYTE,
                    image.getBytes()
                );
            }, config.image);
        }
        Texture::Texture(Texture&& other) noexcept
            : _gpu_id(std::exchange(other._gpu_id, 0)) {}
        Texture::~Texture() {
            if (_gpu_id) {
                glDeleteTextures(1, &_gpu_id);
            }
        }
        // =
        Texture& Texture::operator=(Texture&& other) noexcept {
            _gpu_id = std::exchange(other._gpu_id, 0);
            return *this;
        }
        // bind, unbind
        void Texture::bind(uint slot) const {
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, _gpu_id);
        }
        void Texture::unbind(uint slot) {
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}