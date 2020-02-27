#pragma once

#include <GL/glew.h>    

#include <GLFW/glfw3.h> 

#include <glm/glm.hpp>  
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "TextureLoader.h"
#include "BSpline.h"

using namespace std;

//The cube class that will form the basic components of the car. Will contain pointers to any dependent entities in the hierachial model.


class Cube {


public:

	
	glm::mat4 localWorld;
	glm::mat4 parentWorld;
	glm::mat4 localScale;
	glm::mat4 localRotate;
	glm::mat4 localTranslate;
	vector<Cube> children;
	vector<TextureLoader::TexturedVertex> texturedCurveVertexArray;
	int cvo;
	GLuint customTexture;
	glm::vec3 vertexArray[108] =
	{

		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(1.0f, 0.0f, 0.0f), //left - red
		glm::normalize(glm::vec3(-0.5f, -0.5f, -0.5f)),
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::normalize(glm::vec3(-0.5f, -0.5f, 0.5f)),
		glm::vec3(-0.5f, 0.5f, 0.5f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::normalize(glm::vec3(-0.5f, 0.5f, 0.5f)),

		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::normalize(glm::vec3(-0.5f, -0.5f, -0.5f)),
		glm::vec3(-0.5f, 0.5f, 0.5f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::normalize(glm::vec3(-0.5f, 0.5f, 0.5f)),
		glm::vec3(-0.5f, 0.5f, -0.5f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::normalize(glm::vec3(-0.5f, 0.5f, -0.5f)),

		glm::vec3(0.5f, 0.5f, -0.5f),
		glm::vec3(0.0f, 0.0f, 1.0f), // far - blue
		glm::normalize(glm::vec3(0.5f, 0.5f, -0.5f)),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::normalize(glm::vec3(-0.5f, -0.5f, -0.5f)),
		glm::vec3(-0.5f, 0.5f, -0.5f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::normalize(glm::vec3(-0.5f, 0.5f, -0.5f)),

		glm::vec3(0.5f, 0.5f, -0.5f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::normalize(glm::vec3(0.5f, 0.5f, -0.5f)),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::normalize(glm::vec3(0.5f, -0.5f, -0.5f)),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::normalize(glm::vec3(-0.5f, -0.5f, -0.5f)),

		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(0.0f, 1.0f, 1.0f), // bottom - turquoise
		glm::normalize(glm::vec3(0.5f, -0.5f, 0.5f)),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(0.0f, 1.0f, 1.0f),
		glm::normalize(glm::vec3(-0.5f, -0.5f, -0.5f)),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.0f, 1.0f, 1.0f),
		glm::normalize(glm::vec3(0.5f, -0.5f, -0.5f)),

		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(0.0f, 1.0f, 1.0f),
		glm::normalize(glm::vec3(0.5f, -0.5f, 0.5f)),
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(0.0f, 1.0f, 1.0f),
		glm::normalize(glm::vec3(-0.5f, -0.5f, 0.5f)),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(0.0f, 1.0f, 1.0f),
		glm::normalize(glm::vec3(-0.5f, -0.5f, -0.5f)),

		glm::vec3(-0.5f, 0.5f, 0.5f),
		glm::vec3(1.0f, 1.0f, 1.0f), // near - green
		glm::normalize(glm::vec3(-0.5f, 0.5f, 0.5f)),
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::normalize(glm::vec3(-0.5f, -0.5f, 0.5f)),
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::normalize(glm::vec3(0.5f, -0.5f, 0.5f)),

		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::normalize(glm::vec3(0.5f, 0.5f, 0.5f)),
		glm::vec3(-0.5f, 0.5f, 0.5f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::normalize(glm::vec3(-0.5f, 0.5f, 0.5f)),
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::normalize(glm::vec3(0.5f, -0.5f, 0.5f)),

		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(1.0f, 0.0f, 1.0f), // right - purple
		glm::normalize(glm::vec3(0.5f, 0.5f, 0.5f)),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(1.0f, 0.0f, 1.0f),
		glm::normalize(glm::vec3(0.5f, -0.5f, -0.5f)),
		glm::vec3(0.5f, 0.5f, -0.5f),
		glm::vec3(1.0f, 0.0f, 1.0f),
		glm::normalize(glm::vec3(0.5f, 0.5f, -0.5f)),

		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(1.0f, 0.0f, 1.0f),
		glm::normalize(glm::vec3(0.5f, -0.5f, -0.5f)),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(1.0f, 0.0f, 1.0f),
		glm::normalize(glm::vec3(0.5f, 0.5f, 0.5f)),
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(1.0f, 0.0f, 1.0f),
		glm::normalize(glm::vec3(0.5f, -0.5f, 0.5f)),

		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(1.0f, 1.0f, 0.0f), // top - yellow
		glm::normalize(glm::vec3(0.5f, 0.5f, 0.5f)),
		glm::vec3(0.5f, 0.5f, -0.5f),
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::normalize(glm::vec3(0.5f, 0.5f, -0.5f)),
		glm::vec3(-0.5f, 0.5f, -0.5f),
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::normalize(glm::vec3(-0.5f, 0.5f, -0.5f)),

		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::normalize(glm::vec3(0.5f, 0.5f, 0.5f)),
		glm::vec3(-0.5f, 0.5f, -0.5f),
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::normalize(glm::vec3(-0.5f, 0.5f, -0.5f)),
		glm::vec3(-0.5f, 0.5f, 0.5f),
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::normalize(glm::vec3(-0.5f, 0.5f, 0.5f))
	};
	
	TextureLoader::TexturedVertex texturedCubeVertexArray[36] = {  // position,                            color
		TextureLoader::TexturedVertex(glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)), //left - red
		TextureLoader::TexturedVertex(glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)),
		TextureLoader::TexturedVertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)),

		TextureLoader::TexturedVertex(glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)),
		TextureLoader::TexturedVertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)),
		TextureLoader::TexturedVertex(glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)),

		TextureLoader::TexturedVertex(glm::vec3(0.5f, 0.5f,-0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)), // far - blue
		TextureLoader::TexturedVertex(glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
		TextureLoader::TexturedVertex(glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)),

		TextureLoader::TexturedVertex(glm::vec3(0.5f, 0.5f,-0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)),
		TextureLoader::TexturedVertex(glm::vec3(0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
		TextureLoader::TexturedVertex(glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)),

		TextureLoader::TexturedVertex(glm::vec3(0.5f,-0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)), // bottom - turquoise
		TextureLoader::TexturedVertex(glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
		TextureLoader::TexturedVertex(glm::vec3(0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)),

		TextureLoader::TexturedVertex(glm::vec3(0.5f,-0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)),
		TextureLoader::TexturedVertex(glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)),
		TextureLoader::TexturedVertex(glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)),

		TextureLoader::TexturedVertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)), // near - green
		TextureLoader::TexturedVertex(glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)),
		TextureLoader::TexturedVertex(glm::vec3(0.5f,-0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),

		TextureLoader::TexturedVertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)),
		TextureLoader::TexturedVertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)),
		TextureLoader::TexturedVertex(glm::vec3(0.5f,-0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),

		TextureLoader::TexturedVertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)), // right - purple
		TextureLoader::TexturedVertex(glm::vec3(0.5f,-0.5f,-0.5f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
		TextureLoader::TexturedVertex(glm::vec3(0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)),

		TextureLoader::TexturedVertex(glm::vec3(0.5f,-0.5f,-0.5f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
		TextureLoader::TexturedVertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)),
		TextureLoader::TexturedVertex(glm::vec3(0.5f,-0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)),

		TextureLoader::TexturedVertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)), // top - yellow
		TextureLoader::TexturedVertex(glm::vec3(0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
		TextureLoader::TexturedVertex(glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)),

		TextureLoader::TexturedVertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)),
		TextureLoader::TexturedVertex(glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)),
		TextureLoader::TexturedVertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f))
	};

	Cube();
	
	Cube(glm::mat4 localTranslate, glm::mat4 localRotate, glm::mat4 localScale);

	void appendChild(Cube child);

	int cubeVertexBufferObject();

	int cubeVertexBufferObject(glm::vec3 colors);

	int TexturedCubeVertexBufferObject();

	int texturedCurveVertexBufferObject();

	void generateLocalWorldMatrix(glm::mat4 parentWorld, glm::mat4 localTranslate, glm::mat4 localRotate, glm::mat4 localScale);

	void setlocalScale(glm::mat4 newScale);

	void generateCurveVertexArray();

	

};

