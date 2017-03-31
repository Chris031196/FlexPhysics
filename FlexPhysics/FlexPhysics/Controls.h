#pragma once
#include <glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <stdio.h>
#include "Logger.h"

namespace controls {
	
	void setWindow(GLFWwindow* wnd);
	void computeMatrices(float delta_time);
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();
	void setKeyPressedCallback(GLFWkeyfun callback);
}