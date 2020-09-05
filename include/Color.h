#pragma once

#include <array>

#include "Matrix.h"

using Color = std::array<GLfloat, 4>;

Color operator*(const Matrix &m, const Color &v)
{
	Color t;
	for (int i = 0; i < 4; ++i)
		t[i] = m[i] * v[0] + m[i + 4] * v[1] + m[i + 8] * v[2] + m[i + 12] * v[3];

	return t;
}