#pragma once
#include <cmath>
#include <algorithm>
#include <GL/glew.h>
class Matrix
{
	GLfloat matrix[16];

public:
	Matrix() {}

	Matrix(const GLfloat *a);
	const GLfloat &operator[](std::size_t i) const;
	const GLfloat *data() const;
	GLfloat &operator[](std::size_t i);
	Matrix operator*(const Matrix &m) const;

	void LoadIdentity();
	void GetNormalMatrix(GLfloat *m) const;

	static Matrix Identity();
	static Matrix Translate(GLfloat x, GLfloat y, GLfloat z);
	static Matrix Scale(GLfloat x, GLfloat y, GLfloat z);
	static Matrix Rotate(GLfloat a, GLfloat x, GLfloat y, GLfloat z);
	static Matrix LookAt(GLfloat ex, GLfloat ey, GLfloat ez,
						 GLfloat gx, GLfloat gy, GLfloat gz,
						 GLfloat ux, GLfloat uy, GLfloat uz);
	static Matrix Orthogonal(GLfloat left, GLfloat right,
							 GLfloat bottom, GLfloat top,
							 GLfloat zNear, GLfloat zFar);
	static Matrix Frustum(GLfloat left, GLfloat right,
						  GLfloat bottom, GLfloat top,
						  GLfloat zNear, GLfloat zFar);
	static Matrix Perspective(GLfloat fovy, GLfloat aspect,
							  GLfloat zNear, GLfloat zFar);
};