#pragma once


#include "Building.h"

using namespace std;



Building::Building(glm::mat4 worldMatrix)
{
	
	frame = Cube(glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5, 0.0)), glm::mat4(1.0), glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 2.0f, 0.5)));

	roof1 = Cube(glm::translate(glm::mat4(1.0f), glm::vec3(0.25, 1.5, 0.0)),
		glm::rotate(glm::mat4(1.0f), glm::radians(135.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
		glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.125f, 0.5)));

	roof2 = Cube(glm::translate(glm::mat4(1.0f), glm::vec3(-0.25, 1.5, 0.0)),
		glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
		glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.125f, 0.5)));

	frame.parentWorld = worldMatrix;
	roof1.parentWorld = worldMatrix;
	roof2.parentWorld = worldMatrix;
	frame.appendChild(roof1);
	frame.appendChild(roof2);
	createBuilding(worldMatrix);
}


void Building::createBuilding(glm::mat4 worldMatrix)
{

	
	
}

void Building::drawBuilding(glm::mat4 worldMatrix, int shaderProgram, int renderStyle, Cube part, glm::vec3 color)
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

void Building::drawStructure(glm::mat4 worldMatrix, int shaderProgram, int renderStyle, glm::vec3 frameColor, glm::vec3 roof1color, glm::vec3 roof2color)
{
	drawBuilding(worldMatrix, shaderProgram, renderStyle, frame, frameColor );
	drawBuilding(worldMatrix, shaderProgram, renderStyle, roof1, roof1color);
	drawBuilding(worldMatrix, shaderProgram, renderStyle, roof2, roof2color);
}
