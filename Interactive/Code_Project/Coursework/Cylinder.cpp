#include "Cylinder.h"

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

Cylinder::Cylinder()
{
	float radius = 1.0;
	float height = 1.0;
	int nSegments = 30;

	double PI = 3.1415926535;

	for (float i = 0.0f; i < nSegments; i += 1.0)
	{ 
		/* a loop around circumference of a tube */
		float angle = (float)(PI * i * 2 / nSegments);
		float nextAngle = (float)(PI * (i + 1.0) * 2 / nSegments);
		/* compute sin & cosine */
		float x1 = (float)sin(angle) * radius, y1 = (float)cos(angle) * radius;
		float x2 = (float)sin(nextAngle) * radius, y2 = (float)cos(nextAngle) * radius;

		float s1 = i / nSegments;
		float s2 = (i + 1) / nSegments;
		float t1 = 0.0;
		float t2 = 1.0;
		vertices.push_back({ {x1, y1, 0.0}, {x1, y1, 0.0}, {s1, t1} });
		vertices.push_back({ {x1, y1, height}, {x1, y1, 0.0}, {s1, t2} });
		vertices.push_back({ {x2, y2, height}, {x2, y2, 0.0}, {s2, t2} });


		vertices.push_back({ {x1, y1, 0.0}, {x1, y1, 0.0}, {s1, t1} });
		vertices.push_back({ {x2, y2, height}, {x2, y2, 0.0}, {s2, t2} });
		vertices.push_back({ {x2, y2, 0.0}, {x2, y2, 0.0}, {s2, t1} });
	}
}

void Cylinder::Draw()
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
