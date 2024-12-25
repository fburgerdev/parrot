#pragma once
#include "common.hh"

namespace Parrot {
	// ShaderBuilder
	class ShaderBuilder {
	public:
		// ShaderBuilder
		ShaderBuilder(const stdf::path& filepath);
		ShaderBuilder(const string& source);

		// ShaderType
		enum class ShaderType {
			VERTEX, FRAGMENT
		};
		// ShaderStage
		struct ShaderStage {
			// <=>
			auto operator<=>(const ShaderStage&) const = default;

			// type, version
			ShaderType type;
			string version = "330 core";
		};
		// SnippetHead
		using SnippetHead = Variant<ShaderStage, string>;
		// SnippetInclude
		struct SnippetInclude {
			// identifier, is_optional
			string identifier;
			bool is_optional = false;
		};
		// SnippetBody
		struct SnippetBody {
			// toString
			string toString() const {
				string out;
				for (const auto& part : parts) {
					if (std::holds_alternative<SnippetInclude>(part)) {
						const SnippetInclude& include = std::get<SnippetInclude>(part);
						if (include.is_optional) {
							out += "[[include \"" + include.identifier + "\" optional]]";
						}
						else {
							out += "[[include \"" + include.identifier + "\"]]";
						}
					}
					else {
						out += std::get<string>(part);
					}
				}
				return out;
			}

			// parts
			List<Variant<SnippetInclude, string>> parts;
		};

		// createVertexSource
		string createVertexSource() const {
			for (auto& [head, body] : snippets) {
				if (std::holds_alternative<ShaderStage>(head)) {
					if (std::get<ShaderStage>(head).type == ShaderType::VERTEX) {
						string source = "#version " + std::get<ShaderStage>(head).version;
						source += body.toString();
						return source;
					}
				}
			}
			return {};
		}
		// createFragmentSource
		string createFragmentSource() const {
			for (auto& [head, body] : snippets) {
				if (std::holds_alternative<ShaderStage>(head)) {
					if (std::get<ShaderStage>(head).type == ShaderType::FRAGMENT) {
						string source = "#version " + std::get<ShaderStage>(head).version;
						source += body.toString();
						return source;
					}
				}
			}
			return {};
		}

		// (static) resolve
		void resolve(auto&& builders) {
			Set<ShaderBuilder*> resolved;
			for (auto& [head, body] : snippets) {
				for (usize i = 0; i < body.parts.size(); ++i) {
					if (std::holds_alternative<SnippetInclude>(body.parts.at(i))) {
						SnippetInclude& include = std::get<SnippetInclude>(body.parts.at(i));
						bool found = false;
						for (ShaderBuilder& builder : builders) {
							if (this == &builder) {
								continue;
							}
							if (builder.snippets.contains(include.identifier)) {
								if (!resolved.contains(&builder)) {
									builder.resolve(builders);
									resolved.insert(&builder);
								}
								body.parts.at(i) = builder.snippets.at(include.identifier).toString();
								found = true;
								break;
							}
						}
						if (!found) {
							if (include.is_optional) {
								body.parts.at(i) = string();
							}
							else {
								//TODO: error
							}
						}
					}
				}
			}
		}

		// snippets
		Map<SnippetHead, SnippetBody> snippets;
	};
}