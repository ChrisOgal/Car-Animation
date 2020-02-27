#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "Cube.h"

using namespace std;


class Tree {

public: 
	Cube green1;
	Cube green2;
	Cube trunk;


	Tree(glm::mat4 worldMatrix);

	void createTree(glm::mat4 worldMatrix);

	void drawTree(glm::mat4 worldMatrix, int shaderProgram, int renderStyle, Cube part, glm::vec3 color);

	void drawPlant(glm::mat4 worldMatrix, int shaderProgram, int renderStyle, glm::vec3 frameColor, glm::vec3 roof1color, glm::vec3 roof2color);

};