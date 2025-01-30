#pragma once
#include "core/asset_handle.hh"

namespace Parrot {
	// ShaderSource (Asset)
	class ShaderSource : public Asset {
	public:
		// (constructor) for Asset
		ShaderSource() = default;
		ShaderSource(const AssetPath& asset_path, AssetLocker& locker);
		ShaderSource(const string& source);
		template<JsonType JSON>
		ShaderSource(
			const JSON& json, const AssetPath& asset_path, AssetLocker& locker
		) : Asset(asset_path) {}

		// SnippetInclude
		struct SnippetInclude {
			// identifier, is_optional
			string identifier;
			bool is_optional = false;
		};
		// Snippet
		struct Snippet {
			// toString
			string toString() const {
				string out;
				for (const auto& part : body) {
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

			// name, body
			string name;
			List<Variant<SnippetInclude, string>> body;
		};
		// ShaderStage
		struct ShaderStage : public Snippet {
			// Type
			enum class Type {
				VERTEX, FRAGMENT
			};

			// toString
			string toString() const {
				return "#version " + version + Snippet::toString();
			}

			// type, version
			Type type;
			string version = "330 core";
		};

		// (static) resolve
		void resolve(auto&& sources) {
			if (vertex) {
				resolve(*vertex, sources);
			}
			if (fragment) {
				resolve(*fragment, sources);
			}
			for (auto& [name, snippet] : snippets) {
				resolve(snippet, sources);
			}
		}
		void resolve(Snippet& snippet, auto&& sources) {
			Set<ShaderSource*> resolved;
			for (usize i = 0; i < snippet.body.size(); ++i) {
				if (std::holds_alternative<SnippetInclude>(snippet.body.at(i))) {
					SnippetInclude& include = std::get<SnippetInclude>(snippet.body.at(i));
					bool found = false;
					for (ShaderSource& other : sources) {
						if (this == &other) {
							continue;
						}
						if (other.snippets.contains(include.identifier)) {
							if (!resolved.contains(&other)) {
								other.resolve(sources);
								resolved.insert(&other);
							}
							snippet.body.at(i) = other.snippets.at(include.identifier).toString();
							found = true;
							break;
						}
					}
					if (!found) {
						if (include.is_optional) {
							snippet.body.at(i) = string();
						}
						else {
							//TODO: error
						}
					}
				}
			}
		}

		// vertex, fragment, snippets
		Opt<ShaderStage> vertex, fragment;
		Map<string, Snippet> snippets;
	};
}