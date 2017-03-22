#include "WindowFactory.h"

namespace WindowFactory {
	GLFWwindow * CreateWindow(int width, int height, char * name, bool fullscreen)
	{
		//initialize glfw
		Logger::debug("Initializing GLFW...");
		if (!glfwInit()) {
			Logger::error("Failed to initialize GLFW!");
			return nullptr;
		}

		//set glfw options
		glfwWindowHint(GLFW_SAMPLES, 4); //Antialiasing 4x
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Version 3.3
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //for macs
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // choose gl core profile
		Logger::debug("GLFW initialization successful!");

		//create window
		GLFWwindow* wnd;
		if (fullscreen)
			wnd = glfwCreateWindow(width, height, name, glfwGetPrimaryMonitor(), NULL);
		else
			wnd = glfwCreateWindow(width, height, name, NULL, NULL);

		//check if creation was successful
		Logger::debug("Checking window creation...");
		if (wnd == NULL) {
			Logger::error("Failed to create window!");
			glfwTerminate();
			return nullptr;
		}
		Logger::debug("Window creation successful!");

		return wnd;
	}
}
