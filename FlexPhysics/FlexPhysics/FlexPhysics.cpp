#include "Test2.h"

int main(int argc, char* argv[])
{
	//set Log level
	logger::clear("Logfile");
	logger::log_level = logger::DEBUG;

	return test2::start();
}