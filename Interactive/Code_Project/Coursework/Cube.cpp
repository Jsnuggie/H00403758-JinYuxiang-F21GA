#include "Cube.h"

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

Cube::Cube()
{
	vertices.push_back({ 0.5, -0.5, -0.5,  0.0,  0.0, -1.0,  1.0, 0.0 });
	vertices.push_back({ -0.5, -0.5, -0.5,  0.0,  0.0, -1.0,  0.0, 0.0 });
	vertices.push_back({ 0.5,  0.5, -0.5,  0.0,  0.0, -1.0,  1.0, 1.0 });
	vertices.push_back({ -0.5,  0.5, -0.5,  0.0,  0.0, -1.0,  0.0, 1.0 });
	vertices.push_back({ 0.5,  0.5, -0.5,  0.0,  0.0, -1.0,  1.0, 1.0 });
	vertices.push_back({ -0.5, -0.5, -0.5,  0.0,  0.0, -1.0,  0.0, 0.0 });

	vertices.push_back({ -0.5, -0.5,  0.5,  0.0,  0.0,  1.0,  0.0, 0.0 });
	vertices.push_back({ 0.5, -0.5,  0.5,  0.0,  0.0,  1.0,  1.0, 0.0 });
	vertices.push_back({ 0.5,  0.5,  0.5,  0.0,  0.0,  1.0,  1.0, 1.0 });
	vertices.push_back({ 0.5,  0.5,  0.5,  0.0,  0.0,  1.0,  1.0, 1.0 });
	vertices.push_back({ -0.5,  0.5,  0.5,  0.0,  0.0,  1.0,  0.0, 1.0 });
	vertices.push_back({ -0.5, -0.5,  0.5,  0.0,  0.0,  1.0,  0.0, 0.0 });

	vertices.push_back({ -0.5,  0.5,  0.5, -1.0,  0.0,  0.0,  1.0, 0.0 });
	vertices.push_back({ -0.5,  0.5, -0.5, -1.0,  0.0,  0.0,  1.0, 1.0 });
	vertices.push_back({ -0.5, -0.5, -0.5, -1.0,  0.0,  0.0,  0.0, 1.0 });
	vertices.push_back({ -0.5, -0.5, -0.5, -1.0,  0.0,  0.0,  0.0, 1.0 });
	vertices.push_back({ -0.5, -0.5,  0.5, -1.0,  0.0,  0.0,  0.0, 0.0 });
	vertices.push_back({ -0.5,  0.5,  0.5, -1.0,  0.0,  0.0,  1.0, 0.0 });

	vertices.push_back({ 0.5,  0.5, -0.5,  1.0,  0.0,  0.0,  1.0, 1.0 });
	vertices.push_back({ 0.5,  0.5,  0.5,  1.0,  0.0,  0.0,  1.0, 0.0 });
	vertices.push_back({ 0.5, -0.5, -0.5,  1.0,  0.0,  0.0,  0.0, 1.0 });
	vertices.push_back({ 0.5, -0.5,  0.5,  1.0,  0.0,  0.0,  0.0, 0.0 });
	vertices.push_back({ 0.5, -0.5, -0.5,  1.0,  0.0,  0.0,  0.0, 1.0 });
	vertices.push_back({ 0.5,  0.5,  0.5,  1.0,  0.0,  0.0,  1.0, 0.0 });

	vertices.push_back({ -0.5, -0.5, -0.5,  0.0, -1.0,  0.0,  0.0, 1.0 });
	vertices.push_back({ 0.5, -0.5, -0.5,  0.0, -1.0,  0.0,  1.0, 1.0 });
	vertices.push_back({ 0.5, -0.5,  0.5,  0.0, -1.0,  0.0,  1.0, 0.0 });
	vertices.push_back({ 0.5, -0.5,  0.5,  0.0, -1.0,  0.0,  1.0, 0.0 });
	vertices.push_back({ -0.5, -0.5,  0.5,  0.0, -1.0,  0.0,  0.0, 0.0 });
	vertices.push_back({ -0.5, -0.5, -0.5,  0.0, -1.0,  0.0,  0.0, 1.0 });

	vertices.push_back({ -0.5,  0.5, -0.5,  0.0,  1.0,  0.0,  0.0, 1.0 });
	vertices.push_back({ 0.5,  0.5,  0.5,  0.0,  1.0,  0.0,  1.0, 0.0 });
	vertices.push_back({ 0.5,  0.5, -0.5,  0.0,  1.0,  0.0,  1.0, 1.0 });
	vertices.push_back({ 0.5,  0.5,  0.5,  0.0,  1.0,  0.0,  1.0, 0.0 });
	vertices.push_back({ -0.5,  0.5, -0.5,  0.0,  1.0,  0.0,  0.0, 1.0 });
	vertices.push_back({ -0.5,  0.5,  0.5,  0.0,  1.0,  0.0,  0.0, 0.0 });

}

void Cube::Draw()
{
	glBegin(GL_TRIANGLES);
	glEnable(GL_NORMALIZE);
	for (int i = 0; i < vertices.size(); ++i)
	{
		glTexCoord2d(vertices[i].texcoords[0], vertices[i].texcoords[1]);
		glNormal3d(vertices[i].normals[0], vertices[i].normals[1], vertices[i].normals[2]);
		glVertex3d(vertices[i].verts[0], vertices[i].verts[1], vertices[i].verts[2]);
	}
	glEnd();
}
