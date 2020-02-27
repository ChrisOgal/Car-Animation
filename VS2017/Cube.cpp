#include "Cube.h"


using namespace std;


//Generates a cube with assigned colors for each face


Cube::Cube()
{
	this->localWorld = glm::mat4(1.0);
	this->parentWorld = glm::mat4(1.0);
	this->localRotate = glm::mat4(1.0);
	this->localScale = glm::mat4(1.0);
	this->localTranslate = glm::mat4(1.0);
	this->children;
	this->customTexture = 0;
	
}


Cube::Cube(glm::mat4 localTranslate, glm::mat4 localRotate, glm::mat4 localScale)
{
	this->localRotate = localRotate;
	this->localScale = localScale;
	this->localTranslate = localTranslate;
	this->localWorld = glm::mat4(1.0);
	this->parentWorld = glm::mat4(1.0);
	this->children;
	this->customTexture = 0;
	
}

void Cube::appendChild(Cube child)
{
	this->children.push_back(child);
	child.parentWorld = this->localWorld;
	
}

int Cube::cubeVertexBufferObject()
{
	

	GLuint cubeVertexArrayObject;
	glGenVertexArrays(1, &cubeVertexArrayObject);
	glBindVertexArray(cubeVertexArrayObject);


	// Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
	GLuint cubeVertexBufferObject;
	glGenBuffers(1, &cubeVertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

	// Specify where the data is in the VAO – this allows OpenGL to bind data to vertex shader attributes
	glVertexAttribPointer(0, // attribute 0 matches aPos in Vertex Shader
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		3 * sizeof(glm::vec3), // stride - each vertex contain 3 vec3 (position, color, normal)
		(void*)0 // array buffer offset
	);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, // attribute 1 matches aColor in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(glm::vec3),
		(void*)sizeof(glm::vec3) // color is offseted a vec3 (comes after position)
	);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, // attribute 2 matches aNormal in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(glm::vec3),
		(void*)(2 * sizeof(glm::vec3)) // normal is offseted 2 vec3 (comes after color)
	);
	glEnableVertexAttribArray(2);


	return cubeVertexBufferObject;
}

int Cube::cubeVertexBufferObject(glm::vec3 colors)
{
	

	int i = 0;
	while (i < (sizeof(vertexArray)/sizeof(vertexArray[0])))
	{
		if ((i % 3) == 1)
		{
			vertexArray[i][0] = colors[0];
			vertexArray[i][1] = colors[1];
			vertexArray[i][2] = colors[2];
		}
		i++;
	}

	GLuint cubeVertexArrayObject;
	glGenVertexArrays(1, &cubeVertexArrayObject);
	glBindVertexArray(cubeVertexArrayObject);


	// Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
	GLuint cubeVertexBufferObject;
	glGenBuffers(1, &cubeVertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

	// Specify where the data is in the VAO – this allows OpenGL to bind data to vertex shader attributes
	glVertexAttribPointer(0, // attribute 0 matches aPos in Vertex Shader
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		3 * sizeof(glm::vec3), // stride - each vertex contain 3 vec3 (position, color, normal)
		(void*)0 // array buffer offset
	);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, // attribute 1 matches aColor in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(glm::vec3),
		(void*)sizeof(glm::vec3) // color is offseted a vec3 (comes after position)
	);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, // attribute 2 matches aNormal in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(glm::vec3),
		(void*)(2*sizeof(glm::vec3)) // normal is offseted 2 vec3 (comes after color)
	);
	glEnableVertexAttribArray(2);
	return cubeVertexBufferObject;
}

int Cube::TexturedCubeVertexBufferObject()
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(texturedCubeVertexArray), texturedCubeVertexArray, GL_STATIC_DRAW);

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

int Cube::texturedCurveVertexBufferObject()
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(texturedCurveVertexArray), &(texturedCurveVertexArray), GL_STATIC_DRAW);

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

	glVertexAttribPointer(2, // attribute 2 matches UV in Vertex Shader
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(TextureLoader::TexturedVertex),
		(void*)(2 * sizeof(glm::vec3)) // uv is offseted 2 * vec3 (comes after position and color)
	);

	glEnableVertexAttribArray(2);

	return vertexBufferObject;
}

 void Cube::generateLocalWorldMatrix(glm::mat4 parentWorld, glm::mat4 localTranslate, glm::mat4 localRotate, glm::mat4 localScale)
{
	 localWorld = parentWorld * localTranslate * localRotate * localScale;
}

 void Cube::setlocalScale(glm::mat4 newScale)
 {
	 this->localScale = newScale;
 }

 /*void Cube::generateCurveVertexArray()
 {

	 vector<glm::vec3> curvedPoints;
	 vector<glm::vec3> curvedColors;
	 vector<glm::vec2> curvedUVs;
	 glm::vec2 newUV;
	 BSpline::clearSplineGenerator();
	 BSpline::addControlPoints(texturedCubeVertexArray);
	 BSpline::generateSamplePoints();
	 curvedPoints = BSpline::finalSamplePoints();

	 for (int i = 0; i < 36; i++)
	 {
		 for (int j = 0; j < 10; j++)
		 {
			 curvedColors.push_back(texturedCubeVertexArray[i].color);
			 newUV.x = (texturedCubeVertexArray[i].uv.x * 0.1 * float(j));
			 newUV.y = (texturedCubeVertexArray[i].uv.y * 0.1 * float(j));
			 curvedUVs.push_back(newUV);

		 }
	 }

	 assert(curvedPoints.size() == curvedColors.size());

	 for (int i = 0; i < curvedPoints.size(); i++)
	 {
		 texturedCurveVertexArray.push_back(TextureLoader::TexturedVertex(curvedPoints[i], curvedColors[i], curvedUVs[i]));
	 } 
	
 }  */

 

