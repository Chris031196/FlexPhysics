#pragma once

#include "glew.h"
#include "glfw3.h"
#include "Logger.h"

namespace WindowFactory
{
	/*
	*	creates a GLFW window with the specified parameters
	*
	*	returns the created window or nullptr if creation failed
	*/
	GLFWwindow* CreateWindow(int width, int height, char* name, bool fullscreen);
};

