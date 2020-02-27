#include "Car.h"

using namespace std;

Car::Car()
{
	this->body = Cube(defaultBodyTranslate, defaultBodyRotate, defaultBodyScale);
	this-> roof = Cube(glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.65, 0.0)), glm::mat4(1.0), glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.375f, 0.5)));

	this-> bonnet = Cube(glm::translate(glm::mat4(1.0f), glm::vec3(0.625, 0.0, 0.0)),
		glm::rotate(glm::mat4(1.0f), glm::radians(135.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
		glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.125f, 0.5)));
	this->leftFrontLight = Cube(glm::translate (glm::mat4(1.0f), glm::vec3(0.5, 0.0, (-0.5 + 0.0125))),
									glm::mat4(1.0f),
									glm::scale(glm::mat4(1.0f), glm::vec3(0.125, 0.0625, 0.125)));
	this->rightFrontLight = Cube(glm::translate(glm::mat4(1.0f), glm::vec3(0.5, 0.0, -0.0125)),
		glm::mat4(1.0f),
		glm::scale(glm::mat4(1.0f), glm::vec3(0.125, 0.0625, 0.125)));
		

	this-> trunk = Cube(glm::translate(glm::mat4(1.0f), glm::vec3(-0.625, 0.0, 0.0)),
		glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
		glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.125f, 0.5)));
	this->leftRearLight = Cube(glm::translate(glm::mat4(1.0f), glm::vec3(-0.5, 0.0, (-0.5 + 0.0125))),
								glm::mat4(1.0f),
								glm::scale(glm::mat4(1.0f), glm::vec3(0.125, 0.0625, 0.125)));
	this->rightRearLight = Cube(glm::translate(glm::mat4(1.0f), glm::vec3(-0.5, 0.0, -0.0125)),
								glm::mat4(1.0f),
								glm::scale(glm::mat4(1.0f), glm::vec3(0.125, 0.0625, 0.125)));

	this -> frontRight = Cube(glm::translate(glm::mat4(1.0f), glm::vec3(0.375, -0.5, 0.5)), glm::mat4(1.0), glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0.25)));
	this-> frontLeft = Cube(glm::translate(glm::mat4(1.0f), glm::vec3(0.375, -0.5, -0.5)), glm::mat4(1.0), glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0.25)));
	this-> backLeft = Cube(glm::translate(glm::mat4(1.0f), glm::vec3(-0.375, -0.5, -0.5)), glm::mat4(1.0), glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0.25)));
	this-> backRight = Cube(glm::translate(glm::mat4(1.0f), glm::vec3(-0.375, -0.5, 0.5)), glm::mat4(1.0), glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0.25)));
	generateCar();
}

Car::Car(Car sampleCar, glm::vec3 position, glm::vec3 velocity) : mPosition(position), mVelocity(velocity)
{
	this->body = sampleCar.body;
	this->roof = sampleCar.roof;
	this->bonnet = sampleCar.bonnet;
	this->trunk = sampleCar.trunk;
	this->frontLeft = sampleCar.frontLeft;
	this->frontRight = sampleCar.frontRight;
	this->backRight = sampleCar.backRight;
	this->backLeft = sampleCar.backLeft;
	generateCar();
}

Car::Car(Cube body, Cube roof, Cube bonnet, Cube trunk, Cube frontLeft, Cube frontRight, Cube backRight, Cube backLeft)
{
	this->body = body;
	this->roof = roof;
	this->bonnet = bonnet;
	this->trunk = trunk;
	this->frontLeft = frontLeft;
	this->frontRight = frontRight;
	this->backRight = backRight;
	this->backLeft = backLeft;
	generateCar();
}

int Car::lightVertexBufferObject(glm::vec3 leftLight, glm::vec3 rightLight, glm::vec3 color)
{
	glm::vec3 lightArray[4] = 
	{
		leftLight, color,
		rightLight, color
	};

	GLuint lightVertexArrayObject;
	glGenVertexArrays(1, &lightVertexArrayObject);
	glBindVertexArray(lightVertexArrayObject);


	// Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
	GLuint lightVertexBufferObject;
	glGenBuffers(1, &lightVertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, lightVertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lightArray), lightArray, GL_STATIC_DRAW);

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

	


	return lightVertexBufferObject;
}

void Car::generateCar()
{
	body.appendChild(roof);
	body.appendChild(bonnet);
	body.appendChild(trunk);
	body.appendChild(frontLeft);
	body.appendChild(frontRight);
	body.appendChild(backLeft);
	body.appendChild(backRight);
	bonnet.appendChild(rightFrontLight);
	bonnet.appendChild(leftFrontLight);
	trunk.appendChild(rightRearLight);
	trunk.appendChild(leftRearLight);
}

void Car::drawBody(glm::mat4 worldMatrix, int shaderProgram, int renderStyle)
{
	//Rotation Matrix - Converts degrees to radians and specifies rotation around the x axis for wheels

	//Scaling Matrix to give a uniform size for all the wheels

	//Translation Matrix to move the wheel to the correct position on the car.

	//Done in the order of scale, rotate then translate



	body.generateLocalWorldMatrix(body.parentWorld, body.localTranslate, body.localRotate, body.localScale);

	worldMatrix = body.localWorld;

	for (Cube i : body.children)
	{
		i.parentWorld = body.localWorld;
		i.generateLocalWorldMatrix(i.parentWorld, i.localTranslate, i.localRotate, i.localScale);
	}

	GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);

	glBindVertexArray(0);
	body.cvo = body.cubeVertexBufferObject(glm::vec3(0.0f, 1.0f, 1.0f));
	glBindBuffer(GL_ARRAY_BUFFER, body.cvo);

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
		glDrawArrays(GL_TRIANGLES, 0, 36);
		break;
	}
}

void Car::drawRoof(glm::mat4 worldMatrix, int shaderProgram, int renderStyle)
{
	//Rotation Matrix - Converts degrees to radians and specifies rotation around the x axis for wheels

	//Scaling Matrix to give a uniform size for all the wheels

	//Translation Matrix to move the wheel to the correct position on the car.


	//Done in the order of scale, rotate then translate
	roof.generateLocalWorldMatrix(body.localWorld, roof.localTranslate, roof.localRotate, roof.localScale);

	worldMatrix = roof.localWorld;


	GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);

	glBindVertexArray(0);
	roof.cvo = roof.cubeVertexBufferObject(glm::vec3(0.0f, 1.0f, 1.0f));
	glBindBuffer(GL_ARRAY_BUFFER, roof.cvo);
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
		glDrawArrays(GL_TRIANGLES, 0, 36);
		break;
	}
}

void Car::drawBonnet(glm::mat4 worldMatrix, int shaderProgram, int renderStyle)
{
	//Rotation Matrix - Converts degrees to radians and specifies rotation around the x axis for wheels


	//Scaling Matrix to give a uniform size for all the wheels


	//Translation Matrix to move the wheel to the correct position on the car.



	//Done in the order of scale, rotate then translate

	bonnet.generateLocalWorldMatrix(body.localWorld, bonnet.localTranslate, bonnet.localRotate, bonnet.localScale);

	worldMatrix = bonnet.localWorld;


	GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);

	glBindVertexArray(0);
	bonnet.cvo = bonnet.cubeVertexBufferObject(glm::vec3(0.0f, 1.0f, 1.0f));
	glBindBuffer(GL_ARRAY_BUFFER, bonnet.cvo);
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
		glDrawArrays(GL_TRIANGLES, 0, 36);
		break;
	}
}

void Car::drawTrunk(glm::mat4 worldMatrix, int shaderProgram, int renderStyle)
{
	//Rotation Matrix - Converts degrees to radians and specifies rotation around the x axis for wheels


	//Scaling Matrix to give a uniform size for all the wheels


	//Translation Matrix to move the wheel to the correct position on the car.



	//Done in the order of scale, rotate then translate

	trunk.generateLocalWorldMatrix(body.localWorld, trunk.localTranslate, trunk.localRotate, trunk.localScale);

	worldMatrix = trunk.localWorld;


	GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);

	glBindVertexArray(0);
	trunk.cvo = trunk.cubeVertexBufferObject(glm::vec3(0.0f, 1.0f, 1.0f));
	glBindBuffer(GL_ARRAY_BUFFER, trunk.cvo);
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
		glDrawArrays(GL_TRIANGLES, 0, 36);
		break;
	}
}

void Car::drawWheel(glm::mat4 worldMatrix, int shaderProgram, int renderStyle, Cube wheel)
{
	//Scaling Matrix to give a uniform size for all the wheels


	//Translation Matrix to move the wheel to the correct position on the car.


	//Done in the order of scale, rotate then translate

	wheel.generateLocalWorldMatrix(body.localWorld, wheel.localTranslate, wheel.localRotate, wheel.localScale);

	worldMatrix = wheel.localWorld;


	GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);

	glBindVertexArray(0);
	//wheel.cvo = wheel.cubeVertexBufferObject(glm::vec3(1.0f, 1.0f, 0.0f));
	wheel.cvo = wheel.TexturedCubeVertexBufferObject();
	glBindBuffer(GL_ARRAY_BUFFER, wheel.cvo);
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

void Car::drawLight(glm::mat4 worldMatrix, Cube parent, int shaderProgram, int renderStyle, Cube light)
{
	//Scaling Matrix to give a uniform size for all the wheels


	//Translation Matrix to move the wheel to the correct position on the car.


	//Done in the order of scale, rotate then translate

	light.generateLocalWorldMatrix(parent.localWorld, light.localTranslate, light.localRotate, light.localScale);

	worldMatrix = light.localWorld;


	GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);

	glBindVertexArray(0);
	//wheel.cvo = wheel.cubeVertexBufferObject(glm::vec3(1.0f, 1.0f, 0.0f));
	light.cvo = light.cubeVertexBufferObject();
	glBindBuffer(GL_ARRAY_BUFFER, light.cvo);
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

void Car::drawAllLights(glm::mat4 worldMatrix, int shaderProgram, int renderStyle)
{
	drawLight(worldMatrix, bonnet, shaderProgram, renderStyle, leftFrontLight);
	drawLight(worldMatrix, bonnet, shaderProgram, renderStyle, rightFrontLight);
	drawLight(worldMatrix, trunk, shaderProgram, renderStyle, leftRearLight);
	drawLight(worldMatrix, trunk, shaderProgram, renderStyle, rightRearLight);

}

void Car::drawAllWheels(glm::mat4 worldMatrix, int shaderProgram, int renderStyle)
{
	drawWheel(worldMatrix, shaderProgram, renderStyle, frontLeft);
	drawWheel(worldMatrix, shaderProgram, renderStyle, frontRight);
	drawWheel(worldMatrix, shaderProgram, renderStyle, backLeft);
	drawWheel(worldMatrix, shaderProgram, renderStyle, backRight);
}

void Car::drawChassis(glm::mat4 worldMatrix, int shaderProgram, int renderStyle)
{
	drawBody(worldMatrix, shaderProgram, renderStyle);
	drawRoof(worldMatrix, shaderProgram, renderStyle);
	drawBonnet(worldMatrix, shaderProgram, renderStyle);
	drawTrunk(worldMatrix, shaderProgram, renderStyle);
	drawAllLights(worldMatrix, shaderProgram, renderStyle);
}

void Car::update(float dt)
{
	mPosition += mVelocity * dt;
}
