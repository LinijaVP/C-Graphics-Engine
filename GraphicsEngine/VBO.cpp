#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
	glGenBuffers(1, &ID);
	//Bind the VBO by specifying it's an array buffer
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	//Add the vertices to the VBO
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

}

void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}