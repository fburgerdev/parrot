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
		// Logger
		Logger(strview name);

		// logTrace
		template<class... TArgs>
		void logTrace(strview scope, strview format, const TArgs&... args) {
			if (uint(LogLevel::TRACE) >= uint(getLevel(scope))) {
				logHead(scope, LogLevel::TRACE);
				log(format, args...);
			}
		}
		// logDebug
		template<class... TArgs>
		void logDebug(strview scope, strview format, const TArgs&... args) {
			if (uint(LogLevel::DEBUG) >= uint(getLevel(scope))) {
				logHead(scope, LogLevel::DEBUG);
				log(format, args...);
			}
		}
		// logInfo
		template<class... TArgs>
		void logInfo(strview scope, strview format, const TArgs&... args) {
			if (uint(LogLevel::INFO) >= uint(getLevel(scope))) {
				logHead(scope, LogLevel::INFO);
				log(format, args...);
			}
		}
		// logWarning
		template<class... TArgs>
		void logWarning(strview scope, strview format, const TArgs&... args) {
			if (uint(LogLevel::WARNING) >= uint(getLevel(scope))) {
				logHead(scope, LogLevel::WARNING);
				log(format, args...);
			}
		}
		// logError
		template<class... TArgs>
		void logError(strview scope, strview format, const TArgs&... args) {
			if (uint(LogLevel::ERROR) >= uint(getLevel(scope))) {
				logHead(scope, LogLevel::ERROR);
				log(format, args...);
			}
		}

		// getLevel
		LogLevel getLevel() const;
		LogLevel getLevel(strview scope) const;
		// setLevel
		void setLevel(LogLevel level);
		void setLevel(strview scope, LogLevel level);
	private:
		void logHead(strview scope, LogLevel level);
		void log(strview format);
		template<class TFirst, class... TRest>
		void log(strview format, const TFirst& first, const TRest&... rest) {
			for (auto it = format.begin(); it != format.end(); ++it) {
				if (std::next(it) != format.end()) {
					if (*it == '{' && *std::next(it) == '}') {
						cout << first;
						return log(strview(std::next(it, 2), format.end()), rest...);
					}
				}
				cout << *it;
			}
		}

		string _name;
		Map<string, LogLevel> _levels;
	};
}