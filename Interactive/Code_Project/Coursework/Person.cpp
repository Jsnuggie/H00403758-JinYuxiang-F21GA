#include "Person.h"

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp> 

Person::Person()
	: _pre_time(0.0)
	, _distance(0.0)
	, _pre_distance(0.0)
	, _angle(180.0)
	, _(1.0)
{
}

void Person::Draw()
{
	for (int i = -2 ; i < 3 ; ++i)
	{
		DrawMan(i * 30.0, rands[i + 2] * 100, (i + 2) % 2 == 1);
	}
}

void Person::SetColor(float red, float green, float blue)
{
	// material
	glm::vec4 front_base_color(red, green, blue, 1);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, &front_base_color[0]);
	glm::vec4 specular_color(0.4, 0.4f, 0.4f, 1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, &specular_color[0]);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	glm::vec4 back_base_color(0.4, 0.4f, 0.4f, 1);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, &back_base_color[0]);
}

void Person::DrawMan(float x, float z, bool forward)
{

	glPushMatrix();

	float deltaTime = glfwGetTime() - _pre_time;
	_pre_time = glfwGetTime();
	glTranslated(x, 35.0, 100.0 + z);
	auto rot = _angle + (forward ? 0 : 180);
	glRotated(rot, 0.0, 1.0, 0.0);
	_distance += deltaTime * 50;

	glTranslated(0.0, 0.0, _distance);
	if (_)
	{
		if (_distance > 1000.0)
		{
			_ = -1;
			_distance *= -1;
			_angle += 180;
		}
	}
	else
	{
		if (_distance < -1000.0)
		{
			_ = 1;
			_distance *= -1;
			_angle += 180;
		}
	}
	_pre_distance = _distance;

	glTranslated(0.0, sin(glfwGetTime()) * 0.5, 0.0);
	float tval = sin(glfwGetTime() * 10);

	//head
	{
		glPushMatrix();
		SetColor(0.8, 0.8, 0.8);
		glScaled(10.0, 10.0, 10.0);
		sphere.Draw();
		glPopMatrix();

		//eyes
		{
			glPushMatrix();
			SetColor(0.0, 0.0, 0.0);
			glTranslated(-3.0, 1.0, 8.0);
			glScaled(2.0, 2.0, 2.0);
			sphere.Draw();
			glPopMatrix();


			glPushMatrix();
			SetColor(0.0, 0.0, 0.0);
			glTranslated(3.0, 1.0, 8.0);
			glScaled(2.0, 2.0, 2.0);
			sphere.Draw();
			glPopMatrix();
		}

		//ears
		{
			glPushMatrix();
			SetColor(0.6, 0.2, 0.6);
			glTranslated(-9.0, 0.0, 0.0);
			glScaled(2.0, 4.0, 3.0);
			sphere.Draw();
			glPopMatrix();


			glPushMatrix();
			SetColor(0.6, 0.2, 0.6);
			glTranslated(9.0, 0.0, 0.0);
			glScaled(2.0, 4.0, 3.0);
			sphere.Draw();
			glPopMatrix();
		}
	}

	//body
	{
		glPushMatrix();
		glTranslated(0.0, -13.0, 0.0);
		//neck
		{
			glPushMatrix();
			glTranslated(0.0, 3.0, 0.0);
			SetColor(0.8, 0.8, 0.0);
			glScaled(8.0, 3.0, 8.0);
			sphere.Draw();
			glPopMatrix();
		}
		//body
		{
			glPushMatrix();
			SetColor(0.8, 0.8, 0.8);
			glScaled(9.9, 5.0, 9.9);
			sphere.Draw();
			glPopMatrix();
		}

		{
			glPushMatrix();
			glRotated(90.0, 1.0, 0.0, 0.0);
			SetColor(0.8, 0.8, 0.8);
			glScaled(10.0, 10.0, 10.0);
			cylinder.Draw();
			glPopMatrix();
		}
		{
			glPushMatrix();
			glTranslated(0.0, -10.0, 0.0);
			SetColor(0.8, 0.8, 0.8);
			glScaled(9.9, 5.0, 9.9);
			sphere.Draw();
			glPopMatrix();
		}
		glPopMatrix();
	}


	//arms
	{
		glPushMatrix();
		glTranslated(0.0, -16.0, 0.0);
		{
			glPushMatrix();
			glTranslated(10.0, 0.0, 0.0);
			glRotated(20.0, 0.0, 0.0, 1.0);
			DrawArm(-tval);
			glPopMatrix();
		}
		{
			glPushMatrix();
			glTranslated(-10.0, 0.0, 0.0);
			glRotated(-20.0, 0.0, 0.0, 1.0);
			DrawArm(tval);
			glPopMatrix();
		}
		glPopMatrix();
	}

	SetColor(1.0, 1.0, 1.0);
	//legs
	{
		glPushMatrix();
		glTranslated(0.0, -28.0, 0.0);
		//left
		{
			glPushMatrix();
			glTranslated(4.0, 0.0, 0.0);
			DrawLeg(tval);
			glPopMatrix();
		}
		//right
		{
			glPushMatrix();
			glTranslated(-4.0, 0.0, 0.0);
			DrawLeg(-tval);
			glPopMatrix();
		}

		glPopMatrix();
	}

	glPopMatrix();
}

void Person::DrawArm(float tval)
{
	glPushMatrix();
	glRotated(45.0 * tval, 1.0, 0.0, 0.0);
	glScaled(5.0, 5.0, 5.0);
	{
		SetColor(1.0, 1.0, 1.0);
		sphere.Draw();

		glRotated(90.0, 1.0, 0.0, 0.0);
		glPushMatrix();
		glScaled(0.8f, 0.8f, 2.0f);
		cylinder.Draw();
		glPopMatrix();
		glTranslated(0.0f, 0.0f, 2.0);

		SetColor(0.5, 0.5, 0.5);
		sphere.Draw();
	}
	glPopMatrix();
}

void Person::DrawLeg(float tval)
{
	glPushMatrix();
	glScaled(5.0, 5.0, 5.0);
	glRotated(45.0 * tval, 1.0, 0.0, 0.0);

	SetColor(1.0, 1.0, 1.0);
	//jointer
	{
		glPushMatrix();
		glScaled(1.0, 0.6, 1.0);
		sphere.Draw();
		glPopMatrix();
	}
	glRotated(90.0, 1.0, 0.0, 0.0);
	cylinder.Draw();
	//jointer
	{
		glTranslated(0.0f, 0.0f, 1.0);
		sphere.Draw();
	}
	glRotated(10.0 * (tval + 1.0), 1.0, 0.0, 0.0);
	{
		SetColor(0.8, 0.0, 0.0);
		glPushMatrix();
		glTranslated(0.0f, 0.0f, -0.5);
		glScaled(1.1, 1.1, 0.2);
		sphere.Draw();
		glPopMatrix();
	}
	SetColor(1.0, 1.0, 1.0);
	glPushMatrix();
	glScaled(1.0, 1.0, 2.0);
	cylinder.Draw();
	glPopMatrix();
	//foot
	{
		SetColor(0.6, 0.2, 0.6);
		glTranslated(0.0f, 0.5f, 2.0);
		glScaled(1.2, 1.5, 0.2);
		sphere.Draw();
	}
	glPopMatrix();
}
