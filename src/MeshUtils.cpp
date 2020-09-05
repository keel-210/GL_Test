#include "MeshUtils.h"

std::vector<RenderingObject::Vertex> CreateSphereVertex()
{
	std::vector<RenderingObject::Vertex> solidSphereVertex;

	for (int j = 0; j <= stacks; ++j)
	{
		const float t(static_cast<float>(j) / static_cast<float>(stacks));
		const float y(cos(3.141593f * t)), r(sin(3.141593f * t));
		for (int i = 0; i <= slices; ++i)
		{
			const float s(static_cast<float>(i) / static_cast<float>(slices));
			const float z(r * cos(6.283185f * s)), x(r * sin(6.283185f * s));
			const RenderingObject::Vertex v = {x, y, z, x, y, z};
			solidSphereVertex.emplace_back(v);
		}
	}
	return solidSphereVertex;
}
std::vector<GLuint> CreateSphereIndex()
{
	std::vector<GLuint> solidSphereIndex;
	for (int j = 0; j < stacks; ++j)
	{
		const int k((slices + 1) * j);
		for (int i = 0; i < slices; ++i)
		{
			const GLuint k0(k + i);
			const GLuint k1(k0 + 1);
			const GLuint k2(k1 + slices);
			const GLuint k3(k2 + 1);
			solidSphereIndex.emplace_back(k0);
			solidSphereIndex.emplace_back(k2);
			solidSphereIndex.emplace_back(k3);

			solidSphereIndex.emplace_back(k0);
			solidSphereIndex.emplace_back(k3);
			solidSphereIndex.emplace_back(k1);
		}
	}
	return solidSphereIndex;
}