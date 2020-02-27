#pragma once


#include <GL/glew.h>    

#include <GLFW/glfw3.h> 

#include <glm/glm.hpp>  
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "Cube.h"

using namespace std;

// Class that will handle the generation of cars

class Car{

public:

	Cube body;
	Cube roof;
	Cube bonnet;
	Cube trunk;
	Cube frontLeft;
	Cube frontRight;
	Cube backRight;
	Cube backLeft;
	Cube rightFrontLight;
	Cube leftFrontLight;
	Cube leftRearLight;
	Cube rightRearLight;
	glm::mat4 defaultBodyTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.35f, 0.5f));
	glm::mat4 defaultBodyRotate = glm::mat4(1.0f);
	glm::mat4 defaultBodyScale = glm::scale(glm::mat4(1.0f), glm::vec3(1.05f, 0.5f, 0.5f));
	glm::vec3 mPosition;
	glm::vec3 mVelocity;


	Car();

	Car(Car sampleCar, glm::vec3 position, glm::vec3 velocity);
	Car(Cube body, Cube roof, Cube bonnet, Cube trunk, Cube frontleft, Cube frontRight, Cube backRight, Cube backLeft);

	int lightVertexBufferObject(glm::vec3 leftLight, glm::vec3 rightLight, glm::vec3 color);

	void generateCar();

	void drawBody(glm::mat4 worldMatrix, int shaderProgram, int renderStyle);

	void drawRoof(glm::mat4 worldMatrix, int shaderProgram, int renderStyle);

	void drawBonnet(glm::mat4 worldMatrix, int shaderProgram, int renderStyle);

	void drawTrunk(glm::mat4 worldMatrix, int shaderProgram, int renderStyle);

	void drawWheel(glm::mat4 worldMatrix, int shaderProgram, int renderStyle, Cube wheel);

	void drawLight(glm::mat4 worldMatrix, Cube parent, int shaderProgram, int renderStyle, Cube light);

	void drawAllLights(glm::mat4 worldMatrix, int shaderProgram, int renderStyle);

	void drawAllWheels(glm::mat4 worldMatrix, int shaderProgram, int renderStyle);

	void drawChassis(glm::mat4 worldMatrix, int shaderProgram, int renderStyle);

	void updateChassis();

	void updateWheels();

	void update(float dt);
};