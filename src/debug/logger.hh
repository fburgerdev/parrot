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
		void logTrace(strview scope, const TArgs&... args) {
			log(scope, LogLevel::TRACE, args...);
		}
		// logDebug
		template<class... TArgs>
		void logDebug(strview scope, const TArgs&... args) {
			log(scope, LogLevel::DEBUG, args...);
		}
		// logInfo
		template<class... TArgs>
		void logInfo(strview scope, const TArgs&... args) {
			log(scope, LogLevel::INFO, args...);
		}
		// logWarning
		template<class... TArgs>
		void logWarning(strview scope, const TArgs&... args) {
			log(scope, LogLevel::WARNING, args...);
		}
		// logError
		template<class... TArgs>
		void logError(strview scope, const TArgs&... args) {
			log(scope, LogLevel::ERROR, args...);
		}

		// getLevel
		LogLevel getLevel() const;
		LogLevel getLevel(strview scope) const;
		// setLevel
		void setLevel(LogLevel level);
		void setLevel(strview scope, LogLevel level);
	private:
		void logHead(strview scope, LogLevel level);
		template<class... TArgs>
		void log(strview scope, LogLevel level, const TArgs&... args) {
			if (uint(level) >= uint(getLevel(scope))) {
				logHead(scope, level);
				(cout << ... << args) << endl;
			}
		}

		string _name;
		Map<string, LogLevel> _levels;
	};
}