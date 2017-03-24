#include "Test1.h"

namespace test1 {

	GLFWwindow* wnd;
	GLuint vertex_array_id = 0;

	bool init();

	bool mainLoop();

	bool start() {
		logger::debug("Initializing...");
		if (!init())
			return false;

		logger::debug("Starting main loop...");
		if (!mainLoop())
			return false;

		return true;
	}


	bool init()
	{
		//create glfw window
		logger::debug("Creating Window");
		wnd = WindowFactory::CreateWindow(1920, 1080, "FlexPhysics", false);
		if (wnd == nullptr) {
			return false;
		}

		//setup input mode for window
		glfwSetInputMode(wnd, GLFW_STICKY_KEYS, GL_TRUE);
		glfwSetInputMode(wnd, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		//setup several opengl options
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		glfwSwapInterval(1);

		//Init vertex array
		GLuint cur_vertex_array_id;
		glGenVertexArrays(1, &cur_vertex_array_id);
		logger::debug("Vertex Array at Location %i!", cur_vertex_array_id);
		glBindVertexArray(cur_vertex_array_id);

		vertex_array_id = cur_vertex_array_id;
		return true;
	}

	bool mainLoop()
	{
		glPointSize(5.0f);
		DrawableElement* element1 = new DrawableElement(1.0f, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f), NULL);
		DrawableElement* element2 = new DrawableElement(1.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f), NULL);

		Connection con = Connection(1.0f, 3.0f, 1.0f, element1, element2);

		GLuint uniform_loc_viewmatrix = glGetUniformLocation(element1->getProgram(), "view_matrix");
		GLuint uniform_loc_projectionmatrix = glGetUniformLocation(element1->getProgram(), "projection_matrix");

		double last_time = glfwGetTime();
		do {
			float delta_time = glfwGetTime() - last_time;
			last_time = glfwGetTime();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			controls::computeMatrices(wnd, delta_time);

			glm::mat4 view = controls::getViewMatrix();
			glm::mat4 projection = controls::getProjectionMatrix();
			glUniformMatrix4fv(uniform_loc_viewmatrix, 1, GL_FALSE, &view[0][0]);
			glUniformMatrix4fv(uniform_loc_projectionmatrix, 1, GL_FALSE, &projection[0][0]);
			
			con.calculateForces(delta_time);
			element1->draw();
			element2->draw();

			glfwSwapBuffers(wnd);
			glfwPollEvents();
		} while (glfwGetKey(wnd, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(wnd) == GL_FALSE);

		glDeleteProgram(element1->getProgram());
		delete element1;
		delete element2;
		glDeleteVertexArrays(1, &vertex_array_id);

		glfwTerminate();
		return true;
	}
}