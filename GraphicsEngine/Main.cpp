#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

int main() {
	glfwInit();

	//Define what Opengl version we are using, here we use version 3.3 and use the core library
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
		- 0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f
	};

	GLuint indices[] = {
		0, 3 , 5,
		3, 2 , 4,
		5, 4 , 1
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

	Shader shaderProgram("default.vert", "default.frag");

	//Create Vertex array object, bind it, then create vertex buffer and buffer for indices, 
	//link vao to vbo and then unbind all of them to prevent overwrite
	VAO vao;
	vao.Bind();
	VBO vbo(vertices, sizeof(vertices));
	EBO ebo(indices, sizeof(indices));
	vao.LinkVBO(vbo, 0);
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	float prevTime = float(glfwGetTime());
	float angle = 0.0f;
	//Main while loop
	while (!glfwWindowShouldClose(window)) {
		float time = float(glfwGetTime());
		if (time - prevTime > 0.1f) { //This means every 0.1 second
			
		}

		//glClearColor(float(sin(angle)), float(cos(angle)), float(tan(angle)), 1.0f); changing colors with angle
		//Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//Clean the back buffer and assign new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		//Specify shader Program
		shaderProgram.Activate();
		//Bind VAO so OpenGL will use it
		vao.Bind();
		//Draw triangles
		glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0);

		//Swap the back and the front buffer
		glfwSwapBuffers(window);
		//Take care of glfw events
		glfwPollEvents();
	}

	//Delete section
	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	shaderProgram.Delete();

	//Destroy window and terminate glfw
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}