#include "Test1.h"

int main(int argc, char* argv[])
{
	//set Log level
	logger::clear("Logfile");
	if (argc > 0) {
		switch ('d') {
		case 'e': logger::log_level = logger::ERROR; break;
		case 'i': logger::log_level = logger::INFO; break;
		case 'd': logger::log_level = logger::DEBUG; break;
		}
	}

	return test1::start();
}