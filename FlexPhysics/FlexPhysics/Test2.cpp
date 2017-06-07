#include "Test2.h"

namespace test2 {

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
			element1->addForce(glm::vec3(0.0f, -10.0f, 0.0f));

		if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
			element1->addForce(glm::vec3(0.0f, 10.0f, 0.0f));
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
		std::vector<vec4> vertices;
		std::vector<vec3> normals;
		std::vector<vec2> uvs;
		std::vector<unsigned int> indices;

		/*elements.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
		elements.push_back(glm::vec3(0.5f, -0.5f, 0.5f));
		elements.push_back(glm::vec3(-0.5f, -0.5f, 0.5f));
		elements.push_back(glm::vec3(-0.5f, 0.5f, 0.5f));

		elements.push_back(glm::vec3(0.5f, 0.5f, -0.5f));
		elements.push_back(glm::vec3(0.5f, -0.5f, -0.5f));
		elements.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));
		elements.push_back(glm::vec3(-0.5f, 0.5f, -0.5f));*/

		loader::loadOBJ("icoSphere.obj", indices, vertices, uvs, normals);

		std::vector<vec3> elements = std::vector<vec3>();
		for (int i = 0; i < vertices.size(); i++) {
			elements.push_back(glm::vec3(vertices[i].x, vertices[i].y, vertices[i].z));
		}

		FlexObject object = FlexObject(SOLID, 0.1f);
		object.init(elements);

		element1 = object.getElement(0);

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

			object.update(delta_time);

			glfwSwapBuffers(wnd);
			glfwPollEvents();
		} while (glfwGetKey(wnd, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(wnd) == GL_FALSE);

		glDeleteProgram(element1->getProgram());

		glDeleteVertexArrays(1, &vertex_array_id);

		glfwTerminate();
		getchar();
		return true;
	}
}