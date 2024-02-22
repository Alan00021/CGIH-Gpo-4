#pragma once
#include<stdio.h>
#include<string>
#include<iostream>
#include<fstream>		//Libreria que nos permitira leer archivos de texto plano externos

#include<glew.h>

class Shader
{
public:
	Shader();
	void CreatefromString(const char* vertexCode, const char* fragmentCode);		//Crear de una cadena
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);		//Crea de archivo
	std::string ReadFile(const char*  fileLocation);		//Lee archivo
	GLuint getProjectLocation();		//Sirven para mandar y leer información
	GLuint getModelLocation();
	//Ir agregando nuevas funciones get para cada variable Uniform

	void useShader();
	void ClearShader();
	~Shader();

private: 
	GLuint shaderID, uniformProjection, uniformModel; 	//Ir agregando nuevas variables Uniform
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* ShaderCode, GLenum shaderType);
};

