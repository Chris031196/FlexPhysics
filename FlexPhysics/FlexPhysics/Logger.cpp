#include "Logger.h"

namespace logger {

	void clear(const char* title) {
		FILE* file = fopen(logger::filepath, "w");
		fprintf(file, "");
	}
}