#include "BSpline.h"

BSpline::BSpline()
{
}

void BSpline::addControlPoints(TextureLoader::TexturedVertex texturedCubeVertexArray)
{

}
void BSpline::addControlPoints(vector <glm::vec3> control)
{
	

	for (int i = 0; i < control.size(); i++)
	{
		controlPoints.push_back(control[i]);
	}

}

void BSpline::clearSplineGenerator()
{
	controlPoints.clear();
	samplePoints.clear();
}


void BSpline::generateSamplePoints()
{
	if (controlPoints.size() == 0)
	{
		return;
	}


	const int numPointsPerSegment = 2000;
	float increment = 1.0f / numPointsPerSegment;

	for (int i = 0; i < controlPoints.size(); ++i)
	{
		float t = 0.0f;

		//Set the working control points
		glm::vec3 p1 = controlPoints[i];
		glm::vec3 p2 = controlPoints[(i + 1) % controlPoints.size()];
		glm::vec3 p3 = controlPoints[(i + 1) % controlPoints.size()];
		glm::vec3 p4 = controlPoints[(i + 1) % controlPoints.size()];

		for (int j = 0; j < numPointsPerSegment; ++j)
		{
			samplePoints.push_back(getPosition(t, p1, p2, p3, p4));
			t += increment;
		}
	}

	
}

glm::vec3 BSpline::getPosition(float t, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4)
{
	// based on parameter t and the four control points p1, p2, p3, p4
	glm::vec4 params(t*t*t, t*t, t, 1);
	glm::mat4 coefficients(glm::vec4(-1, 3, -3, 1), glm::vec4(3, -6, 0, 4), glm::vec4(-3, 3, 3, 1), glm::vec4(1, 0, 0, 0));
	glm::vec4 product = (1.0f / 6.0f) * params * coefficients;

	return glm::vec3(glm::vec4(product.x * p1 + product.y * p2 + product.z * p3 + product.w * p4, 1.0f));
}

vector<glm::vec3> BSpline::finalSamplePoints()
{
	vector<glm::vec3> finalPoints = samplePoints;

	return finalPoints;
}

BSpline::~BSpline()
{
}
