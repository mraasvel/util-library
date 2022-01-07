#include "mrlog.hpp"

namespace mrlog {

	namespace Detail {

	void processFormat(const char* format) {
		std::cout << format;
	}

	void log(LogLevel level, const char* s) {
		static const std::string levels[] = {
			"OFF",
			"FATAL",
			"ERROR",
			"WARN",
			"INFO",
			"DEBUG"
		};

		if (level != LogLevel::OFF) {
			std::cout << "[" << levels[static_cast<uint16_t>(level)] << "] " << std::endl;
		}

		processFormat(s);
	}

	}


}
