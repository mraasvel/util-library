#include "util.hpp"
#include <vector>
#include <string>
#include <dirent.h>

namespace util {

	namespace __detail__ {

	static bool isSpecialDirectory(const std::string& dirname) {
		return dirname.find("/..") == dirname.size() - 3 ||
			dirname.find("/.") == dirname.size() - 2;
	}
	
	static int iterateDirectory(const std::string& dirname, std::vector<std::string>& files) {
		DIR* dir = opendir(dirname.c_str());
		if (!dir) {
			return -1;
		}
		std::vector<std::string> directories;
		while (struct dirent* ent = readdir(dir)) {
			const std::string filename = dirname + ent->d_name;
			if (isSpecialDirectory(filename)) {
				continue;
			}
			if (util::isDirectory(filename)) {
				directories.push_back(filename + "/");
			}
			files.push_back(filename);
		}
		closedir(dir);
		for (std::vector<std::string>::const_iterator it = directories.begin(); it != directories.end(); it++) {
			iterateDirectory(*it, files);
		}
		return 0;
	}

	}

std::vector<std::string> directorySearch(const std::string& dirname) {
	if (dirname.empty()) {
		return {};
	}
	std::vector<std::string> files;
	files.push_back(dirname);
	if (dirname.back() == '/') {
		__detail__::iterateDirectory(dirname, files);
	} else {
		__detail__::iterateDirectory(dirname + "/", files);
	}
	return files;
}

}
