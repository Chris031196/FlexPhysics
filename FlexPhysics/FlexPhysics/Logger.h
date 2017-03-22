#pragma once

#include <fstream>
#include <string>

namespace Logger {
	enum Level {ERROR = 0, INFO = 1, DEBUG = 2};
	static Level log_level = Level::ERROR;
	static char* filepath = "Log.txt";

	template<class... Args>
	void error(const char* format, Args&&... args) {
		std::string s = std::string("[ERROR]: ") + format + '\n';
		fprintf(stderr, s.c_str(), std::forward<Args>(args)...);

		FILE* file = fopen(filepath, "a");
		fprintf(file, s.c_str(), std::forward<Args>(args)...);
	}

	template<class... Args>
	void info(const char* format, Args&&... args) {
		if (log_level >= INFO) {
			std::string s = std::string("[INFO]: ") + format + '\n';
			printf(s.c_str(), std::forward<Args>(args)...);

			FILE* file = fopen(filepath, "a");
			fprintf(file, s.c_str(), std::forward<Args>(args)...);
		}
	}

	template<class... Args>
	void debug(const char* format, Args&&... args) {
		if (log_level >= DEBUG) {
			std::string s = std::string("[DEBUG]: ") + format + '\n';
			printf(s.c_str(), std::forward<Args>(args)...);

			FILE* file = fopen(filepath, "a");
			fprintf(file, s.c_str(), std::forward<Args>(args)...);
		}
	}

	void clear(const char* title);
}