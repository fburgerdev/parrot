#pragma once
#include "graphics/shader.hh"
#include "uniform_buffer_opengl.hh"

namespace Parrot {
	namespace OpenGL {
		// ShaderType
		enum class ShaderType {
			VERTEX, FRAGMENT
		};
		// ShaderOpenGL
		class ShaderOpenGL {
		public:
			// ShaderOpenGL / ~ShaderOpenGL
			ShaderOpenGL(const ShaderProgram& program, HandleResolver resolver);
			ShaderOpenGL(const ShaderOpenGL&) = delete;
			ShaderOpenGL(ShaderOpenGL&& other) noexcept;
			~ShaderOpenGL();
			// =
			ShaderOpenGL& operator=(const ShaderOpenGL&) = delete;
			ShaderOpenGL& operator=(ShaderOpenGL&& other) noexcept;

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