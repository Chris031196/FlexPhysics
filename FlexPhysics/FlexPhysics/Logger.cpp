#include "Logger.h"

namespace Logger {

	void clear(const char* title) {
		FILE* file = fopen(Logger::filepath, "w");
		fprintf(file, "");
	}
}