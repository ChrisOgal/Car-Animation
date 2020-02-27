//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 20/06/2019.
//
// Modified by Christopher Idah
//
// Inspired by the following tutorials:
// - https://learnopengl.com/Getting-started/Hello-Window
// - https://learnopengl.com/Getting-started/Hello-Triangle

#include <iostream>
#include <vector>
#include <time.h>
#include <Math.h>
#include <list>



#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
                        // initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp>
#include <FreeImageIO.h> //Import the FreeImage library for texture mapping

//Necessary Local Source Files
#include "\Users\chris\Documents\School\comp 371\Assignment#2_40025085\Assignment 1\Assignment 1\VS2017\Cube.h"
#include "Grid.h"
#include "\Users\chris\Documents\School\comp 371\Assignment#2_40025085\Assignment 1\Assignment 1\VS2017\Car.h"
#include "\Users\chris\Documents\School\comp 371\Assignment#2_40025085\Assignment 1\Assignment 1\VS2017\BSpline.h"
#include "\Users\chris\Documents\School\comp 371\Assignment#2_40025085\Assignment 1\Assignment 1\VS2017\Tree.h"
#include "\Users\chris\Documents\School\comp 371\Assignment#2_40025085\Assignment 1\Assignment 1\VS2017\Building.h"


using namespace  std;




//Input method declarations
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//Various variables to be used through the animation.
float angle = 0;
float rotationSpeed = 720.0f; // 720 degrees/second
float lastFrameTime = glfwGetTime();
int renderStyle = 3;
bool initialMouse = true;
float yaw = -180.0f;
float pitch = 0.0f;
float lastX = 1024.0f / 2.0;
float lastY = 7680. / 2.0;
float cameraSpeed = 2.5;
BSpline path = BSpline();

glm::vec3 cameraPosition = glm::vec3(0.0f, 3.0f, 10.0f); //position
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f); //target
glm::vec3 cameraOrientation(0.0f, 1.0f, 0.0f);  //Orientation
glm::mat4 defaultViewMatrix = glm::lookAt( cameraPosition,
										   cameraTarget,
										   cameraOrientation
										  );
//ISoundEngine *SoundEngine = createIrrKlangDevice();

float fov = 70.0f;
float aspect = 1024.0f / 768.0f;
float near = 0.01f;
float far = 100.0f;

glm::mat4 defaultProjectionMatrix = glm::perspective(fov,
													 aspect,
													  near, far);

Grid x_zGrid = Grid();
Car userCar = Car();

glm::mat4 rotationMatrix = glm::mat4(1.0);
glm::mat4 scalingMatrix = glm::mat4(1.0);
glm::mat4 translationMatrix = glm::mat4(1.0);
glm::mat4 worldMatrix = glm::mat4(1.0);
glm::mat4 viewMatrix = glm::lookAt(cameraPosition,
									cameraTarget,
									cameraOrientation);


glm::mat4 projectionMatrix = glm::perspective(fov,
												aspect,
			
									near, far);

Building building1 = Building(glm::translate(glm::mat4(1.0), glm::vec3(4.0, 0.0, 4.0)));
Building building2 = Building(glm::translate(glm::mat4(1.0), glm::vec3(36.0, 0.0, -12.0)));
Building building3 = Building(glm::translate(glm::mat4(1.0), glm::vec3(-6.0, 0.0, -7.0)));
Building building4 = Building(glm::translate(glm::mat4(1.0), glm::vec3(22.0, 0.0, 5.0)));
Building building5 = Building(glm::translate(glm::mat4(1.0), glm::vec3(-13.0, 0.0, -2.0)));
Building building6 = Building(glm::translate(glm::mat4(1.0), glm::vec3(38.0, 0.0, -36.0)));
Building building7 = Building(glm::translate(glm::mat4(1.0), glm::vec3(50.0, 0.0, 21.0)));
Building building8 = Building(glm::translate(glm::mat4(1.0), glm::vec3(-41.0, 0.0, 44.0)));
Building building9 = Building(glm::translate(glm::mat4(1.0), glm::vec3(17.0, 0.0, -14.0)));
Building building10 = Building(glm::translate(glm::mat4(1.0), glm::vec3(13.0, 0.0, -13.0)));

Tree tree1 = Tree(worldMatrix);


struct PointLight {
	
	glm::vec3 position;
	glm::vec3 color;
	float constant;
	float linear;
	float quadratic;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	PointLight(glm::vec3 position, glm::vec3 color, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
	{
		this->position = position;
		this->color = color;
		this->constant = constant;
		this->linear = linear;
		this->quadratic = quadratic;
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
	}
};



PointLight headLights[4] = 
{
	//front left
PointLight(glm::vec3(userCar.bonnet.localWorld * glm::vec4(0.5, 0.0, (-0.5 + 0.0125), 1.0)), glm::vec3(0.0, 1.0, 1.0), 1.0, 0.9, 0.032, glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.8, 0.8, 0.8), glm::vec3(1.0, 1.0, 1.0)),
	//front right
PointLight(glm::vec3(userCar.bonnet.localWorld * glm::vec4(0.5, 0.0, -0.0125, 1.0)), glm::vec3(0.0, 1.0, 1.0), 1.0, 0.9, 0.032, glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.8, 0.8, 0.8), glm::vec3(1.0, 1.0, 1.0)),
	//rear left
PointLight(glm::vec3(userCar.bonnet.localWorld * glm::vec4(-0.5, 0.0, (-0.5 + 0.0125), 1.0)), glm::vec3(0.0, 1.0, 1.0), 1.0, 0.9, 0.032, glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.8, 0.8, 0.8), glm::vec3(1.0, 1.0, 1.0)),
	//rear right
PointLight(glm::vec3(userCar.bonnet.localWorld * glm::vec4(-0.5, 0.0, -0.0125, 1.0)), glm::vec3(0.0, 1.0, 1.0), 1.0, 0.9, 0.032, glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.8, 0.8, 0.8), glm::vec3(1.0, 1.0, 1.0))

};




glm::vec3 lightInDir = glm::vec3(0.5f,2.0,2.0);

//MVP for the light pass
glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
glm::mat4 depthViewMatrix = glm::lookAt(lightInDir, glm::vec3(0,0,0), glm::vec3(0,1,0));
//glm::mat4 depthModelMatrix = glm::mat4(1.0f);
glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix;

/*""
"vec3 headLightDir = normalize (headLight.position - fragPos);"
""
"theta = dot (headLightDir, normalize(-headLight.direction));"
""
"if (theta > headLight.cutOff)"
"{"
""
"ambient = headLight.ambient;"
""
"diff = max(dot(norm, headLightDir), 0.0);"
"vec3 diffuse = headLight.diffuse * diff;"
""
"reflectDir = reflect(-headLightDir, norm);"
"spec = pow(max(dot(viewDir, reflectDir), 0.0), specularStrength);"
"vec3 specular = headLight.specular * spec;"
""
"float distance = length(headLight.position - fragPos);"
"float attenuation = 1.0/(headLight.constant + headLight.linear * distance + headLight.quadratic * (distance * distance));"
""
"diffuse *= attenuation;"
"specular *= attenuation;"
""
"vec3 headLightResult = ambient + diffuse + specular;"
"FragColor = vec4(headLightResult, 1.0);"
"}"

"else {"
" vec3 result = (ambient + diffuse + specular) * vertexColor;"
" FragColor = vec4(result, 1.0f);"
"}" */

const char* getVertexShaderSource()
{
	return
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;"
		"layout (location = 1) in vec3 aColor;"
		"layout (location = 2) in vec3 aNormal;"
		""
		"uniform mat4 worldMatrix;"
		"uniform mat4 viewMatrix = mat4(1.0);"
		"uniform mat4 projectionMatrix = mat4(1.0);"
		""
		"out vec3 vertexColor;"
		"out vec3 normal;"
		"out vec3 fragPos;"
		"void main()"
		"{"
		" vertexColor = aColor;"
		"mat4 modelViewProjectionMatrix = projectionMatrix * viewMatrix * worldMatrix;"
		" gl_Position = modelViewProjectionMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);"
		"fragPos = vec3(worldMatrix * vec4(aPos, 1.0));"
		" normal = aNormal;"
		"}";
}


const char* getFragmentShaderSource()
{
	return
		"in vec3 vertexColor;"
		"in vec3 normal;"
		"in vec3 fragPos;"
		"out vec4 FragColor;"
		"uniform vec3 lightColor = vec3 (1.0, 1.0, 1.0);"
		"uniform vec3 lightPos = vec3(0.0, 30.0, 0.0);"
		"uniform vec3 viewPos;"
		"void main()"
		"{"
		" float ambientStrength = 0.7;"
		" float specularStrength = 0.9;"
		" vec3 ambient = ambientStrength * lightColor;"
		"vec3 norm = normalize(normal);"
		"vec3 lightDir = normalize(lightPos - fragPos);"
		"vec3 viewDir = normalize(viewPos - fragPos);"
		" vec3 reflectDir = reflect(-lightDir, norm);"
		" float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);"
		" vec3 specular = specularStrength * spec * lightColor;"
		"float diff = max(dot (norm, lightDir), 0.0);"
		"vec3 diffuse = diff * lightColor;"
		" vec3 result = (ambient + diffuse + specular) * vertexColor;"
		" FragColor = vec4(result, 1.0f);"
		"}";
}

const char* getTexturedVertexShaderSource()
{
	
	return
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;"
		"layout (location = 1) in vec3 aColor;"
		"layout (location = 2) in vec2 aUV;"
		""
		"uniform mat4 worldMatrix;"
		"uniform mat4 viewMatrix = mat4(1.0);"  
		"uniform mat4 projectionMatrix = mat4(1.0);"
		""
		"out vec3 vertexColor;"
		"out vec2 vertexUV;"
		""
		"void main()"
		"{"
		"   vertexColor = aColor;"
		"   mat4 modelViewProjection = projectionMatrix * viewMatrix * worldMatrix;"
		"   gl_Position = modelViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);"
		"   vertexUV = aUV;"
		"}";
}

const char* getTexturedFragmentShaderSource()
{
	return
		"#version 330 core\n"
		"in vec3 vertexColor;"
		"in vec2 vertexUV;"
		"uniform sampler2D textureSampler;"
		""
		"out vec4 FragColor;"
		"void main()"
		"{"
		"   vec4 textureColor = texture( textureSampler, vertexUV);"
		"   FragColor = textureColor;"
		"}";
}

const char* getDepthVertexShaderSource()
{
	return
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;"

		
		"uniform mat4 depthMVP;"
		"uniform mat4 worldMatrix;"

		"void main() "
		"{"
		"gl_Position = depthMVP * worldMatrix * vec4(aPos, 1.0);"
		"}";
}

const char* getDepthFragmentShaderSource()
{
	return

		"#version 330 core\n"

		"layout(location = 0) out float fragmentDepth;"

		"void main()"
		"{"
			"fragmentDepth = gl_FragCoord.z;"
		"}";
}


int compileAndLinkShaders(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	// compile and link shader program
	// return shader program id
	// ------------------------------------

	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;

}


vector<float> generateRandomPoint()
{
	float x = 0.0;
	float z = 0.0;

	srand(time(NULL));

	x = (rand() % 50);
	z = (rand() % 50);

	if (x < 25)
	{
		x *= -1;
	}

	if (z < 25)
	{
		z *= -1;
	}

	

	vector<float> result;

	result.push_back(x);
	result.push_back(z);



	return result;
};


void setProjectionMatrix(int shaderProgram, glm::mat4 projectionMatrix)
{
	glUseProgram(shaderProgram);
	GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void setViewMatrix(int shaderProgram, glm::mat4 viewMatrix)
{
	glUseProgram(shaderProgram);
	GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
}

void setWorldMatrix(int shaderProgram, glm::mat4 worldMatrix)
{
	glUseProgram(shaderProgram);
	GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
} 


void setDepthMVP(int shaderProgram, glm::mat4 depthMVP)
{
	glUseProgram(shaderProgram);
	GLuint depthLocation = glGetUniformLocation(shaderProgram, "depthMVP");
	glUniformMatrix4fv(depthLocation, 1, GL_FALSE, &depthMVP[0][0]);
}


int depthMapFrameBufferObject()
{
	GLuint depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);


	const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

	GLuint depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthMap, 0);

	glDrawBuffer(GL_NONE);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;
	else 

	return depthMap;
	
}
int axisVertexBufferObject()
{
	// A vertex is a point on a polygon, it contains positions and other data (eg: colors)
	glm::vec3 axisVertexArray[] = {

		// x y and z axis

		  glm::vec3(1.0f, 0.0f, 0.0f), // x axis origin point
		  glm::vec3(1.0f, 0.0f, 0.0f), // x axis origin color
		  glm::vec3(6.0f, 0.0f, 0.0f), // x axis 5th point
		  glm::vec3(1.0f, 0.0f, 0.0f), // x axis 5th point color

		  glm::vec3(0.0f, 0.0f, 0.0f), // y axis origin point
		  glm::vec3(0.0f, 1.0f, 0.0f), // y axis origin color
		  glm::vec3(0.0f, 5.0f, 0.0f), // y axis 5th point
		  glm::vec3(0.0f, 1.0f, 0.0f), // y axis 5th point color

		  glm::vec3(0.0f, 0.0f, 0.0f), // z axis origin point
		  glm::vec3(0.0f, 0.0f, 1.0f), // z axis origin color
		  glm::vec3(0.0f, 0.0f, 5.0f), // z axis 5th point
		  glm::vec3(0.0f, 0.0f, 1.0f), // z axis 5th point color

	};


	// Create a vertex array
	GLuint axisVertexArrayObject;
	glGenVertexArrays(1, &axisVertexArrayObject);
	glBindVertexArray(axisVertexArrayObject);


	// Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
	GLuint axisVertexBufferObject;
	glGenBuffers(1, &axisVertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, axisVertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(axisVertexArray), axisVertexArray, GL_STATIC_DRAW);

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
	return axisVertexBufferObject;
}

void drawGrid(int shaderProgram, Grid grid)
{

	//Rotation Matrix - Converts degrees to radians and specifies rotation around the x axis for wheels

	//Scaling Matrix to give a uniform size for all the wheels

	//Translation Matrix to move the wheel to the correct position on the car.

	//Done in the order of scale, rotate then translate

	//grid.generateDefaultVertices();

	
		
	scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(100.0f, 0.02f, 100.0f));
	translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.01f, 0.0f));

	worldMatrix = translationMatrix * scalingMatrix;
			
			
			GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);


			glBindVertexArray(0);
			int gbo = grid.TexturedGridVertexBufferObject();
			glBindBuffer(GL_ARRAY_BUFFER, gbo);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		
	
	
}


void drawAxis(int shaderProgram)
{

	//Rotation Matrix - Converts degrees to radians and specifies rotation around the x axis for wheels

	//Scaling Matrix to give a uniform size for all the wheels

	//Translation Matrix to move the wheel to the correct position on the car.

	//Done in the order of scale, rotate then translate

	worldMatrix = glm::mat4(1.0f);

	GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);

	glBindVertexArray(0);
	int abo = axisVertexBufferObject();
	glBindBuffer(GL_ARRAY_BUFFER, abo);
	glDrawArrays(GL_LINES, 0, 6);
}



void drawShadows(int shaderProgram)
{
	setDepthMVP(shaderProgram, depthMVP);
	setWorldMatrix(shaderProgram, worldMatrix);
	glUseProgram(shaderProgram);

	//drawAxis(colorShaderProgram);
	int fbo = depthMapFrameBufferObject();
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	userCar.drawChassis(worldMatrix, shaderProgram, renderStyle);
	userCar.drawAllWheels(worldMatrix, shaderProgram, renderStyle);
} 

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void moveCar(glm::vec3 start, glm::vec3 position, float dt, int shader1, int shader2)
{
	
	float realdt = 0.5*dt;
	

	//current *= realdt;
	//glm::vec3 current = start + ((fin - start) * realdt);

	glm::vec3 current = start + (position * realdt);

	//wheel spin
	angle = (angle + rotationSpeed * dt); // angles in degrees. Conversion follows

			//Rotation Matrix - Converts degrees to radians and specifies rotation around the x axis for wheels
	userCar.frontLeft.localRotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle),
		glm::vec3(0.0f, 0.0f, -1.0f));
	userCar.frontRight.localRotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle),
		glm::vec3(0.0f, 0.0f, -1.0f));
	userCar.backLeft.localRotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle),
		glm::vec3(0.0f, 0.0f, -1.0f));
	userCar.backRight.localRotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle),
		glm::vec3(0.0f, 0.0f, -1.0f));
	userCar.body.localTranslate *= glm::translate(glm::mat4(1.0f), current);


	glm::vec3 cameraSideVector = glm::cross(cameraTarget, glm::vec3(0.0, 1.0, 0.0));
	glm::normalize(cameraSideVector);
	cameraTarget = glm::vec3(userCar.body.localTranslate * glm::vec4(1.0));
	
	//cameraSideVector * realdt
	viewMatrix = glm::lookAt(cameraPosition += current,
			cameraTarget,
			cameraOrientation );

	

	setViewMatrix(shader2, viewMatrix);
	setViewMatrix(shader1, viewMatrix);


	
}



// Compile and link shaders here ...
int colorShaderProgram;
int texturedShaderProgram;
int depthShaderProgram;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (initialMouse)
	{
		lastX = xpos;
		lastY = ypos;
		initialMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.5f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraTarget = glm::normalize(front);

	viewMatrix = glm::lookAt(cameraPosition, cameraTarget, cameraOrientation);
	setViewMatrix(texturedShaderProgram, viewMatrix);
	setViewMatrix(colorShaderProgram, viewMatrix);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;

	projectionMatrix = glm::perspective(glm::radians(fov), aspect, near, far);

	setProjectionMatrix(texturedShaderProgram, projectionMatrix);
	setProjectionMatrix(colorShaderProgram, projectionMatrix);
}

int main(int argc, char*argv[])
{
    // Initialize GLFW and OpenGL version
    glfwInit();

#if defined(PLATFORM_OSX)	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
	// On windows, we set OpenGL version to 2.1, to support more hardware
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#endif

    // Create Window and rendering context using GLFW, resolution is 1024x768
    GLFWwindow* window = glfwCreateWindow(1024, 768, "Comp371 - Assignment 1", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSetWindowSizeLimits(window, 0, 0, 1920, 1080);
	glViewport(0,0,1024,768);
	
    glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

	

	//Load textures

	GLuint grassTextureID = TextureLoader::loadTexture("../Assets/Textures/grass.jpg");
	GLuint wheelTextureID = TextureLoader::loadTexture("../Assets/Textures/wheel.jpg");

	x_zGrid.gridTexture = grassTextureID;
	userCar.frontLeft.customTexture = wheelTextureID;
	userCar.frontRight.customTexture = wheelTextureID;
	userCar.backLeft.customTexture = wheelTextureID;
	userCar.backRight.customTexture = wheelTextureID;
	
	//camera variables
	float cameraAngularSpeed = 60.0f;

	//Movement variables
	bool move = false;
	int k = 0;

    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    
	// Compile and link shaders here ...
	colorShaderProgram = compileAndLinkShaders(getVertexShaderSource(), getFragmentShaderSource());
	texturedShaderProgram = compileAndLinkShaders(getTexturedVertexShaderSource(), getTexturedFragmentShaderSource());
	depthShaderProgram = compileAndLinkShaders(getDepthVertexShaderSource(), getDepthFragmentShaderSource());

	int lastNstate = GLFW_RELEASE;
	bool moving = false;
	glm::vec3 startPos = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 turn1 = glm::vec3(5.0, 0.0, -1.25);
	glm::vec3 turn2 = glm::vec3(7.0, 0.0, -3.0);
	glm::vec3 turn3 = glm::vec3(0.0, 0.0, 3.25);
	glm::vec3 finalPos = glm::vec3(-15.0, 0.0, 6.0);
	//glm::vec3 finalPos = glm::vec3(0.0, 0.0, 0.0);
	vector<glm::vec3> control = vector <glm::vec3>();
	control.push_back(startPos);
	control.push_back(turn1);
	control.push_back(turn2);
	control.push_back(turn3);
	control.push_back(finalPos);

	path.addControlPoints(control);
	path.generateSamplePoints();
	vector<glm::vec3> curvedPath = path.finalSamplePoints(); 

    // Entering Main Loop
    while(!glfwWindowShouldClose(window))
    {
		//Enable Backface Culling
		glEnable(GL_CULL_FACE);

		float dt = glfwGetTime() - lastFrameTime;
		lastFrameTime += dt;
		


		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		// Each frame, reset color of each pixel to glClearColor
		glEnable(GL_DEPTH_TEST);

		

		//depth buffer bit
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		if (!moving)

		{
			glUseProgram(colorShaderProgram);
			drawAxis(colorShaderProgram);
			building1.drawStructure(glm::translate(glm::mat4(1.0), glm::vec3(6.0, 0.0, -3.0)), colorShaderProgram, renderStyle, glm::vec3(1.0, 0.0, 1.0), glm::vec3(0.514, 0.234, 0.145), glm::vec3(0.568, 0.998, 0.487));
			building2.drawStructure(glm::translate(glm::mat4(1.0), glm::vec3(22.0, 0.0, 4.0)), colorShaderProgram, renderStyle, glm::vec3(0.25, 0.25, 1.0), glm::vec3(0.459, 0.127, 0.147), glm::vec3(0.987, 0.983, 0.123));
			building3.drawStructure(glm::translate(glm::mat4(1.0), glm::vec3(6.0, 0.0, -3.0)), colorShaderProgram, renderStyle, glm::vec3(0.875, 0.361, 0.982), glm::vec3(0.786, 0.325, 0.651), glm::vec3(0.254, 0.447, 0.998));
			building4.drawStructure(glm::translate(glm::mat4(1.0), glm::vec3(6.0, 0.0, -3.0)), colorShaderProgram, renderStyle, glm::vec3(0.543, 0.564, 0.142), glm::vec3(1.0, 1.0, 0.225), glm::vec3(0.548, 0.237, 0.795));
			building5.drawStructure(glm::translate(glm::mat4(1.0), glm::vec3(6.0, 0.0, -3.0)), colorShaderProgram, renderStyle, glm::vec3(0.846, 0.918, 0.110), glm::vec3(0.254, 0.157, 0.981), glm::vec3(0.982, 0.457, 0.555));
			building6.drawStructure(glm::translate(glm::mat4(1.0), glm::vec3(6.0, 0.0, -3.0)), colorShaderProgram, renderStyle, glm::vec3(1.0, 0.0, 1.0), glm::vec3(0.514, 0.234, 0.145), glm::vec3(0.568, 0.998, 0.487));
			building7.drawStructure(glm::translate(glm::mat4(1.0), glm::vec3(22.0, 0.0, 4.0)), colorShaderProgram, renderStyle, glm::vec3(0.25, 0.25, 1.0), glm::vec3(0.459, 0.127, 0.147), glm::vec3(0.987, 0.983, 0.123));
			building8.drawStructure(glm::translate(glm::mat4(1.0), glm::vec3(6.0, 0.0, -3.0)), colorShaderProgram, renderStyle, glm::vec3(0.875, 0.361, 0.982), glm::vec3(0.786, 0.325, 0.651), glm::vec3(0.254, 0.447, 0.998));
			building9.drawStructure(glm::translate(glm::mat4(1.0), glm::vec3(6.0, 0.0, -3.0)), colorShaderProgram, renderStyle, glm::vec3(0.543, 0.564, 0.142), glm::vec3(1.0, 1.0, 0.225), glm::vec3(0.548, 0.237, 0.795));
			building10.drawStructure(glm::translate(glm::mat4(1.0), glm::vec3(6.0, 0.0, -3.0)), colorShaderProgram, renderStyle, glm::vec3(0.846, 0.918, 0.110), glm::vec3(0.254, 0.157, 0.981), glm::vec3(0.982, 0.457, 0.555));
			userCar.drawChassis(worldMatrix, colorShaderProgram, renderStyle);
			

			glUseProgram(texturedShaderProgram);
			glActiveTexture(GL_TEXTURE0);
			GLuint textureLocation = glGetUniformLocation(texturedShaderProgram, "textureSampler");
			glBindTexture(GL_TEXTURE_2D, userCar.frontLeft.customTexture);
			glUniform1i(textureLocation, 0);
			userCar.drawAllWheels(worldMatrix, texturedShaderProgram, renderStyle);

			glBindTexture(GL_TEXTURE_2D, x_zGrid.gridTexture);
			drawGrid(texturedShaderProgram, x_zGrid);

			//drawShadows(depthShaderProgram);
		}
			
			

		else
		{


		
				moveCar(startPos, curvedPath.at(1) , dt, texturedShaderProgram, colorShaderProgram);
				glUseProgram(colorShaderProgram);
				drawAxis(colorShaderProgram);
				building1.drawStructure(glm::translate(glm::mat4(1.0), glm::vec3(6.0, 0.0, -3.0)), colorShaderProgram, renderStyle, glm::vec3(1.0, 0.0, 1.0), glm::vec3(0.514, 0.234, 0.145), glm::vec3(0.568, 0.998, 0.487));
				building2.drawStructure(glm::translate(glm::mat4(1.0), glm::vec3(22.0, 0.0, 4.0)), colorShaderProgram, renderStyle, glm::vec3(0.25, 0.25, 1.0), glm::vec3(0.459, 0.127, 0.147), glm::vec3(0.987, 0.983, 0.123));
				building3.drawStructure(glm::translate(glm::mat4(1.0), glm::vec3(6.0, 0.0, -3.0)), colorShaderProgram, renderStyle, glm::vec3(0.875, 0.361, 0.982), glm::vec3(0.786, 0.325, 0.651), glm::vec3(0.254, 0.447, 0.998));
				building4.drawStructure(glm::translate(glm::mat4(1.0), glm::vec3(6.0, 0.0, -3.0)), colorShaderProgram, renderStyle, glm::vec3(0.543, 0.564, 0.142), glm::vec3(1.0, 1.0, 0.225), glm::vec3(0.548, 0.237, 0.795));
				building5.drawStructure(glm::translate(glm::mat4(1.0), glm::vec3(6.0, 0.0, -3.0)), colorShaderProgram, renderStyle, glm::vec3(0.846, 0.918, 0.110), glm::vec3(0.254, 0.157, 0.981), glm::vec3(0.982, 0.457, 0.555));
				building6.drawStructure(glm::translate(glm::mat4(1.0), glm::vec3(6.0, 0.0, -3.0)), colorShaderProgram, renderStyle, glm::vec3(1.0, 0.0, 1.0), glm::vec3(0.514, 0.234, 0.145), glm::vec3(0.568, 0.998, 0.487));
				building7.drawStructure(glm::translate(glm::mat4(1.0), glm::vec3(22.0, 0.0, 4.0)), colorShaderProgram, renderStyle, glm::vec3(0.25, 0.25, 1.0), glm::vec3(0.459, 0.127, 0.147), glm::vec3(0.987, 0.983, 0.123));
				building8.drawStructure(glm::translate(glm::mat4(1.0), glm::vec3(6.0, 0.0, -3.0)), colorShaderProgram, renderStyle, glm::vec3(0.875, 0.361, 0.982), glm::vec3(0.786, 0.325, 0.651), glm::vec3(0.254, 0.447, 0.998));
				building9.drawStructure(glm::translate(glm::mat4(1.0), glm::vec3(6.0, 0.0, -3.0)), colorShaderProgram, renderStyle, glm::vec3(0.543, 0.564, 0.142), glm::vec3(1.0, 1.0, 0.225), glm::vec3(0.548, 0.237, 0.795));
				building10.drawStructure(glm::translate(glm::mat4(1.0), glm::vec3(6.0, 0.0, -3.0)), colorShaderProgram, renderStyle, glm::vec3(0.846, 0.918, 0.110), glm::vec3(0.254, 0.157, 0.981), glm::vec3(0.982, 0.457, 0.555));
				userCar.drawChassis(worldMatrix, colorShaderProgram, renderStyle);

				glUseProgram(texturedShaderProgram);
				glActiveTexture(GL_TEXTURE0);
				GLuint textureLocation = glGetUniformLocation(texturedShaderProgram, "textureSampler");
				glBindTexture(GL_TEXTURE_2D, userCar.frontLeft.customTexture);
				glUniform1i(textureLocation, 0);
				userCar.drawAllWheels(worldMatrix, texturedShaderProgram, renderStyle);

				glBindTexture(GL_TEXTURE_2D, x_zGrid.gridTexture);
				drawGrid(texturedShaderProgram, x_zGrid);
				curvedPath.erase(curvedPath.begin() + 1);
				if (curvedPath.size() == 1)
				{
					moving = false;
				}
				
				
			
			
		}

        // End frame
        glfwSwapBuffers(window);
        
        // Detect inputs
        glfwPollEvents();
        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

		//Default camera, set to the world space origin as the point of focus. 
		//To reset to this view press HOME

	if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS)
		{

		moving = false;
			userCar.body.localRotate = userCar.defaultBodyRotate;
			userCar.body.localScale = userCar.defaultBodyScale;
			userCar.body.localTranslate = userCar.defaultBodyTranslate;

			viewMatrix = defaultViewMatrix;
			projectionMatrix = defaultProjectionMatrix;

			

			setViewMatrix(texturedShaderProgram, viewMatrix);
			setViewMatrix(colorShaderProgram, viewMatrix);
			setProjectionMatrix(texturedShaderProgram, projectionMatrix);
			setProjectionMatrix(colorShaderProgram, projectionMatrix);


			 

		}


	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			
			vector <float> coords = generateRandomPoint();

			userCar.body.localTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(coords[0], 0.5f, coords[1]));
			
		
		}

		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		{
			userCar.body.localScale *= glm::scale(glm::mat4(1.0f), glm::vec3(1.001f, 1.001f, 1.001f));
			
		}

		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		{
			userCar.body.localScale *= glm::scale(glm::mat4(1.0f), glm::vec3(0.999f, 0.999f, 0.999f));

		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{


			
			angle = (angle + rotationSpeed * dt); // angles in degrees. Conversion follows

			//Rotation Matrix - Converts degrees to radians and specifies rotation around the x axis for wheels
			userCar.frontLeft.localRotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle),
				glm::vec3(0.0f, 0.0f, 1.0f));
			userCar.frontRight.localRotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle),
				glm::vec3(0.0f, 0.0f, 1.0f));
			userCar.backLeft.localRotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle),
				glm::vec3(0.0f, 0.0f, 1.0f));
			userCar.backRight.localRotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle),
				glm::vec3(0.0f, 0.0f, 1.0f));
			
			userCar.body.localTranslate *= glm::translate(glm::mat4(1.0f), glm::vec3(-0.0125f, 0.0f, 0.0f));
			
			
			
		}

	 if ( glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		{
		    
		 if (!moving)
		 {
			 moving = true;

			

		 }
		 else
		 {
			 moving = false;
		 }
		
		}  

	

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			userCar.body.localTranslate *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0125f, 0.0f));
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			userCar.body.localTranslate *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.0125f, 0.0f));
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			float dt = glfwGetTime() - lastFrameTime;
			lastFrameTime += dt;
			angle = (angle + rotationSpeed * dt); // angles in degrees. Conversion follows

			//Rotation Matrix - Converts degrees to radians and specifies rotation around the x axis for wheels
			userCar.frontLeft.localRotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle),
				glm::vec3(0.0f, 0.0f, -1.0f));
			userCar.frontRight.localRotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle),
				glm::vec3(0.0f, 0.0f, -1.0f));
			userCar.backLeft.localRotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle),
				glm::vec3(0.0f, 0.0f, -1.0f));
			userCar.backRight.localRotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle),
				glm::vec3(0.0f, 0.0f, -1.0f));

			userCar.body.localTranslate *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0125f, 0.0f, 0.0f));
		}


		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		{
			userCar.body.localRotate *= glm::rotate(glm::mat4(1.0f), glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		}

		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		{
			userCar.body.localRotate *= glm::rotate(glm::mat4(1.0f), glm::radians(-1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

			
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{

			viewMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			setViewMatrix(texturedShaderProgram, viewMatrix);
			setViewMatrix(colorShaderProgram, viewMatrix);
			setProjectionMatrix(texturedShaderProgram, projectionMatrix);
			setProjectionMatrix(colorShaderProgram, projectionMatrix);
			
		}

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			viewMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(-1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			setViewMatrix(texturedShaderProgram, viewMatrix);
			setViewMatrix(colorShaderProgram, viewMatrix);
			setProjectionMatrix(texturedShaderProgram, projectionMatrix);
			setProjectionMatrix(colorShaderProgram, projectionMatrix);;
		}

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			viewMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			setViewMatrix(texturedShaderProgram, viewMatrix);
			setViewMatrix(colorShaderProgram, viewMatrix);
			setProjectionMatrix(texturedShaderProgram, projectionMatrix);
			setProjectionMatrix(colorShaderProgram, projectionMatrix);
		}

		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			viewMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(-1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			setViewMatrix(texturedShaderProgram, viewMatrix);
			setViewMatrix(colorShaderProgram, viewMatrix);
			setProjectionMatrix(texturedShaderProgram, projectionMatrix);
			setProjectionMatrix(colorShaderProgram, projectionMatrix);
		}

		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		{
			renderStyle = 1;
		}

		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		{
			renderStyle = 2;
		}

		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		{
			renderStyle = 3;
		} 

		if (glfwGetKey(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)

		{
			

		}	

    } 
    
    // Shutdown GLFW
    glfwTerminate();
	
	return 0;

	
}




