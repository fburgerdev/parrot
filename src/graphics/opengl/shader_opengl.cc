#include "common.hh"
#include "shader_opengl.hh"
#include "math/matrix.hh"
#include "debug/debug.hh"
#include <glad/glad.hh>

namespace Parrot {
	// ShaderOpenGL
	ShaderOpenGL::ShaderOpenGL(const ShaderProgram& program, HandleResolver resolver) {
		// source
		string vertex;
		resolver.useHandle<Resource<Shader>>([&](const Resource<Shader>& shader) {
			vertex = shader.value.source;
		}, program.vertex);
		string fragment;
		resolver.useHandle<Resource<Shader>>([&](const Resource<Shader>& shader) {
			fragment = shader.value.source;
		}, program.fragment);
		// create + compile
		_gpu_id = glCreateProgram();
		LOG_GRAPHICS_TRACE("created shader");
		bind();
		uint32 vertex_id = compileShader(vertex, ShaderType::VERTEX);
		uint32 fragment_id = compileShader(fragment, ShaderType::FRAGMENT);
		//? what geometry shader
		glAttachShader(_gpu_id, vertex_id);
		glAttachShader(_gpu_id, fragment_id);
		glLinkProgram(_gpu_id);
		glValidateProgram(_gpu_id);
		// cleanup
		glDeleteShader(vertex_id);
		glDeleteShader(fragment_id);
		unbind();
	}
	ShaderOpenGL::ShaderOpenGL(ShaderOpenGL&& other) noexcept
		: _gpu_id(std::exchange(other._gpu_id, 0)) {}
	// ~ShaderOpenGL
	ShaderOpenGL::~ShaderOpenGL() {
		if (_gpu_id) {
			glDeleteProgram(_gpu_id);
		}
	}
	// =
	ShaderOpenGL& ShaderOpenGL::operator=(ShaderOpenGL&& other) noexcept {
		_gpu_id = std::exchange(other._gpu_id, 0);
		return *this;
	}
	// bind, unbind
	void ShaderOpenGL::bind() const {
		glUseProgram(_gpu_id);
		LOG_GRAPHICS_TRACE("bound shader with id={}", _gpu_id);
	}
	void ShaderOpenGL::unbind() {
		glUseProgram(0);
		LOG_GRAPHICS_TRACE("unbound shader");
	}
	// setUniform
	// :: int32
	template<>
	void ShaderOpenGL::setUniform<int32>(const string& name, const int32& value) {
		glUniform1i(getUniformLocation(name), value);
	}
	template<>
	void ShaderOpenGL::setUniform<Vec2<int32>>(const string& name, const Vec2<int32>& value) {
		glUniform2i(getUniformLocation(name), value.x, value.y);
	}
	template<>
	void ShaderOpenGL::setUniform<Vec3<int32>>(const string& name, const Vec3<int32>& value) {
		glUniform3i(getUniformLocation(name), value.x, value.y, value.z);
	}
	template<>
	void ShaderOpenGL::setUniform<Vec4<int32>>(const string& name, const Vec4<int32>& value) {
		glUniform4i(getUniformLocation(name), value.x, value.y, value.z, value.w);
	}
	// :: float32
	template<>
	void ShaderOpenGL::setUniform<float32>(const string& name, const float32& value) {
		glUniform1f(getUniformLocation(name), value);
	}
	template<>
	void ShaderOpenGL::setUniform<Vec2<float32>>(const string& name, const Vec2<float32>& value) {
		glUniform2f(getUniformLocation(name), value.x, value.y);
	}
	template<>
	void ShaderOpenGL::setUniform<Vec3<float32>>(const string& name, const Vec3<float32>& value) {
		glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
	}
	template<>
	void ShaderOpenGL::setUniform<Vec4<float32>>(const string& name, const Vec4<float32>& value) {
		glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
	}
	// :: matrix (note that we need to transpose the matrix since opengl is column-major!)
	template<>
	void ShaderOpenGL::setUniform<Mat<float32, 2>>(const string& name, const Mat<float32, 2>& value) {
		glUniformMatrix2fv(getUniformLocation(name), 1, GL_TRUE, value.data());
	}
	template<>
	void ShaderOpenGL::setUniform<Mat<float64, 2>>(const string& name, const Mat<float64, 2>& value) {
		glUniformMatrix2dv(getUniformLocation(name), 1, GL_TRUE, value.data());
	}
	template<>
	void ShaderOpenGL::setUniform<Mat<float32, 3>>(const string& name, const Mat<float32, 3>& value) {
		glUniformMatrix3fv(getUniformLocation(name), 1, GL_TRUE, value.data());
	}
	template<>
	void ShaderOpenGL::setUniform<Mat<float64, 3>>(const string& name, const Mat<float64, 3>& value) {
		glUniformMatrix3dv(getUniformLocation(name), 1, GL_TRUE, value.data());
	}
	template<>
	void ShaderOpenGL::setUniform<Mat<float32, 4>>(const string& name, const Mat<float32, 4>& value) {
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_TRUE, value.data());
	}
	template<>
	void ShaderOpenGL::setUniform<Mat<float64, 4>>(const string& name, const Mat<float64, 4>& value) {
		glUniformMatrix4dv(getUniformLocation(name), 1, GL_TRUE, value.data());
	}
	// getUniformLocation
	int32 ShaderOpenGL::getUniformLocation(const string& name) {
		if (!_uniform_cache.contains(name)) {
			int32 location = glGetUniformLocation(_gpu_id, name.c_str());
			if (location == -1) {
				LOG_GRAPHICS_WARNING("uniform '{}' was not found in shader", name);
			}
			_uniform_cache.emplace(name, location);
		}
		return _uniform_cache.at(name);
	}
	// compileShader
	uint ShaderOpenGL::compileShader(const string& source, ShaderType type) {
		uint id = glCreateShader(
			type == ShaderType::VERTEX ? GL_VERTEX_SHADER : (
				type == ShaderType::FRAGMENT ? GL_FRAGMENT_SHADER : throw std::logic_error("invalid enum value")
			)
		);
		const char* source_cstr = source.c_str();
		glShaderSource(id, 1, &source_cstr, nullptr);
		glCompileShader(id);
		int32 result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_TRUE) {
			LOG_GRAPHICS_DEBUG("successfully compiled opengl shader");
			return id;
		}
		else if (result == GL_FALSE) {
			LOG_GRAPHICS_ERROR("failed to compile opengl shader");
			//TODO: log error message + source
		}
		return 0;	
	}
}