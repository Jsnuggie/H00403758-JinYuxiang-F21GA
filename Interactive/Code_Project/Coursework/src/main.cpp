#include <iostream>
#include <string>
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "loadimage.h"

using namespace std;

GLFWwindow* window = NULL;
const char* WINDOW_TITLE = "Texture";
const GLint WINDOW_WIDTH = 600;
const GLint WINDOW_HEIGHT = 600;

bool initOpenGL();
void drawCube(int colourIndex);

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

struct UV
{
	GLfloat ux, uy, vx, vy;
};
const int COLOR_COUNT = 6;
//UV uvs[COLOR_COUNT] =
//{
//	/*U								V*/
//	{ 0.0, 5.0/6.0,						1.0/6.0, 1.0 },
//	{ 1.0 / 6.0, 5.0 / 6.0,				2.0 / 6.0, 1.0 },
//	{ 2.0 / 6.0, 5.0 / 6.0,				3.0 / 6.0, 1.0 },
//	{ 3.0 / 6.0, 5.0 / 6.0,				4.0 / 6.0, 1.0 },
//	{ 4.0 / 6.0, 5.0 / 6.0,				5.0 / 6.0, 1.0 },
//	{ 5.0 / 6.0, 5.0 / 6.0,				6.0 / 6.0, 1.0 },
//};

UV uvs[COLOR_COUNT][6];
void initUvs()
{
	GLfloat _1over6 = 1.0f / 6.0f;
	GLfloat _1overColorCount = 1.0f / COLOR_COUNT;

	// colors
	for (int c = 0; c < COLOR_COUNT; ++c)
	{
		int yi = COLOR_COUNT - c - 1;

		// points
		for (int p = 0; p < 6; ++p)
		{
			int xi = p;

			UV& uv = uvs[c][p];
			uv.ux = xi * _1overColorCount;
			uv.uy = yi * _1over6;
			uv.vx = (xi + 1) * _1overColorCount;
			uv.vy = (yi + 1) * _1over6;
		}
	}
}

int main()
{
	if (!initOpenGL())
	{
		cerr << "GLFW initialisation failed." << endl;
		return -1;
	}

	/* Enable depth testing */
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/* Enable back-face culling */
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	/* Enable transparency blending */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Choose a colour to clear the screen (RGBA range [0, 1]) */
	glClearColor(0.4f, 0.5f, 0.6f, 1.0f);

	float rotateTime = (float)glfwGetTime();
	float colourTime = (float)glfwGetTime(); 
	int colourIndex = 0; 

	GLuint tex = loadimage("Sprite_Dice.bmp"); 
	initUvs(); 

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		
		/* Start rendering */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);

		glEnable(GL_TEXTURE_2D); 
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); 
		glBindTexture(GL_TEXTURE_2D, tex); 

		/* Auto rotation */
		if ((float)glfwGetTime() - rotateTime >= 0.03f)
		{
			glRotatef(0.5f, 1.0f, 1.0f, 1.0f);
			rotateTime = (float)glfwGetTime();
		}

		if ((float)glfwGetTime() - colourTime >= 1.0f)
		{
			colourTime = (float)glfwGetTime();
			colourIndex += 1; 
			if (colourIndex == 6)
			{
				colourIndex = 0; 
			}
		}

		drawCube(colourIndex);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and porcess events */
		glfwPollEvents();
		
		glDisable(GL_TEXTURE_2D); 
	}

	glfwTerminate();
	return 0;
}

bool initOpenGL()
{
	/* Initialize the GLFW library */
	if (!glfwInit()) {
		cout << "GLFW initialisation failed." << endl;
		return false;
	}

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		cout << "GLFW failed to create window." << endl;
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Initialize the GLEW library */
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		/* Problem: glewInit failed, something is seriously wrong */
		cout << "GLEW initialisation failed: " << glewGetErrorString(err) << endl;
		return false;
	}
	cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << endl;

	return true;
}

void drawCube(int colourIndex)
{
	float r = 0.5;
	glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
	glBegin(GL_TRIANGLES);

	UV* uv = uvs[colourIndex];

	// shown
	glTexCoord2f(uv[0].ux, uv[0].vy); 
	glVertex3f(-r, r, r);
	glTexCoord2f(uv[0].ux, uv[0].uy);
	glVertex3f(-r, -r, r);
	glTexCoord2f(uv[0].vx, uv[0].uy);
	glVertex3f(r, -r, r);
	// shown
	glTexCoord2f(uv[0].vx, uv[0].uy);
	glVertex3f(r, -r, r);
	glTexCoord2f(uv[0].vx, uv[0].vy);
	glVertex3f(r, r, r);
	glTexCoord2f(uv[0].ux, uv[0].vy);
	glVertex3f(-r, r, r);

	// hidden
	glTexCoord2f(uv[5].ux, uv[5].uy);
	glVertex3f(-r, -r, -r);
	glTexCoord2f(uv[5].ux, uv[5].vy);
	glVertex3f(-r, r, -r);
	glTexCoord2f(uv[5].vx, uv[5].vy);
	glVertex3f(r, r, -r);
	// hidden
	glTexCoord2f(uv[5].vx, uv[5].vy);
	glVertex3f(r, r, -r);
	glTexCoord2f(uv[5].vx, uv[5].uy);
	glVertex3f(r, -r, -r);
	glTexCoord2f(uv[5].ux, uv[5].uy);
	glVertex3f(-r, -r, -r);

	// shown
	glTexCoord2f(uv[1].ux, uv[1].uy);
	glVertex3f(r, -r, r);
	glTexCoord2f(uv[1].vx, uv[1].uy);
	glVertex3f(r, -r, -r);
	glTexCoord2f(uv[1].vx, uv[1].vy);
	glVertex3f(r, r, -r);
	// shown
	glTexCoord2f(uv[1].vx, uv[1].vy);
	glVertex3f(r, r, -r);
	glTexCoord2f(uv[1].ux, uv[1].vy);
	glVertex3f(r, r, r);
	glTexCoord2f(uv[1].ux, uv[1].uy);
	glVertex3f(r, -r, r);

	// hidden
	glTexCoord2f(uv[4].ux, uv[4].vy);
	glVertex3f(-r, r, r);
	glTexCoord2f(uv[4].vx, uv[4].vy);
	glVertex3f(-r, r, -r);
	glTexCoord2f(uv[4].vx, uv[4].uy);
	glVertex3f(-r, -r, -r);
	// hidden
	glTexCoord2f(uv[4].vx, uv[4].uy);
	glVertex3f(-r, -r, -r);
	glTexCoord2f(uv[4].ux, uv[4].uy);
	glVertex3f(-r, -r, r);
	glTexCoord2f(uv[4].ux, uv[4].vy);
	glVertex3f(-r, r, r);

	//shown
	glTexCoord2f(uv[2].ux, uv[2].uy);
	glVertex3f(-r, r, r);
	glTexCoord2f(uv[2].vx, uv[2].uy);
	glVertex3f(r, r, r);
	glTexCoord2f(uv[2].vx, uv[2].vy);
	glVertex3f(r, r, -r);
	//shown
	glTexCoord2f(uv[2].vx, uv[2].vy);
	glVertex3f(r, r, -r);
	glTexCoord2f(uv[2].ux, uv[2].vy);
	glVertex3f(-r, r, -r);
	glTexCoord2f(uv[2].ux, uv[2].uy);
	glVertex3f(-r, r, r);

	//hidden
	glTexCoord2f(uv[3].vx, uv[3].uy);
	glVertex3f(r, -r, r);
	glTexCoord2f(uv[3].ux, uv[3].uy);
	glVertex3f(-r, -r, r);
	glTexCoord2f(uv[3].ux, uv[3].vy);
	glVertex3f(-r, -r, -r);
	//hidden
	glTexCoord2f(uv[3].ux, uv[3].vy);
	glVertex3f(-r, -r, -r);
	glTexCoord2f(uv[3].vx, uv[3].vy);
	glVertex3f(r, -r, -r);
	glTexCoord2f(uv[3].vx, uv[3].uy);
	glVertex3f(r, -r, r);

	glEnd();
}
