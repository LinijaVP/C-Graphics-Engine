#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cerrno>


std::string get_file_contents(const char* filename);

class Shader {
	public:
		GLuint ID;
		Shader(const char* vertexFile, const char* fragmentFile);

		void Activate();
		void Delete();

	private:
		// Checks if the different Shaders have compiled properly
		void compileErrors(unsigned int shader, const char* type);

};




#endif 