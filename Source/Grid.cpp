#define GLEW_STATIC 1   
#include <GL/glew.h>    

#include <GLFW/glfw3.h> 

#include <glm/glm.hpp> 

#include "Grid.h"

Grid::Grid()
{
	gridTexture = 0;
	
}


int Grid::GridVertexBufferObject()
{
	// A vertex is a point on a polygon, it contains positions and other data (eg: colors)
	// Create a vertex array
	GLuint vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);


	// Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
	GLuint vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertexArray), lineVertexArray, GL_STATIC_DRAW);

	// Specify where the data is in the VAO – this allows OpenGL to bind data to vertex shader attributes
	glVertexAttribPointer(0, // attribute 0 matches aPos in Vertex Shader
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		2 * sizeof(glm::vec3), // stride - each vertex contain 2 vec3 (position, color)
		(void*)0 // array buffer offset
	);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, // attribute 1 matches aColor in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		2 * sizeof(glm::vec3),
		(void*)sizeof(glm::vec3) // color is offseted a vec3 (comes after position)
	);
	glEnableVertexAttribArray(1);

	return vertexBufferObject;
}

int Grid::TexturedGridVertexBufferObject()
{
	// A vertex is a point on a polygon, it contains positions and other data (eg: colors)
	// Create a vertex array
	GLuint vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);


	// Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
	GLuint vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texturedGridVertexArray), texturedGridVertexArray, GL_STATIC_DRAW);

	// Specify where the data is in the VAO – this allows OpenGL to bind data to vertex shader attributes
	glVertexAttribPointer(0, // attribute 0 matches aPos in Vertex Shader
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		sizeof(TextureLoader::TexturedVertex), // stride - each vertex contain 2 vec3 (position, color)
		(void*)0 // array buffer offset
	);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, // attribute 1 matches aColor in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(TextureLoader::TexturedVertex),
		(void*)sizeof(glm::vec3) // color is offseted a vec3 (comes after position)
	);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, // attribute 1 matches aColor in Vertex Shader
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(TextureLoader::TexturedVertex),
		(void*)(2 * sizeof(glm::vec3)) // uv is offseted 2 * vec3 (comes after position and color)
	);

	glEnableVertexAttribArray(2);

	return vertexBufferObject;
}

void Grid::generateDefaultVertices()
{
	/*= {

	glm::vec3(-1.0f, 0.0f, 0.0f), // First x vertice
	glm::vec3(1.0f, 1.0f, 1.0f), // First x vertice color

	glm::vec3(1.0f, 0.0f, 0.0f), // Second x vertice
	glm::vec3(1.0f, 1.0f, 1.0f), // Second x vertice color

	glm::vec3(0.0f, 0.0f, 1.0f), // First z vertice
	glm::vec3(1.0f, 1.0f, 1.0f), // First z vertice color

	glm::vec3(0.0f, 0.0f, -1.0f), // Second z vertice
	glm::vec3(1.0f, 1.0f, 1.0f), // Second z vertice color

	}; */

	float offset = 2.0;
	float x = 1.0;
	float y = 0.0;
	float z = -1.0;

	for (int i = 0; i < 8; i++)
	{
		float f = 0.0f;

		switch (i % 8)
		{
		case 0:


			for (int j = 0; j < 50; j++)
			{
				f = (float)j;
				x = -50.0;
				y = 0.0;
				z = (f * offset);
				lineVertexArray[(j) * 8] = glm::vec3(x, y, z);
			}
			break;

		case 1: case 3: case 5: case 7:

			for (int j = 0; j < 50; j++)
			{
				x = 1.0;
				y = 1.0;
				z = 1.0;
				lineVertexArray[i + (j * 8)] = glm::vec3(x, y, z);
			}
			break;

		case 2:

			for (int j = 0; j < 50; j++)
			{
				f = (float)j;
				x = 50.0;
				y = 0.0;
				z = (f * offset);
				lineVertexArray[i + ((j) * 8)] = glm::vec3(x, y, z);
			}
			break;

		case 4:

			for (int j = 0; j < 50; j++)
			{
				f = (float)j;
				x = -50.0f + (f * offset);
				y = 0.0;
				z = 100.0f;
				lineVertexArray[i + ((j) * 8)] = glm::vec3(x, y, z);

				//lineVertexArray[i + (j *8)] = glm::vec3(0.0f, 0.0f, 1.0f);
			}
			break;

		case 6:

			for (int j = 0; j < 50; j++)
			{
				f = (float)j;
				x = -50.0f + (f * offset);
				y = 0.0;
				z = 0.0f;
				lineVertexArray[i + ((j) * 8)] = glm::vec3(x, y, z);

				//lineVertexArray[i + (j * 8)] = glm::vec3(0.0f, 0.0f, -1.0f);
			}
			break;

		default:
			break;

		}
	}
}

/*void Grid::generateTexturedVertices()
{
	generateDefaultVertices();

	for (int i = 0; i < 200; i++) // texturedCubeVertexArrayCounter
	{
		
		
			texturedCubeVertexArray[i].position = lineVertexArray[i * 3];
			texturedCubeVertexArray[i].color = lineVertexArray[(i * 3) + 1];

			switch (i % 2)
			{
			case 0:
			{
				texturedCubeVertexArray[i].uv = glm::vec2(0.0f, 0.5f);
				break;
			}

			case 1:
			{
				texturedCubeVertexArray[i].uv = glm::vec2(0.5f, 1.0f);
				break;
			}

			default:
			{
				break;
			}

			}

	}
	
} */
