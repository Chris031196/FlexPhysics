#include "glew.h"
#include "glfw3.h"
#include "WindowFactory.h"

int main(int argc, char* argv[])
{
	//set Log level
	Logger::clear("Logfile");
	if (argc > 0) {
		switch ('d') {
		case 'e': Logger::log_level = Logger::ERROR; break;
		case 'i': Logger::log_level = Logger::INFO; break;
		case 'd': Logger::log_level = Logger::DEBUG; break;
		}
	}
	//create glfw window
	Logger::debug("Creating Window");
	GLFWwindow* wnd = WindowFactory::CreateWindow(1920, 1080, "FlexPhysics", false);

	getchar();
	return 0;
}