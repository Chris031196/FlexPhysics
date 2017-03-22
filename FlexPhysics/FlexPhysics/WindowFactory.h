#pragma once

#include "glfw3.h"
#include "Logger.h"

namespace WindowFactory
{
	GLFWwindow* CreateWindow(int width, int height, char* name, bool fullscreen);
};

