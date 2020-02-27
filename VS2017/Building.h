#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "Cube.h"

using namespace std;


class Building {

public:

	Cube roof1;
	Cube roof2;
	Cube frame;

	Building(glm::mat4 worldMatrix);

	void createBuilding(glm::mat4 worldMatrix);

	void drawBuilding(glm::mat4 worldMatrix, int shaderProgram, int renderStyle, Cube part, glm::vec3 color);

	void drawStructure(glm::mat4 worldMatrix, int shaderProgram, int renderStyle, glm::vec3 frameColor, glm::vec3 roof1color, glm::vec3 roof2color);

};