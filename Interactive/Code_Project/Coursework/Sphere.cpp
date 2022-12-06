#include "Sphere.h"

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

Sphere::Sphere()
{
	double radius = 1.0;
	double slices = 30;
	double segments = 20;

	double PI = 3.1415926535;

	double x, y, z;
	double s = 0.0f, t = 0.0f; // texture coordinates

	double inctheta = ((2.0 * PI) / slices);
	double incphi = (PI / segments);

	for (double theta = -PI; theta <= PI; theta += inctheta)
	{
		for (double phi = -(PI / 2.0f); phi < (PI /2.0f - incphi); phi += incphi)
		{
			x = (cos(phi) * cos(theta) * radius);
			y = (cos(phi) * sin(theta) * radius);
			z = (sin(phi) * radius);
			vertices.push_back({ {x, y, z}, {x, y, z}, {s, t} });

			x = (cos(phi) * cos(theta + inctheta) * radius);
			y = (cos(phi) * sin(theta + inctheta) * radius);
			z = (sin(phi) * radius);
			t = (((float)phi / (float)PI) + 0.5);
			s = ((((float)theta + inctheta) / ((float)PI * 2.0))) + 0.5;

			vertices.push_back({ {x, y, z}, {x, y, z}, {s, t} });

			x = (cos(phi + incphi) * cos(theta + inctheta) * radius);
			y = (cos(phi + incphi) * sin(theta + inctheta) * radius);
			z = (sin(phi + incphi) * radius);
			t = ((((float)phi + incphi) / (float)PI) + 0.5f);
			s = ((((float)theta + inctheta) / ((float)PI * 2.0f)) + 0.5f);

			vertices.push_back({ {x, y, z}, {x, y, z}, {s, t} });

			x = (cos(phi + incphi) * cos(theta) * radius);
			y = (cos(phi + incphi) * sin(theta) * radius);
			z = (sin(phi + incphi) * radius);
			t = ((((float)phi + incphi) / (float)PI) + 0.5f);
			s = (((float)theta / ((float)PI * 2.0f)) + 0.5f);

			vertices.push_back({ {x, y, z}, {x, y, z}, {s, t} });
		}
	}
}

void Sphere::Draw()
{
	glBegin(GL_QUADS);
	glEnable(GL_NORMALIZE);
	for (int i = 0; i < vertices.size(); ++i)
	{
		glTexCoord2d(vertices[i].texcoords[0], vertices[i].texcoords[1]);
		glNormal3d(vertices[i].verts[0], vertices[i].verts[1], vertices[i].verts[2]);
		glVertex3d(vertices[i].verts[0], vertices[i].verts[1], vertices[i].verts[2]);
	}
	glEnd();
}
