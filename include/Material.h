#pragma once
#include <array>
#include <GL/glew.h>

struct Material
{
	alignas(16) std::array<GLfloat, 3> ambient;
	alignas(16) std::array<GLfloat, 3> diffuse;
	alignas(16) std::array<GLfloat, 3> specular;
	alignas(4) GLfloat shininess;
};