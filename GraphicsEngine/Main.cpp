#include "Model.h"


const unsigned int width = 800;
const unsigned int height = 800;

int main() {
	glfwInit();

	//Define what Opengl version we are using, here we use version 3.3 and use the core library
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create window with size width,height
	GLFWwindow* window = glfwCreateWindow(width, height, "GraphicsEngine", NULL, NULL);
	//Error check: was window sucessfully created
	if (window == NULL) { 
		std::cout << "Unable to create GLFW window." << std::endl; 
		glfwTerminate();
		return -1;
	}
	//Make the context the current window
	glfwMakeContextCurrent(window);

	//Load glad that configures OpenGL
	gladLoadGL();

	//Specify the viewport of OpenGL in the window and set it from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Take care of all the light related things
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	// Enable depth write
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	Model model("Models/sword/scene.gltf");

	//for time manipulations
	float prevTime = float(glfwGetTime());
	float deltaTime = 0.0f;
	float lastFrame = prevTime;
	//Main while loop
	while (!glfwWindowShouldClose(window)) {
		float time = float(glfwGetTime());
		if (time - prevTime > 0.03f) { //This means every 0.1 second
			prevTime = time;
		}
		deltaTime = time - lastFrame;
		lastFrame = time;

		
		//Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//Clean the back buffer and assign new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Handles camera inputs
		camera.Inputs(window, deltaTime);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// Draw a model
		model.Draw(shaderProgram, camera);

		//Swap the back and the front buffer
		glfwSwapBuffers(window);
		//Take care of glfw events
		glfwPollEvents();
	}

	//Delete section
	shaderProgram.Delete();

	//Destroy window and terminate glfw
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}