#include <cmath>
#include <algorithm>
#include <GL/glew.h>

#include "Matrix.h"

Matrix::Matrix(const GLfloat *a)
{
	std::copy(a, a + 16, matrix);
}
const GLfloat &Matrix::operator[](std::size_t i) const
{
	return matrix[i];
}
GLfloat &Matrix::operator[](std::size_t i)
{
	return matrix[i];
}
const GLfloat *Matrix::data() const
{
	return matrix;
}
void Matrix::LoadIdentity()
{
	std::fill(matrix, matrix + 16, 0.0f);
	matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1.0f;
}
Matrix Matrix::Identity()
{
	Matrix t;
	t.LoadIdentity();
	return t;
}
Matrix Matrix::Translate(GLfloat x, GLfloat y, GLfloat z)
{
	Matrix t;
	t.LoadIdentity();
	t[12] = x;
	t[13] = y;
	t[14] = z;
	return t;
}
Matrix Matrix::Scale(GLfloat x, GLfloat y, GLfloat z)
{
	Matrix t;
	t.LoadIdentity();
	t[0] = x;
	t[5] = y;
	t[10] = z;
	return t;
}
Matrix Matrix::Rotate(GLfloat a, GLfloat x, GLfloat y, GLfloat z)
{
	Matrix t;
	const GLfloat d(sqrt(x * x + y * y + z * z));
	if (d <= 0.0f)
		return t;

	const GLfloat l(x / d), m(y / d), n(z / d);
	const GLfloat l2(l * l), m2(m * m), n2(n * n);
	const GLfloat lm(l * m), mn(m * n), nl(n * l);
	const GLfloat c(cos(a)), c1(1.0f - c), s(sin(a));

	t.LoadIdentity();
	t[0] = (1.0f - l2) * c + l2;
	t[1] = lm * c1 + n * s;
	t[2] = nl * c1 - m * s;
	t[4] = lm * c1 - n * s;
	t[5] = (1.0f - m2) * x + m2;
	t[6] = mn * c1 + l * s;
	t[8] = nl * c1 + m * s;
	t[9] = mn * c1 - l * s;
	t[10] = (1.0f - n2) * c + n2;
	return t;
}
Matrix Matrix::operator*(const Matrix &m) const
{
	Matrix t;
	for (int i = 0; i < 16; ++i)
	{
		const int j(i & 3), k(i & ~3);
		t[i] =
			matrix[0 + j] * m[k + 0] +
			matrix[4 + j] * m[k + 1] +
			matrix[8 + j] * m[k + 2] +
			matrix[12 + j] * m[k + 3];
	}
	return t;
}
Matrix Matrix::LookAt(GLfloat ex, GLfloat ey, GLfloat ez,
					  GLfloat gx, GLfloat gy, GLfloat gz,
					  GLfloat ux, GLfloat uy, GLfloat uz)
{
	//平行移動
	const Matrix tv(Matrix::Translate(-ex, -ey, -ez));

	//視点を原点とした時の座標系の軸ベクトルを求める
	//t軸:e-g
	const GLfloat tx(ex - gx);
	const GLfloat ty(ey - gy);
	const GLfloat tz(ez - gz);
	//r軸:u*t
	const GLfloat rx(uy * tz - uz * ty);
	const GLfloat ry(uz * tx - ux * tz);
	const GLfloat rz(ux * ty - uy * tx);
	//s軸:t*r
	const GLfloat sx(ty * rz - tz * ry);
	const GLfloat sy(tz * rx - tx * rz);
	const GLfloat sz(tx * ry - ty * rx);

	//s軸の長さチェック
	const GLfloat s2(sx * sx + sy * sy + sz * sz);
	if (s2 == 0.0f)
		return tv;

	Matrix rv;
	rv.LoadIdentity();
	//r軸を正規化
	const GLfloat r(sqrt(rx * rx + ry * ry + rz * rz));
	rv[0] = rx / r;
	rv[4] = ry / r;
	rv[8] = rz / r;
	//s軸を正規化
	const GLfloat s(sqrt(s2));
	rv[1] = sx / s;
	rv[5] = sy / s;
	rv[9] = sz / s;
	//t軸を正規化
	const GLfloat t(sqrt(tx * tx + ty * ty + tz * tz));
	rv[2] = tx / t;
	rv[6] = ty / t;
	rv[10] = tz / t;

	return rv * tv;
}
Matrix Matrix::Orthogonal(GLfloat left, GLfloat right,
						  GLfloat bottom, GLfloat top,
						  GLfloat zNear, GLfloat zFar)
{
	Matrix t;
	const GLfloat dx(right - left);
	const GLfloat dy(top - bottom);
	const GLfloat dz(zFar - zNear);

	if (dx != 0.0f && dy != 0.0f && dz != 0.0f)
	{
		t.LoadIdentity();
		t[0] = 2.0f / dx;
		t[5] = 2.0f / dy;
		t[10] = -2.0f / dz;
		t[12] = -(right + left) / dx;
		t[13] = -(top + bottom) / dy;
		t[14] = -(zFar + zNear) / dz;
	}
	return t;
}
Matrix Matrix::Frustum(GLfloat left, GLfloat right,
					   GLfloat bottom, GLfloat top,
					   GLfloat zNear, GLfloat zFar)
{
	Matrix t;
	const GLfloat dx(right - left);
	const GLfloat dy(top - bottom);
	const GLfloat dz(zFar - zNear);
	if (dx != 0.0f && dy != 0.0f && dz != 0.0f)
	{
		t.LoadIdentity();
		t[0] = 2.0f * zNear / dx;
		t[5] = 2.0f * zNear / dy;
		t[8] = (right + left) / dx;
		t[9] = (top + bottom) / dy;
		t[10] = -(zFar + zNear) / dz;
		t[11] = -1.0f;
		t[14] = -2.0f * zFar * zNear / dz;
		t[15] = 0.0f;
	}
	return t;
}
