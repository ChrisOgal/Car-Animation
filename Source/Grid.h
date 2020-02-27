#pragma once

#define GLEW_STATIC 1   
#include <GL/glew.h>    

#include <GLFW/glfw3.h> 

#include <glm/glm.hpp> 

#include "\Users\chris\Documents\School\comp 371\Assignment#2_40025085\Assignment 1\Assignment 1\VS2017\TextureLoader.h"


class Grid {



public:
	
	GLuint gridTexture;
	glm::vec3 lineVertexArray[400];
	TextureLoader::TexturedVertex texturedGridVertexArray[36] = {  // position,                            color
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

	Grid();
	int GridVertexBufferObject();
	int TexturedGridVertexBufferObject();
	void generateDefaultVertices();
	//void generateTexturedVertices();


	


};