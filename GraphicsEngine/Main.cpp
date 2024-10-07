#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


#include "Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

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

	Shader shaderProgram("default.vert", "default.frag");

	//Create Vertex array object, bind it, then create vertex buffer and buffer for indices, 
	//link vao to vbo and then unbind all of them to prevent overwrite
	VAO vao;
	vao.Bind();
	VBO vbo(vertices, sizeof(vertices));
	EBO ebo(indices, sizeof(indices));

	//vao.LinkVBO(vbo, 0);
	// Links VBO attributes such as coordinates and colors to VAO
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	// Texture
	Texture popCat("Graphics/pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);

	// Enable depth write
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	//for time manipulations
	float prevTime = float(glfwGetTime());
	float angle = 0.0f;
	float rotation = 0.0f;
	//Main while loop
	while (!glfwWindowShouldClose(window)) {
		float time = float(glfwGetTime());
		if (time - prevTime > 0.03f) { //This means every 0.1 second
			prevTime = time;
		}

		//glClearColor(float(sin(angle)), float(cos(angle)), float(tan(angle)), 1.0f); changing colors with angle
		//Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//Clean the back buffer and assign new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Specify shader Program
		shaderProgram.Activate();

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		//Bind texture
		popCat.Bind();
		//Bind VAO so OpenGL will use it
		vao.Bind();
		
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

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
	popCat.Delete();

	//Destroy window and terminate glfw
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}