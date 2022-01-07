#include "mrlog.hpp"

namespace mrlog {

	namespace Detail {

	std::string logfile = "mrlog.log";

	std::string generateDate() {
		char buffer[100];
		time_t rawtime;
		time(&rawtime);
		struct tm* timeinfo = gmtime(&rawtime);
		strftime(buffer, sizeof(buffer), "%FT%T%z", timeinfo);
		return std::string(buffer);
	}

	const char* parseFormat(const char* format) {
		while (*format != '}') {
			if (*format == '\0') {
				throw std::runtime_error("mrlog: expected '}'");
			}
			++format;
		}
		return format;
	}

	}

	void clearLog() {
		std::ofstream(Detail::logfile, std::ios_base::trunc);
	}

	void setLogFile(std::string&& file) {
		Detail::logfile = std::forward<std::string>(file);
	}

}
