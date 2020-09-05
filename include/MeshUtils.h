#pragma once
#include "RenderingObject.h"
#include <vector>
#include <cmath>

const int slices(16), stacks(8);

std::vector<RenderingObject::Vertex> CreateSphereVertex();
std::vector<GLuint> CreateSphereIndex();