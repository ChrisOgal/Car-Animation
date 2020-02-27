
#pragma once


#include "Tree.h"

using namespace std;

Tree::Tree(glm::mat4 worldMatrix)
{
	Cube trunk = Cube(glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5, 0.0)), glm::mat4(1.0), glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 2.0f, 0.5)));
	Cube green1 = Cube(glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 1.0, -1.0)), glm::mat4(1.0), glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.375f, 0.5)));
	Cube green2 = Cube(glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 1.0, 2.0)), glm::mat4(1.0), glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.375f, 0.5)));



	trunk.parentWorld = worldMatrix;
	green1.parentWorld = trunk.localWorld;
	green2.parentWorld = trunk.localWorld;
	trunk.appendChild(green1);
	trunk.appendChild(green2);
}

void Tree::createTree(glm::mat4 worldMatrix)
{
	
}

void Tree::drawTree(glm::mat4 worldMatrix, int shaderProgram, int renderStyle, Cube part, glm::vec3 color)
{
	//Scaling Matrix to give a uniform size for all the wheels


	//Translation Matrix to move the wheel to the correct position on the car.


	//Done in the order of scale, rotate then translate

	part.generateLocalWorldMatrix(part.parentWorld, part.localTranslate, part.localRotate, part.localScale);

	worldMatrix = part.localWorld;


	GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);

	glBindVertexArray(0);
	part.cvo = part.cubeVertexBufferObject(color);
	//wheel.cvo = wheel.TexturedCubeVertexBufferObject();
	glBindBuffer(GL_ARRAY_BUFFER, part.cvo);
	switch (renderStyle)
	{
	case 1:
		glDrawArrays(GL_POINTS, 0, 36);
		break;

	case 2:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_QUADS, 0, 24);
		break;

	case 3:
		glDrawArrays(GL_TRIANGLES, 0, 360);
		break;
	}
}

void Tree::drawPlant(glm::mat4 worldMatrix, int shaderProgram, int renderStyle, glm::vec3 frameColor, glm::vec3 roof1color, glm::vec3 roof2color)
{
	drawTree(worldMatrix, shaderProgram, renderStyle, trunk, frameColor);
	drawTree(worldMatrix, shaderProgram, renderStyle, green1, roof1color);
	drawTree(worldMatrix, shaderProgram, renderStyle, green2, roof2color);
}
