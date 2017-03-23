#include "Test1.h"

namespace test1 {

	bool init();

	bool mainLoop();

	bool start() {

		//create glfw window
		logger::debug("Creating Window");
		GLFWwindow* wnd = WindowFactory::CreateWindow(1920, 1080, "FlexPhysics", false);
		if (wnd == nullptr) {
			return false;
		}

		return true;
	}


	bool init()
	{
		return false;
	}

	bool mainLoop()
	{
		return false;
	}
}