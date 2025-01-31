#pragma once
#include "common.hh"

namespace Parrot {
	// LogLevel
	enum class LogLevel {
		TRACE, DEBUG, INFO, WARNING, ERROR
	};
	// Logger
	class Logger {
	public:
		// (constructor)
		Logger(strview name);

		// log
		template<LogLevel Level, class... TArgs>
		void log(strview scope, strview format, const TArgs&... args) {
			if (uint(Level) >= uint(getLevel(scope))) {
				logHead(scope, Level);
				logBody(format, args...);
			}
		}
		// :: trace
		template<class... TArgs>
		void logTrace(strview scope, strview format, const TArgs&... args) {
			log<LogLevel::TRACE>(scope, format, args...);
		}
		// :: debug
		template<class... TArgs>
		void logDebug(strview scope, strview format, const TArgs&... args) {
			log<LogLevel::DEBUG>(scope, format, args...);
		}
		// :: info
		template<class... TArgs>
		void logInfo(strview scope, strview format, const TArgs&... args) {
			log<LogLevel::INFO>(scope, format, args...);
		}
		// :: warning
		template<class... TArgs>
		void logWarning(strview scope, strview format, const TArgs&... args) {
			log<LogLevel::WARNING>(scope, format, args...);
		}
		// :: error
		template<class... TArgs>
		void logError(strview scope, strview format, const TArgs&... args) {
			log<LogLevel::ERROR>(scope, format, args...);
		}

		// level
		// :: get
		LogLevel getLevel() const;
		LogLevel getLevel(strview scope) const;
		// :: set
		void setLevel(LogLevel level);
		void setLevel(strview scope, LogLevel level);
	private:
		void logHead(strview scope, LogLevel level);
		void logBody(strview format);
		template<class TFirst, class... TRest>
		void logBody(strview format, const TFirst& first, const TRest&... rest) {
			for (auto it = format.begin(); it != format.end(); ++it) {
				if (std::next(it) != format.end()) {
					if (*it == '{' && *std::next(it) == '}') {
						cout << first;
						return logBody(strview(std::next(it, 2), format.end()), rest...);
					}
				}
				cout << *it;
			}
		}

		string _name;
		Map<string, LogLevel> _levels;
	};
}