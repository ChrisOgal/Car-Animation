#pragma once

#include <GL/glew.h>    

#include <GLFW/glfw3.h> 

#include <glm/glm.hpp>  
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include "TextureLoader.h"

using namespace std;

class BSpline
{
public:

	


	BSpline();

	static void addControlPoints(TextureLoader::TexturedVertex texturedCubeVertexArray);

	static void addControlPoints(vector <glm::vec3> control);
	static void clearSplineGenerator();
	static void generateSamplePoints();
	static glm::vec3 getPosition(float t, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4);
	static vector<glm::vec3> finalSamplePoints();

	~BSpline();
	
};


static vector<glm::vec3> controlPoints;
static vector<glm::vec3> samplePoints;