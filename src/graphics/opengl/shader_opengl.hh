#pragma once
#include "graphics/shader_source.hh"
#include "uniform_buffer_opengl.hh"

namespace Parrot {
	namespace OpenGL {
		// ShaderType
		enum class ShaderType {
			VERTEX, FRAGMENT
		};
		// Shader
		class Shader {
		public:
			// (constructor)
			Shader(const ShaderSource& source);
			Shader(const Shader&) = delete;
			Shader(Shader&& other) noexcept;
      // (destructor)
			~Shader();
			// (assignment)
			Shader& operator=(const Shader&) = delete;
			Shader& operator=(Shader&& other) noexcept;

			// setUniform
			template<class T>
			void setUniform(const string& name, const T& value);
			// bindUniformBuffer
			void bindUniformBuffer(const string& name, const UniformBuffer& buffer);

			// bind, unbind
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