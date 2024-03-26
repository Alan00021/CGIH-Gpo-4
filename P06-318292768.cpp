/*
Pr�ctica 6: Texturizado
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
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_m.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture dadoTexture;
Texture logofiTexture;

Texture cofreTexture;


Model Kitt_M;
Model Llanta_M;
Model Dado_M;
Model Dado_An;

Skybox skybox;

//CARROO
Model CarroC;
Model CarroCof;
Model CarroTIR;
Model CarroTIL;
Model CarroTBR;
Model CarroTBL;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;


// Vertex Shader
static const char* vShader = "shaders/shader_texture.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_texture.frag";




//c�lculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}



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

	unsigned int vegetacionIndices[] = {
		0, 1, 2,
		0, 2, 3,
		4,5,6,
		4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,
	};
	calcAverageNormals(indices, 12, vertices, 32, 8, 5);



	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void CrearDado()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,

		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,

		// right
		4, 5, 6,
		6, 7, 4,

	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
// average normals
	GLfloat cubo_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		-0.5f, -0.5f,  0.5f,	0.5f,   0.33f,		0.0f,	0.0f,	-1.0f,	//0
		0.5f, -0.5f,  0.5f,		0.75f,	0.33f,		0.0f,	0.0f,	-1.0f,	//1			CAra principal Elefante
		0.5f,  0.5f,  0.5f,		0.75f,	0.66f,		0.0f,	0.0f,	-1.0f,	//2
		-0.5f,  0.5f,  0.5f,	0.5f,	0.66f,		0.0f,	0.0f,	-1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	    0.75f,  0.33f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	1.0f,	0.33f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	1.0f,	0.66f,		-1.0f,	0.0f,	0.0f,			//Jirafas
		0.5f,  0.5f,  0.5f,	    0.75f,	0.66f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.25f,   0.33f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		0.0f,	0.33f,		0.0f,	0.0f,	1.0f,			//Catarinas
		0.5f,  0.5f, -0.5f,		0.0f,	0.66f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.25f,	0.66f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		  T
		-0.5f, -0.5f,  -0.5f,	0.25f,   0.33f,		1.0f,	0.0f,	0.0f,	//Inferior Izq
		-0.5f, -0.5f,  0.5f,	0.5f,	0.33f,		1.0f,	0.0f,	0.0f,	//Inferior Der 		//Pulpos
		-0.5f,  0.5f,  0.5f,	0.5f,	0.66f,		1.0f,	0.0f,	0.0f,	//Superior Der 
		-0.5f,  0.5f,  -0.5f,	0.25f,	0.66f,		1.0f,	0.0f,	0.0f,	//Superior Izq 

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.5f,  0.0f,		0.0f,	1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	0.75f,	0.0f,		0.0f,	1.0f,	0.0f,			//Puerquitos
		 0.5f,  -0.5f,  -0.5f,	0.75f,	0.33f,		0.0f,	1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.5f,	0.33f,		0.0f,	1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		 -0.5f, 0.5f,	 0.5f,	  0.5f,   0.66f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,	 0.5f,	  0.75f,   0.66f,		0.0f,	-1.0f,	0.0f,			///Pajaros
		  0.5f, 0.5f,	-0.5f,	  0.75f,   1.0f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,	-0.5f,	  0.5f,   1.0f,		0.0f,	-1.0f,	0.0f,

	};

	Mesh* dado = new Mesh();
	dado->CreateMesh(cubo_vertices, cubo_indices, 192, 36);
	meshList.push_back(dado);

}


///////////////////////////
void CrearDado10()
{

	GLuint indices[] = {
	  0, 1, 2,
	  3, 4, 5,
	  6, 7, 8,
	  9, 10, 11,
	  12, 13, 14,
	  15, 16, 17,
	  18, 19, 20,
	  21, 22, 23,
	  24, 25, 26, //Si se cambia una coordenada por ejemplo repetir el 24 podemos simular una transparencia
	  27, 28, 29, 
	};

	GLfloat vertices[] = {			//X		  //Y

		// x		  y      z        S	      T       NX     NY      NZ
		 0.0f ,  0.0f,		0.5,    0.42f,   0.25f,  0.0f,	 0.0f, -1.0f,//PUNTA			1
		 0.0f ,  0.5f,		0.0f,   0.00f,   0.27f,  0.0f,	 0.0f,  0.0f,//  lado iz
		-0.4f ,  0.0f,		0.0f,   0.10f,   0.10f,  0.0f,	 0.0f,  0.0f,// punta der

		 0.0f ,  0.0f,		0.5,	0.42f,  0.25f,  0.0f,	 0.0f, -1.0f,//		3
		 0.5f ,  0.3f,		0.0f,   0.14f,   0.07f,  0.0f,	 0.0f, -1.0f,// 
		 0.0f ,  0.5f,		0.0f,   0.40,   0.00f,  0.0f,	 0.0f, -1.0f,// 

		 0.0f ,  0.0f,		0.5,	0.42f,  0.25f,  0.0f,	 0.0f, -1.0f,//		9
		 0.5f ,  -0.3f,		0.0f,   0.51,   0.017f,  0.0f,	 0.0f, -1.0f,// 
		 0.5f , 0.3f,		0.0f,   0.75,   0.08f,  0.0f,	 0.0f, -1.0f,//


		 0.0f ,  0.0f,		0.5,	0.42f,  0.25f,  0.0f,	 0.0f, -1.0f,//		5
		 0.0f , -0.5f,		0.0f,   0.55,   0.48f,  0.0f,	 0.0f, -1.0f,//
		 0.5f , -0.3f,		0.0f,   0.32f,  0.49f,  0.0f,	 0.0f, -1.0f,//


		 0.0f ,  0.0f,		0.5,	0.42f,  0.25f,  0.0f,	 0.0f, -1.0f,//		7
		 -0.4f , -0.0f,		0.0f,   0.20f,  0.45f,  0.0f,	 0.0f, -1.0f,//
		 0.0f ,  -0.5f,		0.0f,   0.023f, 0.33f,  0.0f,	 0.0f,  0.0f,//

		 0.0f ,  0.0f,		-0.5,   0.61f,  0.75f,  0.0f,	 0.0f, -1.0f,//		2
		-0.4f ,  0.0f,		0.0f,   0.28f,  0.90f,  0.0f,	 0.0f,  0.0f,//
		 0.0f ,  0.5f,		0.0f,   0.18f,  0.73f,  0.0f,	 0.0f,  0.0f,//

		 0.0f ,  0.0f,		-0.5,	0.61f,  0.75f,  0.0f,	 0.0f, -1.0f,//		8
		 0.0f ,  0.5f,		0.0f,   0.20f,  0.67f,  0.0f,	 0.0f, -1.0f,//
		 0.5f ,  0.3f,		0.0f,   0.38,   0.54f,  0.0f,	 0.0f, -1.0f,//

		 0.0f ,  0.0f,		-0.5,	0.61f,  0.75f,  0.0f,	 0.0f, -1.0f,//		10
		 0.5f ,  0.3f,		0.0f,   0.43,   0.53f,  0.0f,	 0.0f, -1.0f,//
		 0.5f , -0.3f,		0.0f,   0.78,   0.52f,  0.0f,	 0.0f, -1.0f,//

		 0.0f ,  0.0f,		-0.5,	0.61f,  0.75f,  0.0f,	 0.0f, -0.0f,//		4
		 0.5f , -0.3f,		0.0f,   0.95,   0.9f,  0.0f,	 0.0f, -0.0f,//	//////////////////////
		 0.0f , -0.5f,		0.0f,   0.71,   0.98f,  0.0f,	 0.0f, -0.0f,//

		 0.0f ,  0.0f,		-0.5,	0.61f,  0.75f,  0.0f,	 0.0f, -1.0f,//		6
		 0.0f , -0.5f,		0.0f,   0.58,   1.0f,   0.0f,	 0.0f, -1.0f,//	//////////////////////
		-0.4f ,  0.0f,		0.0f,   0.36,   0.95f,  0.0f,	 0.0f, -1.0f,//
	};

	calcAverageNormals(indices, 30, vertices, 24 * 10, 8, 5);

	Mesh* Dado10 = new Mesh();
	Dado10->CreateMesh(vertices, indices, 24 * 10, 30);
	meshList.push_back(Dado10);
}
////////////////////////////
/////////////////



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CrearDado();
	CrearDado10();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	/*dadoTexture = Texture("Textures/dado-de-numeros.png");
	dadoTexture.LoadTextureA();*/

	dadoTexture = Texture("Textures/Dado10.tga");		//Modificaci�n por vertices
	dadoTexture.LoadTextureA();
	cofreTexture = Texture("Textures/escudo_fi_color.tga");		//Modificaci�n por vertices
	cofreTexture.LoadTextureA();

	Dado_An = Model();
	Dado_An.LoadModel("Models/cubo_animales.obj");		//Carga el modelo del 3DS MAX



	CarroC = Model();
	CarroC.LoadModel("Models/carroC.obj");			/////////////////
	CarroTIR = Model();
	CarroTIR.LoadModel("Models/tireIR.obj");
	CarroTIL = Model();
	CarroTIL.LoadModel("Models/tireIL.obj");	///////////////
	CarroTBR = Model();							
	CarroTBR.LoadModel("Models/tireBR.obj");	//////////////
	CarroTBL = Model();
	CarroTBL.LoadModel("Models/tireBL.obj");	//////////////////
	CarroCof = Model();
	CarroCof.LoadModel("Models/carroCof.obj");	/////////////

	/////////////////////


	//logofiTexture = Texture("Textures/escudo_fi_color.png");
	//logofiTexture.LoadTextureA();


	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");


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
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformColor = shaderList[0].getColorLocation();
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		color = glm::vec3(1.0f, 1.0f, 1.0f);//color blanco, multiplica a la informaci�n de color de la textura

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();

		//////EJERCICIO DE CLASE//////
		////Dado de Opengl
		////Ejercicio 1: Texturizar su cubo con la imagen dado_animales ya optimizada por ustedes
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-1.5f, 4.5f, -2.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//dadoTexture.UseTexture();
		//meshList[4]->RenderMesh();

		////Ejercicio 2:Importar el cubo texturizado en el programa de modelado con 
		////la imagen dado_animales ya optimizada por ustedes

		////Dado importado
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-3.0f, 3.0f, -2.0f));
		//model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Dado_An.RenderModel();

		//Para referencias al archivo de mtl, debemos quitar toda la ruta que tiene, y dejar solo la parte de donde jalaremos la forma
		//En este caso el 
		//map_Ka cubo_animales.tga
		//map_Kd cubo_animales.tga
		//Quedan de esa manera.


		/*Reporte de pr�ctica :
		Ejercicio 1: Crear un dado de 8 caras y texturizarlo por medio de c�digo
		Ejercicio 2: Importar el modelo de su coche con sus 4 llantas acomodadas
		y tener texturizadas las 4 llantas (diferenciar caucho y rin)  y
		texturizar el logo de la Facultad de ingenier�a en el cofre de su propio modelo de coche*/

		//Dado 10 caras
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-8.5f, 5.5f, -5.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dadoTexture.UseTexture();
		meshList[5]->RenderMesh();


		//Instancia del coche 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f + mainWindow.getmuevex(), -1.8f, -3.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		color = glm::vec3(.0f, 1.0f, 1.0f);//llanta con color gris
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CarroC.RenderModel();

		//Instancia del cofre 
		model = modelaux;
		model = glm::translate(model, glm::vec3(-5.42f, 3.6f, 7.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.18f, 0.2f, 0.18f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);//llanta con color gris
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		CarroCof.RenderModel();
		glDisable(GL_BLEND);

		//Llanta delantera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.4f, 2.0f, 2.9f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		color = glm::vec3(0.5f, 0.5f, 0.5f);//llanta con color gris
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CarroTIL.RenderModel();

		//Llanta trasera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(8.4f, 1.8f, 2.4f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CarroTIR.RenderModel();

		//Llanta delantera derecha //
		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.4f, 2.0f, 11.8f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CarroTBR.RenderModel();

		//Llanta trasera derecha //
		model = modelaux;
		model = glm::translate(model, glm::vec3(8.4f, 2.0f, 12.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		//color = glm::vec3(0.0f, 0.0f, 0.0f);//llanta con color gris
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CarroTBL.RenderModel();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
/*
//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		logofiTexture.UseTexture(); //textura con transparencia o traslucidez
		FIGURA A RENDERIZAR de OpenGL, si es modelo importado no se declara UseTexture
		glDisable(GL_BLEND);
*/