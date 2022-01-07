#ifndef MRLOG_HPP
#define MRLOG_HPP

#include <iostream>

namespace mrlog {

enum class LogLevel : uint16_t {
	OFF,
	FATAL,
	ERROR,
	WARN,
	INFO,
	DEBUG
};

	namespace Detail {

	void processFormat(const char* format);

	template<typename T, typename... Args>
	void processFormat(const char* format, const T& value, Args&&...args) {
		while (*format != '\0') {
			if (*format == '{') {
				while (*format != '}') {
					if (*format == '\0') {
						throw std::runtime_error("mrlog: expected '}'");
					}
					++format;
				}
				std::cout << value;
				processFormat(format + 1, std::forward<Args>(args)...);
				return;
			} else {
				std::cout << *format++;
			}
		}
	}

	void log(LogLevel level, const char* s);
	template <typename T, typename... Args>
	void log(LogLevel level, const char* format, const T& value, Args&&...args) {
		log(level, "");
		processFormat(format, value, std::forward<Args>(args)...);
	}

	}

template <typename... Args>
void log(const char* format, Args&&...args) {
	Detail::log(LogLevel::OFF, format, std::forward<Args>(args)...);
}

template <typename... Args>
void fatal(const char* format, Args&&...args) {
	Detail::log(LogLevel::FATAL, format, std::forward<Args>(args)...);
}

template <typename... Args>
void error(const char* format, Args&&...args) {
	Detail::log(LogLevel::ERROR, format, std::forward<Args>(args)...);
}

template <typename... Args>
void warn(const char* format, Args&&...args) {
	Detail::log(LogLevel::WARN, format, std::forward<Args>(args)...);
}

template <typename... Args>
void info(const char* format, Args&&...args) {
	Detail::log(LogLevel::INFO, format, std::forward<Args>(args)...);
}

template <typename... Args>
void debug(const char* format, Args&&...args) {
	Detail::log(LogLevel::DEBUG, format, std::forward<Args>(args)...);
}

};

#endif /* MRLOG_HPP */
