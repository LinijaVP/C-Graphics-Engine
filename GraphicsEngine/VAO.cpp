#include "VAO.h"

VAO::VAO() {
	//Create the objects with one item each
	glGenVertexArrays(1, &ID);
}

void VAO::LinkVBO(VBO vbo, GLuint layout) {
	vbo.Bind();
	
	//Configure vertex attribute so it knows how to read the VBO
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(layout);

	vbo.Unbind();
}

void VAO::Bind() {
	//Make VAO the current Vertex Array object by binding
	glBindVertexArray(ID);
}

void VAO::Unbind() {
	glBindVertexArray(0);
}

void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}