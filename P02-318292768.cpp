//Práctica 2 semestre 2024-2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;				//Lista de Mesh
std::vector<MeshColor*> meshColorList;		//Lista de Mesh		Estructura FiFo
std::vector<Shader>shaderList;				//Lista de Mesh
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";

//AGREGADOS

static const char* vShaderAzulF = "shaders/shaderAzulF.vert";
static const char* fShaderAzulF = "shaders/shaderAzulF.frag";
static const char* vShaderROJO = "shaders/shaderROJO.vert";
static const char* fShaderROJO = "shaders/shaderROJO.frag";
static const char* vShaderVerdeC = "shaders/shaderVerdeC.vert";
static const char* fShaderVerdeC = "shaders/shaderVerdeC.frag";
static const char* vShaderVerdeF = "shaders/shaderVerdeF.vert";
static const char* fShaderVerdeF = "shaders/shaderVerdeF.frag";
static const char* vShaderCafe = "shaders/shaderCafe.vert";
static const char* fShaderCafe = "shaders/shaderCafe.frag";

//shaders nuevos se crearían acá

float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067		//Se despliega en otro momento

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,						//Estos indices pintan a partir de los vértices que creamos abajo, solo indicando de que punto a que punto iremos
		1,0,3

	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1					Estos puntos posicionan los vertices por decirlo asi
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);		//El último valor nos dice cuantos vertices tenemos 3*4 = 12
	meshList.push_back(obj1);
}

void CreaPiramideVerde()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,						//Estos indices pintan a partir de los vértices que creamos abajo, solo indicando de que punto a que punto iremos
		1,0,3

	};
	GLfloat vertices[] = {
		-0.2f, -0.2f,0.0f,	//0
		0.2f,-0.2f,0.0f,	//1					Estos puntos posicionan los vertices por decirlo asi
		0.0f,0.2f, -0.15f,	//2
		0.0f,-0.2f,-0.2f,	//3

	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);		//El último valor nos dice cuantos vertices tenemos 3*4 = 12
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);		//Vetices = renglones * columnas = 8*3=24   El otro dato es 6*&
	meshList.push_back(cubo);
}



void CrearCuboVerdeC()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.15f, -0.15f,  0.15f,
		0.15f, -0.15f,  0.15f,
		0.15f,  0.15f,  0.15f,
		-0.15f,  0.15f,  0.15f,
		// back
		-0.15f, -0.15f, -0.15f,
		0.15f, -0.15f, -0.15f,
		0.15f,  0.15f, -0.15f,
		-0.15f,  0.15f, -0.15f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);		//Vetices = renglones * columnas = 8*3=24   El otro dato es 6*&
	meshList.push_back(cubo);
}



void CrearCuboCafe()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.1f, -0.1f,  0.1f,
		0.1f, -0.1f,  0.1f,
		0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,
		// back
		-0.1f, -0.1f, -0.1f,
		0.1f, -0.1f, -0.1f,
		0.1f,  0.1f, -0.1f,
		-0.1f,  0.1f, -0.1f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);		//Vetices = renglones * columnas = 8*3=24   El otro dato es 6*&
	meshList.push_back(cubo);
}




void CrearLetrasyFiguras()
{
	GLfloat vertices_letras[] = {
		//Comienza la A
		-1.0f,  -0.4f,      0.0f,			0.0f,	0.0f,	1.0f,
		-0.9f,  -0.4f,		0.0f,			0.0f,	0.0f,	1.0f,
		-0.8f,	 0.4f,		0.0f,			0.0f,	0.0f,	1.0f,

		-0.8f,	 0.4f,		0.0f,			0.0f,	0.0f,	1.0f,
		-0.9f,	-0.4f,		0.0f,			0.0f,	0.0f,	1.0f,
		-0.8f,	 0.2f,		0.0f,			0.0f,	0.0f,	1.0f,

		-0.8f,	 0.4f,		0.0f,			0.0f,	0.0f,	1.0f,
		-0.7f,	-0.4f,		0.0f,			0.0f,	0.0f,	1.0f,
		-0.6f,	-0.4f,		0.0f,			0.0f,	0.0f,	1.0f,

		-0.8f,	 0.4f,		0.0f,			0.0f,	0.0f,	1.0f,
		-0.7f,	-0.4f,		0.0f,			0.0f,	0.0f,	1.0f,
		-0.8f,	 0.2f,		0.0f,			0.0f,	0.0f,	1.0f,

		-0.9f,	 0.0f,		0.0f,			0.0f,	0.0f,	1.0f,
		-0.9f,	-0.1f,		0.0f,			0.0f,	0.0f,	1.0f,
		-0.7f,	-0.1f,		0.0f,			0.0f,	0.0f,	1.0f,

		-0.7f,	-0.1f,		0.0f,			0.0f,	0.0f,	1.0f,
		-0.7f,	 0.0f,		0.0f,			0.0f,	0.0f,	1.0f,		//Termina A
		-0.9f,	 0.0f,		0.0f,			0.0f,	0.0f,	1.0f,

		-0.4f,	 0.4f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.3f,	 0.4f,		0.0f,			0.0f,	1.0f,	0.0f,		//Comienza U
		-0.4f,  -0.4f,		0.0f,			0.0f,	1.0f,	0.0f,

		-0.3f,	 0.4f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.3f,	-0.4f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.4f,	-0.4f,		0.0f,			0.0f,	1.0f,	0.0f,

		-0.3f,	-0.4f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.3f,	-0.3f,		0.0f,			0.0f,	1.0f,	0.0f,
		0.0f,	-0.4f,		0.0f,			0.0f,	1.0f,	0.0f,

		0.0f,	-0.4f,		0.0f,			0.0f,	1.0f,	0.0f,
		0.0f,	-0.3f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.3f,	-0.3f,		0.0f,			0.0f,	1.0f,	0.0f,

		-0.1f,	-0.4f,		0.0f,			0.0f,	1.0f,	0.0f,
		0.0f,	-0.4f,		0.0f,			0.0f,	1.0f,	0.0f,
		0.0f,	 0.4f,		0.0f,			0.0f,	1.0f,	0.0f,

		0.0f,	 0.4f,		0.0f,			0.0f,	1.0f,	0.0f,
		-0.1f,	 0.4f,		0.0f,			0.0f,	1.0f,	0.0f,			//Fina de la U
		-0.1f,	-0.4f,		0.0f,			0.0f,	1.0f,	0.0f,

		0.2f,	 0.4f,		0.0f,			1.0f,	0.0f,	1.0f,
		0.2f,	-0.4f,		0.0f,			1.0f,	0.0f,	1.0f,			//Comeinza la C
		0.3f,	 0.4f,		0.0f,			1.0f,	0.0f,	1.0f,

		0.3f,	 0.4f,		0.0f,			1.0f,	0.0f,	1.0f,
		0.3f,	-0.4f,		0.0f,			1.0f,	0.0f,	1.0f,
		0.2f,	-0.4f,		0.0f,			1.0f,	0.0f,	1.0f,

		0.3f,	 0.3f,		0.0f,			1.0f,	0.0f,	1.0f,
		0.3f,	 0.4f,		0.0f,			1.0f,	0.0f,	1.0f,
		0.6f,	 0.4f,		0.0f,			1.0f,	0.0f,	1.0f,

		0.6f,	 0.4f,		0.0f,			1.0f,	0.0f,	1.0f,
		0.6f,	 0.3f,		0.0f,			1.0f,	0.0f,	1.0f,
		0.3f,	 0.3f,		0.0f,			1.0f,	0.0f,	1.0f,

		0.3f,	-0.3f,		0.0f,			1.0f,	0.0f,	1.0f,
		0.3f,	-0.4f,		0.0f,			1.0f,	0.0f,	1.0f,
		0.6f,	-0.4f,		0.0f,			1.0f,	0.0f,	1.0f,

		0.6f,	-0.4f,		0.0f,			1.0f,	0.0f,	1.0f,
		0.6f,	-0.3f,		0.0f,			1.0f,	0.0f,	1.0f,		//Termina C
		0.3f,	-0.3f,		0.0f,			1.0f,	0.0f,	1.0f,


	};
	MeshColor* letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras, 324);		//En este ejemplo es filas -> * columnas ^
	meshColorList.push_back(letras);


}


void CreateShaders()
{
	///Aqui se agregan los shaders que suare
	Shader* shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide					0
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);													//1
	shaderList.push_back(*shader2);

	//AGREGADOS

	Shader* shader3 = new Shader();//shader para usar color como parte del VAO: letras 
	shader3->CreateFromFiles(vShaderAzulF, fShaderAzulF);								//Azul				2
	shaderList.push_back(*shader3);

	Shader* shader4 = new Shader();//shader para usar color como parte del VAO: letras 
	shader4->CreateFromFiles(vShaderROJO, fShaderROJO);										//ROJO			3
	shaderList.push_back(*shader4);

	Shader* shader5 = new Shader();//shader para usar color como parte del VAO: letras 
	shader5->CreateFromFiles(vShaderVerdeC, fShaderVerdeC);										//verde  claro			4
	shaderList.push_back(*shader5);

	Shader* shader6 = new Shader();//shader para usar color como parte del VAO: letras 
	shader6->CreateFromFiles(vShaderVerdeF, fShaderVerdeF);										//Verde oscuro			5
	shaderList.push_back(*shader6);

	Shader* shader7 = new Shader();//shader para usar color como parte del VAO: letras 
	shader7->CreateFromFiles(vShaderCafe, fShaderCafe);										//Café					6
	shaderList.push_back(*shader7);

}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearCuboVerdeC();	//indice 2											AGREGADOOO
	CrearCuboCafe();		// indice 3
	CreaPiramideVerde();	// indice 4
	CrearLetrasyFiguras(); //INDICE 5 en mesh color list
	CreateShaders();
	GLuint uniformProjection = 0;		//Variables de tipo entero sin signo
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);	//Aqui idnicamos que veremos una proyección ortogonal, que es en 2D, Aqui el valor de Z lo vuelve plano
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f), mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	//Primer argumento angulo de visio, los otros ancho y alto, finalmente los valores de Z,Esta es la matriz mas similir a nuestra vista humana


//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad el pipe es para separar datos
		
		
				//Figuras de la casa 
		
		
		//Para el cubo y la pirámide se usa el primer set de shaders con índice 0 en ShaderList
		shaderList[3].useShader();		//Con este ponemso que colro de lso shader cremaos usaremos
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		//angulo += 0.01;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas}
		
		//Dibuja cubo Rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.0f, -0.5f, -3.0f));	//Sube, baja y mueve la posición de la figura		Eje x lo desplaza izq a der
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 0.0f, 0.0f));	//Le decimos al rededor de que eje queremos mover el objeto
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();	//Manda la figura con el indice 1	que en este caso es el cubo
		
		
		//Al poner esto de shader list cambiamos el color con el índice qu queramos en la parte del shader list
		
//Para el cubo y la pirámide se usa el primer set de shaders con índice 0 en ShaderList
		shaderList[2].useShader();		//Con este ponemso que colro de lso shader cremaos usaremos
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		//angulo += 0.01;
		
		//Crea triángulo		AZUL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.0f, 0.5f, -2.0f));	//Sube, baja y mueve la posición de la figura
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));	//Le decimos al rededor de que eje queremos mover el objeto
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();	//Manda la figura con el indice 1 que en este caso es la piramide
		
		
		
		
		
		//la pirámide se usa el primer set de shaders con índice 0 en ShaderList
		shaderList[5].useShader();		//Con este ponemso que colro de lso shader cremaos usaremos
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		//angulo += 0.01;
		//Crea Piramide		Verde fuerte 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(.8f, -0.6f, -3.0f));	//Sube, baja y mueve la posición de la figura
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));	//Le decimos al rededor de que eje queremos mover el objeto
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[4]->RenderMesh();	//Manda la figura con el indice 1 que en este caso es la piramide
		
		//Crea Piramide		Verde fuerte 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.8f, -0.6f, -3.0f));	//Sube, baja y mueve la posición de la figura
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));	//Le decimos al rededor de que eje queremos mover el objeto
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[4]->RenderMesh();	//Manda la figura con el indice 1 que en este caso es la piramide
		
		
		
		
		
		//Para el cubo y la pirámide se usa el primer set de shaders con índice 0 en ShaderList
		shaderList[4].useShader();		//Con este ponemso que colro de lso shader cremaos usaremos
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		//angulo += 0.01;
		
		//Crea Cubo verde
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.0f, -0.85f, -2.0f));	//Sube, baja y mueve la posición de la figura
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));	//Le decimos al rededor de que eje queremos mover el objeto
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[2]->RenderMesh();	//Manda la figura con el indice 1 que en este caso es la piramide
		
		
		//Para el cubo VERDE
		shaderList[4].useShader();		//Con este ponemso que colro de lso shader cremaos usaremos
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		//angulo += 0.01;
		
		//Crea Cubo verde izq
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.25f, -0.3f, -2.0f));	//Sube, baja y mueve la posición de la figura
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));	//Le decimos al rededor de que eje queremos mover el objeto
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[2]->RenderMesh();	//Manda la figura con el indice 1 que en este caso es la piramide
		
		
		//Para el cubo VERDE
		shaderList[4].useShader();		//Con este ponemso que colro de lso shader cremaos usaremos
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		//angulo += 0.01;
		
		//Crea Cubo verde DER
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.25f, -0.3f, -2.0f));	//Sube, baja y mueve la posición de la figura
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));	//Le decimos al rededor de que eje queremos mover el objeto
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[2]->RenderMesh();	//Manda la figura con el indice 1 que en este caso es la piramide
		
		
		//Para el cubo Cafe der
		shaderList[6].useShader();		//Con este ponemso que colro de lso shader cremaos usaremos
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		//angulo += 0.01;
		
		//Crea Cubo cafe der
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.8f, -0.9f, -3.0f));	//Sube, baja y mueve la posición de la figura
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));	//Le decimos al rededor de que eje queremos mover el objeto
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[3]->RenderMesh();	//Manda la figura con el indice 1 que en este caso es la piramide
		
		
		//Para el cubo CAFE izq
		shaderList[6].useShader();		//Con este ponemso que colro de lso shader cremaos usaremos
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		angulo += 0.0;
		
		//Crea Cubo cafe izq
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.8f, -0.9f, -3.0f));	//Sube, baja y mueve la posición de la figura
		model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));	//Le decimos al rededor de que eje queremos mover el objeto
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[3]->RenderMesh();	//Manda la figura con el indice 1 que en este caso es la piramide
		
		
				//TERMINAN FIGURAS DE LA CASA




				//AQUI EMPIEZAN LAS LETRAS
		
				//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		//shaderList[1].useShader();
		//uniformModel = shaderList[1].getModelLocation();
		//uniformProjection = shaderList[1].getProjectLocation();
		//
		////Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));	//Le decimos al rededor de que eje queremos ver
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[0]->RenderMeshColor();		//Se usa el 0 en mesh Color list porque no hay otra figura que use esta parte


				//AQUI TERMINAN LAS LETRAS




		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
