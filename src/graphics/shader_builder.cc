#include "common.hh"
#include "shader_builder.hh"

namespace Parrot {
	// (static) split
	static List<string> split(strview str, const List<char>& delim) {
		List<string> out = { "" };
		for (char ch : str) {
			if (std::find(delim.begin(), delim.end(), ch) != delim.end()) {
				if (!out.back().empty()) {
					out.emplace_back();
				}
			}
			else {
				out.back().push_back(ch);
			}
		}
		if (out.back().empty()) {
			out.pop_back();
		}
		return out;
	}
	// (static) join
	static string join(strview delim, auto begin, auto end) {
		string out;
		for (auto it = begin; it != end; ++it) {
			out += *it;
			if (std::next(it) != end) {
				out += delim;
			}
		}
		return out;
	}

	// ShaderBuilder
	ShaderBuilder::ShaderBuilder(const stdf::path& filepath)
		: ShaderBuilder((ostrstream() << ifstream(filepath).rdbuf()).str()) {}
	ShaderBuilder::ShaderBuilder(const string& source) {
		usize offset = 0;
		Opt<SnippetHead> current_head = std::nullopt;
		SnippetBody current_body = {};
		while (true) {
			usize open_index = source.find("[[", offset);
			usize close_index = source.find("]]", offset);
			if (open_index == string::npos || close_index == string::npos) {
				break;
			}
			string inner = source.substr((open_index + 2), close_index - (open_index + 2));
			List<string> splitted = split(inner, { ' ', '(', ')', '"' });
			if (splitted.size()) {
				if (splitted.front() == "vertex" || splitted.front() == "fragment") {
					string version = join(" ", splitted.begin() + 1, splitted.end());
					if (splitted.front() == "vertex") {
						current_head = ShaderStage({ ShaderType::VERTEX, version });
					}
					else {
						current_head = ShaderStage({ ShaderType::FRAGMENT, version });
					}
				}
				else if (splitted.front() == "snippet") {
					current_head = splitted.at(1);
				}
				else if (splitted.front() == "include") {
					string identifier = splitted.at(1);
					current_body.parts.emplace_back(source.substr(offset, open_index - offset));
					if (splitted.back() == "optional") {
						current_body.parts.emplace_back(SnippetInclude({ identifier, true }));
					}
					else {
						current_body.parts.emplace_back(SnippetInclude({ identifier, false }));
					}
				}
				else if (splitted.front() == "end") {
					current_body.parts.emplace_back(source.substr(offset, open_index - offset));
					snippets.emplace(std::move(*current_head), std::move(current_body));
					current_head = std::nullopt;
				}
			}
			offset = close_index + 2;
		}
	}
}