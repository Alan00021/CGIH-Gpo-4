/*
Pr�ctica 5: Optimizaci�n y Carga de Modelos
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_m.h"
#include "Camera.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

const float toRadians = 3.14159265f / 180.0f;
//float angulocola = 0.0f;
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;
Model Goddard_M;
Model Goddard_Cuerpo;
Model Goddard_Cabeza;
Model Goddard_Mandibula;
Model Goddard_PAI;
Model Goddard_PAD;
Model Goddard_PDD;
Model Goddard_PDI;

Skybox skybox;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;


// Vertex Shader
static const char* vShader = "shaders/shader_m.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_m.frag";





void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);


}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.5f, 7.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 1.0f);

	/*Goddard_M = Model();
	Goddard_M.LoadModel("Models/goddard_base.obj");*/

	//Se a�ade tanto aqui la ruta o nombre dle archivo a a�adir, como arriba en lso modelos hay que declararlos
	Goddard_Cuerpo = Model();
	Goddard_Cuerpo.LoadModel("Models/cuerpogodaard.obj");
	Goddard_Cabeza = Model();
	Goddard_Cabeza.LoadModel("Models/cabezaG.obj");
	Goddard_Mandibula = Model();
	Goddard_Mandibula.LoadModel("Models/mandibulaG.obj");
	Goddard_PDD = Model();
	Goddard_PDD.LoadModel("Models/piernaDD.obj");
	Goddard_PDI = Model();
	Goddard_PDI.LoadModel("Models/piernaDI.obj");
	Goddard_PAI = Model();
	Goddard_PAI.LoadModel("Models/piernaAI.obj");
	Goddard_PAD = Model();
	Goddard_PAD.LoadModel("Models/piernaAD.obj");

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	

	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Se dibuja el Skybox
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformColor = shaderList[0].getColorLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		// INICIA DIBUJO DEL PISO
		color = glm::vec3(0.5f, 0.5f, 0.5f); //piso de color gris
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[2]->RenderMesh();

		////------------*INICIA DIBUJO DE NUESTROS DEM�S OBJETOS-------------------*
		////Goddard
		//color = glm::vec3(0.0f, 0.0f, 0.0f); //modelo de goddard de color negro
		//
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, -2.0f, -1.5f));
		////modelaux = model;
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Goddard_M.RenderModel();//modificar por el modelo sin las 4 patas y sin cola
		//color = glm::vec3(0.0f, 0.0f, 1.0f);
		////En sesi�n se separara una parte del modelo de Goddard y se unir� por jeraqu�a al cuerpo
		//modelaux = model;
		

		////////////////////////////////

		//------------*INICIA DIBUJO DE NUESTROS DEM�S OBJETOS-------------------*
		//Goddard
		color = glm::vec3(1.0f, 0.1f, 0.1f); //modelo de goddard de color negro

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, -1.5f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Goddard_Cuerpo.RenderModel();//modificar por el modelo sin las 4 patas y sin cola
		color = glm::vec3(0.0f, 0.0f, 1.0f);

		//////////////////////////////////////////////////////////////////
		//pata delantera derecha
		modelaux = model;
		//model = modelaux;
		color = glm::vec3(0.3f, 0.3f, 0.3f); // color 
		model = glm::translate(model, glm::vec3(0.5f, 2.3f, 1.3f));
		model = glm::rotate(model, glm::radians(mainWindow.getanguloPDDD()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Goddard_PDD.RenderModel();//modificar por el modelo sin las 4 patas
		model = modelaux;

		// pata delantera izquierda
		modelaux = model;
		color = glm::vec3(0.3f, 0.3f, 0.3f); // color 
		model = glm::translate(model, glm::vec3(0.6f, 2.3f, -0.1f));
		model = glm::rotate(model, glm::radians(mainWindow.getanguloPDID()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Goddard_PDI.RenderModel();//modificar por el modelo sin las 4 patas
		model = modelaux;//Se agrega para quitar 
		
		//pata trasera izquierda
		modelaux = model;
		color = glm::vec3(0.1f, 0.1f, 0.3f); // color 
		model = glm::translate(model, glm::vec3(-1.2f, 1.5f, 1.2f));
		model = glm::rotate(model, glm::radians(mainWindow.getanguloPADD()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Goddard_PAI.RenderModel();//modificar por el modelo sin las 4 patas
		model = modelaux;

		//pata trasera derecha
		modelaux = model;
		color = glm::vec3(0.1f, 0.1f, 0.3f); // color 
		model = glm::translate(model, glm::vec3(-1.1f, 1.5f, -0.2f));
		model = glm::rotate(model, glm::radians(mainWindow.getanguloPAID()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Goddard_PAD.RenderModel();//modificar por el modelo sin las 4 patas
		model = modelaux;

		//////////////////////////////////////////////////////////////////


		//En sesi�n se separara una parte del modelo de Goddard y se unir� por jeraqu�a al cuerpo
		//modelaux = model; Se quita porque no hay nada que se hered�
		//cabeza
		modelaux = model;
		color = glm::vec3(1.0f, 0.0f, 1.0f); //modelo de color negro
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		model = glm::translate(model, glm::vec3(0.5f, 1.8f, 0.3f));	//Movemos la posici�n del objeto partiendo del origen
		//model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Goddard_Cabeza.RenderModel();//modificar por el modelo sin las 4 patas y sin cola
		//color = glm::vec3(0.0f, 0.0f, 1.0f);
		//En sesi�n se separara una parte del modelo de Goddard y se unir� por jeraqu�a al cuerpo
		//modelaux = model; Se quita porque no hay nada que se hered�


		//Mandibula
		modelaux = model;
		color = glm::vec3(.0f, 1.0f, 0.0f); //modelo de color negro
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		model = glm::translate(model, glm::vec3(1.2f, 1.5f, 0.3f));	//Movemos la posici�n del objeto partiendo del origen
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Goddard_Mandibula.RenderModel();//modificar por el modelo sin las 4 patas
		modelaux = model; //Se quita porque no hay nada que se hered�

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
