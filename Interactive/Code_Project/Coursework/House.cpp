#include "House.h"

void House::Draw(GLuint* texids)
{
	for (int i = -2 ; i < 1 ; ++i)
	{
		Draw1(texids, 100 + 840 * i, -300, -90, glm::vec3(0.99, 0.95, 0.5), glm::vec3(0.0, 1.0, 1.0));
		Draw1(texids, 380 + 840 * i, -300, -90, glm::vec3(0.99, 0.5, 0.5), glm::vec3(1.0, 0.0, 1.0));
		Draw1(texids, 660 + 840 * i, -300, -90, glm::vec3(0.99, 0.95, 0.95), glm::vec3(1.0, 1.0, 0.0));
	}
	for (int i = -1; i < 2; ++i)
	{
		Draw1(texids, 100 + 840 * i, -300, 90, glm::vec3(0.99, 0.95, 0.5), glm::vec3(0.0, 1.0, 1.0));
		Draw1(texids, 380 + 840 * i, -300, 90, glm::vec3(0.99, 0.5, 0.5), glm::vec3(1.0, 0.0, 1.0));
		Draw1(texids, 660 + 840 * i, -300, 90, glm::vec3(0.99, 0.95, 0.95), glm::vec3(1.0, 1.0, 0.0));
	}
}

void House::SetColor(float red, float green, float blue)
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

void House::SetColorNoSpecular(float red, float green, float blue)
{
	// material
	glm::vec4 front_base_color(red, green, blue, 1);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, &front_base_color[0]);
	glm::vec4 specular_color(0., 0., 0., 1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, &specular_color[0]);
	glMaterialf(GL_FRONT, GL_SHININESS, 0);
	glm::vec4 back_base_color(0.4, 0.4f, 0.4f, 1);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, &back_base_color[0]);
}

void House::DrawWindow(GLuint* texids, float x)
{
	glPushMatrix();
	glTranslated(x, 0.8, 0.5);
	glScaled(0.15, 0.15, 0.15);
	SetColor(0.95, 0.95, 0.5);
	glPushMatrix();
	glScaled(1.0, 0.2, 0.2);
	cube.Draw();
	glPopMatrix();
	glPushMatrix();
	SetColorNoSpecular(0.0, 0.0, 0.0);
	glScaled(0.6, 1.0, 0.04);
	glTranslated(0, 0.5, 0.0);
	cube.Draw();
	glPopMatrix();
	glPopMatrix();
}

void House::Draw1(GLuint* texids, float x, float z, float rotate, glm::vec3 color1, glm::vec3 color2)
{
	glPushMatrix();

	glPushMatrix();
	glRotated(rotate, 0.0, 1.0, 0.0);
	glTranslated(x, 10, z);
	glScaled(200, 200, 200);
	//top
	{
		SetColor(color1.x, color1.y, color1.z);
		{
			glPushMatrix();
			glTranslated(0, 1.5, 0);
			glScaled(0.42, 0.05, 0.42);
			sphere.Draw();
			glPopMatrix();
		}
		{
			glPushMatrix();
			glTranslated(0, 1.45, 0);
			glScaled(0.42, 0.05, 0.42);
			sphere.Draw();
			glPopMatrix();
		}
		{
			glPushMatrix();
			glTranslated(0, 1.5, 0);
			glScaled(0.4, 0.3, 0.4);
			sphere.Draw();
			glPopMatrix();
		}

		{
			glPushMatrix();
			glTranslated(0, 1.80, 0);
			glScaled(0.04, 0.03, 0.04);
			sphere.Draw();
			glPopMatrix();
		}
		{
			glPushMatrix();
			glTranslated(0, 1.83, 0);
			glScaled(0.02, 0.015, 0.02);
			sphere.Draw();
			glPopMatrix();
		}
		{
			glPushMatrix();
			glTranslated(0, 1.5, 0);
			glScaled(0.4, 0.4, 0.4);
			glRotated(90.0, 1.0, 0.0, 0.0);
			cylinder.Draw();
			glPopMatrix();
		}
	}

	//body
	{
		glPushMatrix();
		glTranslated(0, 0.5, 0);
		glScaled(1.0, 1.5, 1.0);
		SetColor(color1.x, color1.y, color1.z);
		glBindTexture(GL_TEXTURE_2D, texids[1]);
		cube.Draw();
		glBindTexture(GL_TEXTURE_2D, 0);
		glPopMatrix();
	}
	//eave
	{
		glPushMatrix();
		glTranslated(0, 1.25, 0);
		glScaled(1.2, 0.05, 1.2);
		SetColor(1.0, 1.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, texids[1]);
		cube.Draw();
		glBindTexture(GL_TEXTURE_2D, 0);
		glPopMatrix();
	}
	//window
	{
		DrawWindow(texids, -0.3);
		DrawWindow(texids, 0);
		DrawWindow(texids, 0.3);
	}
	//door
	{
		glPushMatrix();
		glTranslated(0.0, -0.05, 0.5);
		glScaled(0.15, 0.15, 0.15);
		SetColor(color1.x, color1.y, color1.z);
		//step
		{
			for (int i = 0; i < 5; ++i)
			{
				glPushMatrix();
				glTranslated(0.0, -0.2 * i, 0.2 * i + 0.1);
				glScaled(1.0, 0.2, 0.2);
				SetColor(1.0, 1.0, 1.0);
				glBindTexture(GL_TEXTURE_2D, texids[2]);
				cube.Draw();
				glBindTexture(GL_TEXTURE_2D, 0);
				glPopMatrix();
			}

			for (int i = 0; i < 2; ++i)
			{
				glPushMatrix();
				glTranslated(-0.6 + i * 1.2, 0.2, 0.0);
				glRotated(45.0, 1.0, 0.0, 0.0);
				glScaled(0.2, 0.2, 3.5);
				cube.Draw();
				glPopMatrix();
			}
		}

		//door main
		{
			glPushMatrix();
			SetColorNoSpecular(0.0, 0.0, 0.0);
			glScaled(0.6, 1.0, 0.04);
			glTranslated(0, 0.5, 0.0);
			cube.Draw();
			glPopMatrix();
		}

		//mask
		{
			glPushMatrix();
			SetColor(color2.x, color2.y, color2.z);
			glTranslated(0, 1.5, 0.0);
			glRotated(20.0, 1.0, 0.0, 0.0);
			glScaled(1.5, 0.01, 2.0);
			cube.Draw();
			glPopMatrix();
		}
		glPopMatrix();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	glPopMatrix();
}
