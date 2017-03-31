#include "Controls.h"

namespace controls {
	glm::mat4 proMat;
	glm::mat4 viewMat;

	glm::vec3 position = glm::vec3(0, 0, -5);
	float horizontalAngle = glm::radians(0.0f);
	float verticalAngle = 0.0f;
	float initialFov = glm::radians(75.0f);
	float speedN = 1.0f;
	float mouseSpeed = 0.05f;
	GLFWwindow* window;

	void computeMatrices(float delta_time)
	{
		int width, height;
		glfwGetWindowSize(window, &width, &height);

		double mX, mY;
		glfwGetCursorPos(window, &mX, &mY);
		glfwSetCursorPos(window, width / 2.0, height / 2.0);

		horizontalAngle += mouseSpeed * delta_time * float(width / 2.0 - mX);
		verticalAngle += mouseSpeed * delta_time * float(height / 2.0 - mY);

		if (verticalAngle <= glm::radians(-90.0f)) {
			verticalAngle = glm::radians(-90.0f);
		}
		if (verticalAngle >= glm::radians(90.0f)) {
			verticalAngle = glm::radians(90.0f);
		}

		glm::vec3 direction(
			cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
		);

		glm::vec3 right = glm::vec3(
			sin(horizontalAngle - glm::radians(90.0f)),
			0,
			cos(horizontalAngle - glm::radians(90.0f))
		);

		glm::vec3 up = glm::cross(right, direction);

		float speed = speedN;
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			speed = speedN * 2;
		}
		// Move forward
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			position += direction * delta_time * speed;
		}
		// Move backward
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			position -= direction * delta_time * speed;
		}
		// Strafe right
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			position += right * delta_time * speed;
		}
		// Strafe left
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			position -= right * delta_time * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			position += glm::vec3(0, 1, 0) * delta_time * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
			position -= glm::vec3(0, 1, 0) * delta_time * speed;
		}

		proMat = glm::perspective(initialFov, 16.0f / 9.0f, 0.1f, 1000.0f);
		viewMat = glm::lookAt(position, position + direction, up);
	}


	void setWindow(GLFWwindow * wnd)
	{
		window = wnd;
	}

	glm::mat4 getProjectionMatrix()
	{
		return proMat;
	}

	glm::mat4 getViewMatrix()
	{
		return viewMat;
	}

	void setKeyPressedCallback(GLFWkeyfun callback)
	{
		glfwSetKeyCallback(window, callback);
	}

}