#pragma once


#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp> 

#include "Cube.h"
#include "Sphere.h"
#include "Cylinder.h"

class House
{
public:
	void Draw(GLuint* texids);
private:
	void SetColor(float red, float green, float blue);
	void SetColorNoSpecular(float red, float green, float blue);

	void DrawWindow(GLuint* texids, float x);

	void Draw1(GLuint* texids, float x, float z, float rotate, glm::vec3 color1, glm::vec3 color2);
private:
	Cube cube;
	Sphere sphere;
	Cylinder cylinder;
};

