#include "WindowFactory.h"

namespace WindowFactory {
	GLFWwindow * CreateWindow(int width, int height, char * name, bool fullscreen)
	{
		//initialize glfw
		logger::debug("Initializing GLFW...");
		if (!glfwInit()) {
			logger::error("Failed to initialize GLFW!");
			return nullptr;
		}

		//set glfw options
		glfwWindowHint(GLFW_SAMPLES, 4); //Antialiasing 4x
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Version 3.3
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //for macs
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // choose gl core profile
		logger::debug("GLFW initialization successful!");

		//create window
		GLFWwindow* wnd;
		if (fullscreen)
			wnd = glfwCreateWindow(width, height, name, glfwGetPrimaryMonitor(), NULL);
		else
			wnd = glfwCreateWindow(width, height, name, NULL, NULL);

		//check if creation was successful
		logger::debug("Checking window creation...");
		if (wnd == NULL) {
			logger::error("Failed to create window!");
			glfwTerminate();
			return nullptr;
		}
		glfwMakeContextCurrent(wnd);
		logger::debug("Window creation successful!");

		//Init GLEW
		glewExperimental = true;
		if (glewInit() != GLEW_OK) {
			fprintf(stderr, "Failed to Init GLEW!");
			getchar();
			glfwTerminate();
			return nullptr;
		}

		return wnd;
	}
}
