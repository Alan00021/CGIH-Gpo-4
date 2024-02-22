#pragma once
#include<glew.h>
class Mesh
{
public:
	Mesh();						//Variables publicas que tiene
	void CreateMesh(GLfloat *vertices,unsigned int *indices, unsigned int numOfVertices, unsigned int numberOfIndices);
	void RenderMesh();			//Dibuja por medio del draw arrays
	void ClearMesh();			//Limpia la información creada
	~Mesh();
private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;			//Arreglo de indices

};
class MeshColor
{
public:
	MeshColor();
	void CreateMeshColor(GLfloat *vertices, unsigned int numOfVertices);
	void RenderMeshColor();
	void ClearMeshColor();
	~MeshColor();
private:
	GLuint VAO, VBO, IBO;		///Sobra la variable IBO, se puede quitar sin problema
	GLsizei  vertexCount;
};

