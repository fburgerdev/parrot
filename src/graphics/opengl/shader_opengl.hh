#pragma once
#include "graphics/shader_source.hh"
#include "uniform_buffer_opengl.hh"

namespace Parrot {
  namespace OpenGL {
    enum class ShaderType {
      VERTEX, FRAGMENT
    };
    class Shader {
    public:
      Shader(const ShaderProgram& program);
      Shader(const Shader&) = delete;
      Shader(Shader&& other) noexcept;
      ~Shader();
      Shader& operator=(const Shader&) = delete;
      Shader& operator=(Shader&& other) noexcept;

      template<class T>
      void setUniform(const string& name, const T& value);
      void bindUniformBuffer(const string& name, const UniformBuffer& buffer);

      void bind() const;
      static void unbind();
    private:
      static uint compileShader(const string& source, ShaderType type);
      int32 getUniformLocation(const string& name);

      uint _gpu_id = 0;
      Map<string, int32> _uniform_cache;
    };
  }
}