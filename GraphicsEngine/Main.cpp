#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";




int main() {
	glfwInit();

	//Define what Opengl version we are using, here we use version 3.3 and use the core library
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};

	//Create window with size 800,800
	GLFWwindow* window = glfwCreateWindow(800, 800, "GraphicsEngine", NULL, NULL);
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
	glViewport(0, 0, 800, 800);

	//Create vertex shader and appoint the created shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//Create fragment shader and appoint the created shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Create shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//Create reference containers for vertex buffer and vertex array
	GLuint VAO, VBO;

	//Create the objects with one item each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//Make VAO the current Vertex Array object by binding
	glBindVertexArray(VAO);

	//Bind the VBO by specifying it's an array buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Add the vertices to the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Configure vertex attribute so it knows how to read the VBO
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Bind VBO and VAO to 0 so we don't modify them
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	//Clean the back buffer and assign new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	//Swap the back and the front buffer
	glfwSwapBuffers(window);


	//Main while loop
	while (!glfwWindowShouldClose(window)) {


		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//Specify shader Program
		glUseProgram(shaderProgram);
		//Bind VAO so OpenGL will use it
		glBindVertexArray(VAO);
		//Draw triangles
		glDrawArrays(GL_TRIANGLES,0,3);

		glfwSwapBuffers(window);
		//Take care of glfw events
		glfwPollEvents();
	}


	//Delete section
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);



	//Destroy window and terminate glfw
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}