#pragma once

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp>
#include <FreeImageIO.h> //Import the FreeImage library for texture mapping

class TextureLoader
{
public:
	TextureLoader();

	static int loadTexture(char* imagepath);

	struct TexturedVertex
	{
		TexturedVertex();

		TexturedVertex(glm::vec3 _position, glm::vec3 _color, glm::vec2 _uv)
			: position(_position), color(_color), uv(_uv) {}

		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 uv;
	};
	

private:

};

