#include "Test1.h"

namespace test1 {

	GLFWwindow* wnd;
	GLuint vertex_array_id = 0;
	DrawableElement* element1;

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


	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_E && action == GLFW_RELEASE)
			element1->addImpulse(glm::vec3(-1.0f, 0.0f, 0.0f));

		if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
			element1->addImpulse(glm::vec3(1.0f, 0.0f, 0.0f));
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

		controls::setWindow(wnd);
		controls::setKeyPressedCallback(key_callback);
		return true;
	}

	bool mainLoop()
	{
		glPointSize(5.0f);
		element1 = new DrawableElement(10.0f, glm::vec3(0.51f, 0.51f, 0.51f), glm::vec3(0.0f), glm::vec3(0.0f), NULL);
		DrawableElement* element2 = new DrawableElement(1.0f, glm::vec3(0.51f, -0.51f, 0.51f), glm::vec3(0.0f), glm::vec3(0.0f), NULL);
		DrawableElement* element3 = new DrawableElement(1.0f, glm::vec3(-0.51f, -0.51f, 0.51f), glm::vec3(0.0f), glm::vec3(0.0f), NULL);
		DrawableElement* element4 = new DrawableElement(1.0f, glm::vec3(-0.51f, 0.51f, 0.51f), glm::vec3(0.0f), glm::vec3(0.0f), NULL);

		DrawableElement* element5 = new DrawableElement(1.0f, glm::vec3(0.51f, 0.51f, -0.51f), glm::vec3(0.0f), glm::vec3(0.0f), NULL);
		DrawableElement* element6 = new DrawableElement(1.0f, glm::vec3(0.51f, -0.51f, -0.51f), glm::vec3(0.0f), glm::vec3(0.0f), NULL);
		DrawableElement* element7 = new DrawableElement(1.0f, glm::vec3(-0.51f, -0.51f, -0.51f), glm::vec3(0.0f), glm::vec3(0.0f), NULL);
		DrawableElement* element8 = new DrawableElement(1.0f, glm::vec3(-0.51f, 0.51f, -0.51f), glm::vec3(0.0f), glm::vec3(0.0f), NULL);

		DrawableConnection con12 = DrawableConnection(1.0f, 3.0f, 1.0f, element1, element2, element1->getProgram());
		DrawableConnection con23 = DrawableConnection(1.0f, 3.0f, 1.0f, element2, element3, element1->getProgram());
		DrawableConnection con34 = DrawableConnection(1.0f, 3.0f, 1.0f, element3, element4, element1->getProgram());
		DrawableConnection con41 = DrawableConnection(1.0f, 3.0f, 1.0f, element4, element1, element1->getProgram());

		DrawableConnection con56 = DrawableConnection(1.0f, 3.0f, 1.0f, element5, element6, element1->getProgram());
		DrawableConnection con67 = DrawableConnection(1.0f, 3.0f, 1.0f, element6, element7, element1->getProgram());
		DrawableConnection con78 = DrawableConnection(1.0f, 3.0f, 1.0f, element7, element8, element1->getProgram());
		DrawableConnection con85 = DrawableConnection(1.0f, 3.0f, 1.0f, element8, element5, element1->getProgram());

		DrawableConnection con15 = DrawableConnection(1.0f, 3.0f, 1.0f, element1, element5, element1->getProgram());
		DrawableConnection con26 = DrawableConnection(1.0f, 3.0f, 1.0f, element2, element6, element1->getProgram());
		DrawableConnection con37 = DrawableConnection(1.0f, 3.0f, 1.0f, element3, element7, element1->getProgram());
		DrawableConnection con48 = DrawableConnection(1.0f, 3.0f, 1.0f, element4, element8, element1->getProgram());

		DrawableConnection con17 = DrawableConnection(1.6f, 3.0f, 1.0f, element1, element7, element1->getProgram());
		DrawableConnection con28 = DrawableConnection(1.6f, 3.0f, 1.0f, element2, element8, element1->getProgram());
		DrawableConnection con35 = DrawableConnection(1.6f, 3.0f, 1.0f, element3, element5, element1->getProgram());
		DrawableConnection con46 = DrawableConnection(1.6f, 3.0f, 1.0f, element4, element6, element1->getProgram());
		

		GLuint uniform_loc_viewmatrix = glGetUniformLocation(element1->getProgram(), "view_matrix");
		GLuint uniform_loc_projectionmatrix = glGetUniformLocation(element1->getProgram(), "projection_matrix");

		double last_time = glfwGetTime();
		do {
			double delta_time = glfwGetTime() - last_time;
			last_time = glfwGetTime();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			controls::computeMatrices(delta_time);

			glm::mat4 view = controls::getViewMatrix();
			glm::mat4 projection = controls::getProjectionMatrix();
			glUniformMatrix4fv(uniform_loc_viewmatrix, 1, GL_FALSE, &view[0][0]);
			glUniformMatrix4fv(uniform_loc_projectionmatrix, 1, GL_FALSE, &projection[0][0]);
			
			con12.calculateForces();
			con23.calculateForces();
			con34.calculateForces();
			con41.calculateForces();

			con56.calculateForces();
			con67.calculateForces();
			con78.calculateForces();
			con85.calculateForces();

			con15.calculateForces();
			con26.calculateForces();
			con37.calculateForces();
			con48.calculateForces();

			con17.calculateForces();
			con28.calculateForces();
			con35.calculateForces();
			con46.calculateForces();

			element1->update(delta_time);
			element2->update(delta_time);
			element3->update(delta_time);
			element4->update(delta_time);

			element5->update(delta_time);
			element6->update(delta_time);
			element7->update(delta_time);
			element8->update(delta_time);

			element1->draw();
			element2->draw();
			element3->draw();
			element4->draw();

			element5->draw();
			element6->draw();
			element7->draw();
			element8->draw();

			con12.draw();
			con23.draw();
			con34.draw();
			con41.draw();

			con56.draw();
			con67.draw();
			con78.draw();
			con85.draw();

			con15.draw();
			con26.draw();
			con37.draw();
			con48.draw();

			con17.draw();
			con28.draw();
			con35.draw();
			con46.draw();

			glfwSwapBuffers(wnd);
			glfwPollEvents();
		} while (glfwGetKey(wnd, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(wnd) == GL_FALSE);

		glDeleteProgram(element1->getProgram());
		delete element1;
		delete element2;
		delete element3;
		delete element4;

		glDeleteVertexArrays(1, &vertex_array_id);

		glfwTerminate();
		getchar();
		return true;
	}
}