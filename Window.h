#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);		//Crea una ventana  apartir de lso valores que tengan esas variables
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	bool keys[1024];		//Es como la declaración del teclado
	GLint bufferWidth, bufferHeight;
	void createCallbacks();		//Recibe teclado y mouse
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
};

