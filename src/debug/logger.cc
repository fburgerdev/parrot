#include "common.hh"
#include "logger.hh"

namespace Parrot {
	// (static) color codes
	static string s_white_code = "\033[0m";
	static string s_blue_code = "\033[34m";
	static string s_green_code = "\033[32m";
	static string s_yellow_code = "\033[33m";
	static string s_red_code = "\033[31m";
	// (static) mappings
	static Map<LogLevel, strview> s_color_map = {
		{ LogLevel::TRACE, s_white_code },
		{ LogLevel::DEBUG, s_blue_code },
		{ LogLevel::INFO, s_green_code },
		{ LogLevel::WARNING, s_yellow_code },
		{ LogLevel::ERROR, s_red_code }
	};
	static Map<LogLevel, string> s_tag_map = {
		{ LogLevel::TRACE, "Trace" },
		{ LogLevel::DEBUG, "Debug" },
		{ LogLevel::INFO, "Info" },
		{ LogLevel::WARNING, "Warning" },
		{ LogLevel::ERROR, "Error" }
	};

	// Logger
	Logger::Logger(strview name)
		: _name(name) {}

	// level
	// :: get
	LogLevel Logger::getLevel() const {
		return getLevel(strview());
	}
	LogLevel Logger::getLevel(strview scope) const {
		strview longest_scope = strview();
		LogLevel level = LogLevel::TRACE;
		for (const auto& [other_scope, other_level] : _levels) {
			if (scope.starts_with(other_scope)) {
				if (other_scope.empty() || other_scope.length() == scope.length() || scope.at(other_scope.length()) == '/') {
					if (longest_scope.length() <= other_scope.length()) {
						longest_scope = other_scope;
						level = other_level;
					}
				}
			}
		}
		return level;
	}
	// :: set
	void Logger::setLevel(LogLevel level) {
		setLevel(strview(), level);
	}
	void Logger::setLevel(strview scope, LogLevel level) {
		for (auto it = _levels.begin(); it != _levels.end();) {
			if (it->first.starts_with(scope)) {
				it = _levels.erase(it);
			}
			else {
				++it;
			}
		}
		_levels.emplace(scope, level);
	}

	// log
	// :: head
	void Logger::logHead(strview scope, LogLevel level) {
		cout << s_color_map.at(level);
		cout << '[' << s_tag_map.at(level) << ']';
		cout << " in ";
		if (scope.empty()) {
			cout << _name;
		}
		else {
			cout << _name << '/' << scope;
		}
		cout << s_white_code << "\n";
	}
	// :: body
	void Logger::logBody(strview format) {
		cout << format << endl;
	}
}