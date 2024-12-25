#include "common.hh"
#include "shader_opengl.hh"
#include "surface_opengl.hh"
#include "math/matrix.hh"
#include "debug/debug.hh"
#include <glad/glad.hh>

namespace Parrot {
	namespace OpenGL {
		// Shader
		Shader::Shader(const ShaderSource& source) {
			// source
			string vertex = source.vertex->toString();
			string fragment = source.fragment->toString();
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
		Shader::Shader(Shader&& other) noexcept
			: _gpu_id(std::exchange(other._gpu_id, 0)) {}
		// ~Shader
		Shader::~Shader() {
			if (_gpu_id) {
				glDeleteProgram(_gpu_id);
			}
		}
		// =
		Shader& Shader::operator=(Shader&& other) noexcept {
			_gpu_id = std::exchange(other._gpu_id, 0);
			return *this;
		}
		// bind, unbind
		void Shader::bind() const {
			glUseProgram(_gpu_id);
			LOG_GRAPHICS_TRACE("bound shader with id={}", _gpu_id);
		}
		void Shader::unbind() {
			glUseProgram(0);
			LOG_GRAPHICS_TRACE("unbound shader");
		}
		// setUniform
		// note that we need to transpose the matrix since opengl is column-major!
		// :: int32
		template<>
		void Shader::setUniform<int32>(const string& name, const int32& value) {
			glUniform1i(getUniformLocation(name), value);
		}
		template<>
		void Shader::setUniform<Vec2<int32>>(const string& name, const Vec2<int32>& value) {
			glUniform2i(getUniformLocation(name), value.x, value.y);
		}
		template<>
		void Shader::setUniform<Vec3<int32>>(const string& name, const Vec3<int32>& value) {
			glUniform3i(getUniformLocation(name), value.x, value.y, value.z);
		}
		template<>
		void Shader::setUniform<Vec4<int32>>(const string& name, const Vec4<int32>& value) {
			glUniform4i(getUniformLocation(name), value.x, value.y, value.z, value.w);
		}
		// :: uint32
		template<>
		void Shader::setUniform<uint32>(const string& name, const uint32& value) {
			glUniform1ui(getUniformLocation(name), value);
		}
		template<>
		void Shader::setUniform<Vec2<uint32>>(const string& name, const Vec2<uint32>& value) {
			glUniform2ui(getUniformLocation(name), value.x, value.y);
		}
		template<>
		void Shader::setUniform<Vec3<uint32>>(const string& name, const Vec3<uint32>& value) {
			glUniform3ui(getUniformLocation(name), value.x, value.y, value.z);
		}
		template<>
		void Shader::setUniform<Vec4<uint32>>(const string& name, const Vec4<uint32>& value) {
			glUniform4ui(getUniformLocation(name), value.x, value.y, value.z, value.w);
		}
		// :: float32
		template<>
		void Shader::setUniform<float32>(const string& name, const float32& value) {
			glUniform1f(getUniformLocation(name), value);
		}
		template<>
		void Shader::setUniform<Vec2<float32>>(const string& name, const Vec2<float32>& value) {
			glUniform2f(getUniformLocation(name), value.x, value.y);
		}
		template<>
		void Shader::setUniform<Vec3<float32>>(const string& name, const Vec3<float32>& value) {
			glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
		}
		template<>
		void Shader::setUniform<Vec4<float32>>(const string& name, const Vec4<float32>& value) {
			glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
		}
		template<>
		void Shader::setUniform<Mat<float32, 2>>(const string& name, const Mat<float32, 2>& value) {
			glUniformMatrix2fv(getUniformLocation(name), 1, GL_TRUE, value.data());
		}
		template<>
		void Shader::setUniform<Mat<float32, 3>>(const string& name, const Mat<float32, 3>& value) {
			glUniformMatrix3fv(getUniformLocation(name), 1, GL_TRUE, value.data());
		}
		template<>
		void Shader::setUniform<Mat<float32, 4>>(const string& name, const Mat<float32, 4>& value) {
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_TRUE, value.data());
		}
		// :: float64
		template<>
		void Shader::setUniform<float64>(const string& name, const float64& value) {
			glUniform1d(getUniformLocation(name), value);
		}
		template<>
		void Shader::setUniform<Vec2<float64>>(const string& name, const Vec2<float64>& value) {
			glUniform2d(getUniformLocation(name), value.x, value.y);
		}
		template<>
		void Shader::setUniform<Vec3<float64>>(const string& name, const Vec3<float64>& value) {
			glUniform3d(getUniformLocation(name), value.x, value.y, value.z);
		}
		template<>
		void Shader::setUniform<Vec4<float64>>(const string& name, const Vec4<float64>& value) {
			glUniform4d(getUniformLocation(name), value.x, value.y, value.z, value.w);
		}
		template<>
		void Shader::setUniform<Mat<float64, 2>>(const string& name, const Mat<float64, 2>& value) {
			glUniformMatrix2dv(getUniformLocation(name), 1, GL_TRUE, value.data());
		}
		template<>
		void Shader::setUniform<Mat<float64, 3>>(const string& name, const Mat<float64, 3>& value) {
			glUniformMatrix3dv(getUniformLocation(name), 1, GL_TRUE, value.data());
		}
		template<>
		void Shader::setUniform<Mat<float64, 4>>(const string& name, const Mat<float64, 4>& value) {
			glUniformMatrix4dv(getUniformLocation(name), 1, GL_TRUE, value.data());
		}
		// bindUniformBuffer
		void Shader::bindUniformBuffer(const string& name, const UniformBuffer& buffer) {
			//? warn if name not found
			uint block_index = glGetUniformBlockIndex(_gpu_id, name.c_str());
			glUniformBlockBinding(_gpu_id, block_index, buffer.getBindingPoint());
		}
		// getUniformLocation
		int32 Shader::getUniformLocation(const string& name) {
			if (!_uniform_cache.contains(name)) {
				int32 location = glGetUniformLocation(_gpu_id, name.c_str());
				if (location == -1) {
					LOG_GRAPHICS_WARNING("uniform '{}' was not found in shader", name);
				}
				_uniform_cache.emplace(name, location);
			}
			return _uniform_cache.at(name);
		}

		// (static) emphasize
		static string s_emphasize = "\033[91m";
		static string s_no_emphasize = "\033[0m";
		// split
		static List<string> split(strview str, strview delim) {
			List<string> list;
			usize offset = 0;
			while (true) {
				usize found = str.find(delim, offset);
				if (found == string::npos) {
					break;
				}
				list.emplace_back(str.substr(offset, found - offset));
				offset = found + delim.size();
			}
			return list;
		}
		// prependLineNumbers
		static string prependLineNumbers(strview str, const Set<uint>& error_lines) {
			string out;
			usize line = 1, offset = 0;
			while (str.find('\n', offset) != string::npos) {
				usize newline = str.find('\n', offset);
				if (line < 10) {
					out += "  ";
				}
				else if (line < 100) {
					out += " ";
				}
				if (error_lines.contains(line)) {
					out += s_emphasize;
				}
				out += std::to_string(line);
				out += "| ";
				if (error_lines.contains(line)) {
					out += s_no_emphasize;
				}
				out += str.substr(offset, newline - offset + 1);
				line += 1;
				offset = newline + 1;
			}
			return out;
		}
		// compileShader
		uint Shader::compileShader(const string& source, ShaderType type) {
			uint id = glCreateShader(
				type == ShaderType::VERTEX ? GL_VERTEX_SHADER : (
					type == ShaderType::FRAGMENT ? GL_FRAGMENT_SHADER : throw std::logic_error("invalid enum value")
					)
			);
			const char* source_cstr = source.c_str();
			glShaderSource(id, 1, &source_cstr, nullptr);
			glCompileShader(id);
			int32 result = 0;
			glGetShaderiv(id, GL_COMPILE_STATUS, &result);
			if (result == GL_TRUE) {
				LOG_GRAPHICS_DEBUG("successfully compiled opengl shader");
				return id;
			}
			else {
				LOG_GRAPHICS_ERROR("failed to compile opengl shader");
				int32 length = 0;
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
				char* message = new char[length];
				glGetShaderInfoLog(id, length, &length, message);
				Set<uint> error_lines;
				for (const string& line : split(message, "\n")) {
					List<string> splitted = split(line, ":");
					if (splitted.size() > 2) {
						error_lines.insert(std::stoul(splitted.at(2)));
					}
				}
				string extended_source = prependLineNumbers(source, error_lines);
				LOG_GRAPHICS_ERROR("error message:\n{}shader source code:\n{}", message, extended_source);
				delete[] message;
				glDeleteShader(id);
				return 0;
			}
		}
	}
}