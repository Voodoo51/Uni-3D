#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include "Math.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>

using namespace glm;

/*!
		Funkcja pozwalająca na zarządanie shaderem.
*/
class Shader
{
public:
	/*!
		ID shadera.
	*/
	unsigned int ID;

	Shader() {};
	// constructor reads and builds the shader
	/*!
		Konstruktor który pozwala na wczytanie shadera.
	*/
	Shader(const char* vertexPath, const char* fragmentPath)
	{
		load(vertexPath, fragmentPath);
	}

	/*!
		Funkcja wczytująca shader.
	*/
	void load(const char* vertexPath, const char* fragmentPath)
	{
		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		// vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		// print compile errors if any
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		};

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		// print compile errors if any
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		};


		// shader Program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		// print linking errors if any
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		if (!success)
		{
			std::cout << "VERTEX SHADER" << std::endl;
			std::cout << vertexCode << std::endl;
			std::cout << std::endl;
			std::cout << "FRAGMENT SHADER" << std::endl;
			std::cout << fragmentCode << std::endl;
		}
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);


	}

	/*!
		Funkcja pozwalająca na użycie shadera.
	*/
	void use()
	{
		glUseProgram(ID);
	}

	/*!
		Funkcja usuwająca shader.
	*/
	void free()
	{
		glDeleteProgram(ID);
	}
	
	/*!
		Funkcja ustawiająca uniform o typie bool i danej nazwie na daną wartość.
	*/
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	/*!
		Funkcja ustawiająca uniform o typie int i danej nazwie na daną wartość.
	*/
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	/*!
		Funkcja ustawiająca uniform o typie float i danej nazwie na daną wartość.
	*/
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	/*!
		Funkcja ustawiająca uniform o typie vec3 i danej nazwie na daną wartość.
	*/
	void setFloat3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	/*!
		Funkcja ustawiająca uniform o typie vec3 i danej nazwie na daną wartość.
	*/
	void setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	/*!
		Funkcja ustawiająca uniform o typie vec2 i danej nazwie na daną wartość.
	*/
	void setVec2(const std::string& name, vec2 value) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y);
	}

	/*!
		Funkcja ustawiająca uniform o typie vec3 i danej nazwie na daną wartość.
	*/
	void setVec3(const std::string& name, vec3 value) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
	}
	
	
	void setMat4(const std::string& name, const mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	
};

