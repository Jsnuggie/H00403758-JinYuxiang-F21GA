// Coursework.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp> 

#include "loadimage.h"

#include <io.h>
using namespace std;

GLFWwindow* window = NULL;
const char* WINDOW_TITLE = "Coursework";
const GLint WINDOW_WIDTH = 800;
const GLint WINDOW_HEIGHT = 600;

//camera
bool wKey, sKey, aKey, dKey;
bool lMouseButton;

double mouseX, mouseY;
float sensitivity = 0.01f; // speed of the camera moving
float cameraSpeed = 10.0f;
/* Vectors containing eye coordinates */
glm::vec3 pos = glm::vec3(0.0f, 100.0f, -200.0f);
/* The vector along which the camera are looking */
glm::vec3 vd = glm::vec3(0.0f, 0.0f, 1.0f);

GLuint texids[16];
int rands[10];

#include "Sphere.h"
#include "Cylinder.h"
#include "Cube.h"
#include "Plane.h"
Sphere sphere;
Cylinder cylinder;
Cube cube;
Plane plane;
#include "Person.h"
#include "House.h"
Person person;
House house;

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, int button, int action, int mods);

void drawSkybox(float r)
{
	glPushMatrix();
	glRotated(180.0, 0.0, 0.0, 1.0);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	GLfloat vertices[] = {
		-4000.0, -4000.0, -4000.0,  0.0, 0.0,  0.0,  0.0, -1.0,
		 4000.0, -4000.0, -4000.0,  1.0, 0.0,  0.0,  0.0, -1.0,
		 4000.0,  4000.0, -4000.0,  1.0, 1.0,  0.0,  0.0, -1.0,
		 4000.0,  4000.0, -4000.0,  1.0, 1.0,  0.0,  0.0, -1.0,
		-4000.0,  4000.0, -4000.0,  0.0, 1.0,  0.0,  0.0, -1.0,
		-4000.0, -4000.0, -4000.0,  0.0, 0.0,  0.0,  0.0, -1.0,

		 4000.0, -4000.0,  4000.0,  1.0, 0.0,  0.0,  0.0,  1.0,
		-4000.0, -4000.0,  4000.0,  0.0, 0.0,  0.0,  0.0,  1.0,
		 4000.0,  4000.0,  4000.0,  1.0, 1.0,  0.0,  0.0,  1.0,
		-4000.0,  4000.0,  4000.0,  0.0, 1.0,  0.0,  0.0,  1.0,
		 4000.0,  4000.0,  4000.0,  1.0, 1.0,  0.0,  0.0,  1.0,
		-4000.0, -4000.0,  4000.0,  0.0, 0.0,  0.0,  0.0,  1.0,

		-4000.0,  4000.0, -4000.0,  1.0, 1.0, -1.0,  0.0,  0.0,
		-4000.0,  4000.0,  4000.0,  1.0, 0.0, -1.0,  0.0,  0.0,
		-4000.0, -4000.0, -4000.0,  0.0, 1.0, -1.0,  0.0,  0.0,
		-4000.0, -4000.0,  4000.0,  0.0, 0.0, -1.0,  0.0,  0.0,
		-4000.0, -4000.0, -4000.0,  0.0, 1.0, -1.0,  0.0,  0.0,
		-4000.0,  4000.0,  4000.0,  1.0, 0.0, -1.0,  0.0,  0.0,

		 4000.0,  4000.0,  4000.0,  1.0, 0.0,  1.0,  0.0,  0.0,
		 4000.0,  4000.0, -4000.0,  1.0, 1.0,  1.0,  0.0,  0.0,
		 4000.0, -4000.0, -4000.0,  0.0, 1.0,  1.0,  0.0,  0.0,
		 4000.0, -4000.0, -4000.0,  0.0, 1.0,  1.0,  0.0,  0.0,
		 4000.0, -4000.0,  4000.0,  0.0, 0.0,  1.0,  0.0,  0.0,
		 4000.0,  4000.0,  4000.0,  1.0, 0.0,  1.0,  0.0,  0.0,

		-4000.0, -4000.0, -4000.0,  0.0, 1.0,  0.0, -1.0,  0.0,
		 4000.0, -4000.0,  4000.0,  1.0, 0.0,  0.0, -1.0,  0.0,
		 4000.0, -4000.0, -4000.0,  1.0, 1.0,  0.0, -1.0,  0.0,
		 4000.0, -4000.0,  4000.0,  1.0, 0.0,  0.0, -1.0,  0.0,
		-4000.0, -4000.0, -4000.0,  0.0, 1.0,  0.0, -1.0,  0.0,
		-4000.0, -4000.0,  4000.0,  0.0, 0.0,  0.0, -1.0,  0.0,

		-4000.0,  4000.0, -4000.0,  0.0, 1.0,  0.0,  1.0,  0.0,
		 4000.0,  4000.0, -4000.0,  1.0, 1.0,  0.0,  1.0,  0.0,
		 4000.0,  4000.0,  4000.0,  1.0, 0.0,  0.0,  1.0,  0.0,
		 4000.0,  4000.0,  4000.0,  1.0, 0.0,  0.0,  1.0,  0.0,
		-4000.0,  4000.0,  4000.0,  0.0, 0.0,  0.0,  1.0,  0.0,
		-4000.0,  4000.0, -4000.0,  0.0, 1.0,  0.0,  1.0,  0.0
	};
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	{//1	
		glBindTexture(GL_TEXTURE_2D, texids[3]);
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < 6; i++)
		{
			glTexCoord2f(vertices[i * 8 + 3], vertices[i * 8 + 4]);
			glVertex3f(vertices[i * 8 + 0], vertices[i * 8 + 1], vertices[i * 8 + 2]);
		}
		glEnd();

	}
	{//2

		glBindTexture(GL_TEXTURE_2D, texids[4]);
		glBegin(GL_TRIANGLES);
		for (int i = 6; i < 12; i++)
		{
			glTexCoord2f(vertices[i * 8 + 3], vertices[i * 8 + 4]);
			glVertex3f(vertices[i * 8 + 0], vertices[i * 8 + 1], vertices[i * 8 + 2]);
		}
		glEnd();
	}
	{//3

		glBindTexture(GL_TEXTURE_2D, texids[5]);
		glBegin(GL_TRIANGLES);
		for (int i = 12; i < 18; i++)
		{
			glTexCoord2f(vertices[i * 8 + 3], vertices[i * 8 + 4]);
			glVertex3f(vertices[i * 8 + 0], vertices[i * 8 + 1], vertices[i * 8 + 2]);
		}
		glEnd();
	}
	{//4
		glBindTexture(GL_TEXTURE_2D, texids[6]);
		glBegin(GL_TRIANGLES);
		for (int i = 18; i < 24; i++)
		{
			glTexCoord2f(vertices[i * 8 + 3], vertices[i * 8 + 4]);
			glVertex3f(vertices[i * 8 + 0], vertices[i * 8 + 1], vertices[i * 8 + 2]);
		}
		glEnd();
	}
	{//5
		glBindTexture(GL_TEXTURE_2D, texids[7]);
		glBegin(GL_TRIANGLES);
		for (int i = 24; i < 30; i++)
		{
			glTexCoord2f(vertices[i * 8 + 3], vertices[i * 8 + 4]);
			glVertex3f(vertices[i * 8 + 0], vertices[i * 8 + 1], vertices[i * 8 + 2]);
		}
		glEnd();
	}
	{//6

		glBindTexture(GL_TEXTURE_2D, texids[8]);
		glBegin(GL_TRIANGLES);
		for (int i = 30; i < 36; i++)
		{
			glTexCoord2f(vertices[i * 8 + 3], vertices[i * 8 + 4]);
			glVertex3f(vertices[i * 8 + 0], vertices[i * 8 + 1], vertices[i * 8 + 2]);
		}
		glEnd();
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPopMatrix();
}

void setMaterial()
{

	// material
	glm::vec4 front_base_color(0.7f, 0.7f, 0.7f, 1);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, &front_base_color[0]);
	glm::vec4 specular_color(0.4, 0.4f, 0.4f, 1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, &specular_color[0]);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	glm::vec4 back_base_color(0.4, 0.4f, 0.4f, 1);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, &back_base_color[0]);
}

bool initOpenGL()
{
	/* Initialize the GLFW library */
	if (!glfwInit()) {
		cout << "GLFW initialisation failed." << std::endl;
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
		cout << "GLFW failed to create window." << std::endl;
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_callback);

	/* Initialize the GLEW library */
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		/* Problem: glewInit failed, something is seriously wrong */
		cout << "GLEW initialisation failed: " << glewGetErrorString(err) << std::endl;
		return false;
	}
	cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

	return true;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		std::cout << "Esc key is pressed." << std::endl;
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		wKey = true;
	}

	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		wKey = false;
	}

	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		sKey = true;
	}

	if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	{
		sKey = false;
	}

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		aKey = true;
	}

	if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		aKey = false;
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		dKey = true;
	}

	if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	{
		dKey = false;
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		glLoadIdentity();
	}
}

void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{

	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT)
	{
		lMouseButton = true;
		glfwGetCursorPos(window, &mouseX, &mouseY);
	}
	if (action == GLFW_RELEASE && button == GLFW_MOUSE_BUTTON_LEFT)
		lMouseButton = false;

}

void setCamera()
{
	float aspectRatio = static_cast<GLdouble>(WINDOW_WIDTH) / static_cast<GLdouble>(WINDOW_HEIGHT);
	//gluPerspective(60.0, aspect, 1.0, 1000.0);
	float znear = 0.1f;
	float zfar = 10000.f;
	float fovyInDegrees = 60.f;

	glm::mat4 proj = glm::perspective(glm::radians(fovyInDegrees), aspectRatio, znear, zfar);

	glLoadMatrixf(glm::value_ptr(proj));


	/* Set modelview matrix as the current matrix */
	glMatrixMode(GL_MODELVIEW);
	/* Reset the current matrix */
	glLoadIdentity();

	/* Camera */
	glm::vec3 eye = pos;
	glm::vec3 cen = pos + vd;
	glm::vec3 cameraDirection = glm::normalize(cen - eye);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
	glm::mat4 view = glm::mat4(
		cameraRight[0], cameraUp[0], -cameraDirection[0], 0.0f,
		cameraRight[1], cameraUp[1], -cameraDirection[1], 0.0f,
		cameraRight[2], cameraUp[2], -cameraDirection[2], 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	view = glm::translate(view, -eye);

	glLoadMatrixf(glm::value_ptr(view));

	// Camera mouse and keyboard control
	double xpos, ypos;
	if (lMouseButton)
	{
		glfwGetCursorPos(window, &xpos, &ypos);
	}
	else
	{
		xpos = mouseX;
		ypos = mouseY;
	}

	vd = vd + cameraRight * (float)((xpos - mouseX) * sensitivity);
	vd = vd + cameraUp * (float)(-(ypos - mouseY) * sensitivity);

	mouseX = xpos;
	mouseY = ypos;

	// Key input
	if (wKey)
	{
		pos = pos + cameraDirection * cameraSpeed;
	}

	if (sKey)
	{
		pos = pos + cameraDirection * -cameraSpeed;
	}

	if (aKey)
	{
		pos = pos + cameraRight * -cameraSpeed;
	}

	if (dKey)
	{
		pos = pos + cameraRight * cameraSpeed;
	}
}

void setLights()
{
	GLfloat ambience1[] = { 0.6f, 0.0f, 0.0f, 1.0f };
	GLfloat diffuse1[] = { 0.8f, 0.0f, 0.0f, 1.0f };
	GLfloat specular1[] = { 1.0f, 0.0f, 0.0f, 1.0f };

	float position_1[] = { 150.f, 500, 100.f, 1.f };      // positional light (w = 1)
	glLightfv(GL_LIGHT0, GL_POSITION, position_1);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambience1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular1);
	glEnable(GL_LIGHT0);


	GLfloat spot_dir[] = { 0.f, -1.0f, 0.0f };
	GLfloat spot_cutoff =60.0f;
	GLfloat spot_exponent = 100.0f;

	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_dir);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);


	float ambient_2[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float diffuse_2[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float specular_2[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	//Re position LIGHT1 to follow camera
	float position_2[] = { 0.f, 0.f, 0.f, 1.f };      // positional light (w = 1)
	glLightfv(GL_LIGHT1, GL_POSITION, position_2);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular_2);
	glEnable(GL_LIGHT1);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Projection */
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION); //switch from model/view to projection mode
	glLoadIdentity();			 //reset matrix
	setCamera();
	setLights();

	glEnable(GL_TEXTURE_2D);
	setMaterial();
	glEnable(GL_CULL_FACE);
	drawSkybox(4000);
	// land
	setMaterial();
	glBindTexture(GL_TEXTURE_2D, texids[0]);
	glPushMatrix();
	glTranslated(0.0, -10.0, 0.0);
	glScaled(100.0, 100.0, 100.0);
	float scale = 1.0, area = 50;
	for (int x = -area; x < area; ++x)
	{
		for (int z = -area; z < area; ++z)
		{
			glPushMatrix();
			glTranslated(x * scale, 0.0, z * scale);
			plane.Draw();
			glPopMatrix();
		}
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	for (int i = -2; i < 2; ++i)
	{
		person.DrawMan(i * 40.0, rands[i + 2] * 100, (i + 2) % 2 == 1);
	}
	house.Draw(texids);



	/* Swap front and back buffers */
	glfwSwapBuffers(window);
	/* Poll for and porcess events */
	glfwPollEvents();
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
	glCullFace(GL_FRONT);

	/* Enable transparency blending */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Enable lighting */
	glEnable(GL_LIGHTING);

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	/* Choose a colour to clear the screen (RGBA range [0, 1]) */
	glClearColor(0.4f, 0.5f, 0.6f, 1.0f);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	texids[0] = loadimage("images/land.bmp");
	texids[1] = loadimage("images/wall.bmp");
	texids[2] = loadimage("images/step.bmp");
	texids[3] = loadimage("images/rainbow_bk.bmp");
	texids[4] = loadimage("images/rainbow_ft.bmp");
	texids[5] = loadimage("images/rainbow_lf.bmp");
	texids[6] = loadimage("images/rainbow_rt.bmp");
	texids[7] = loadimage("images/rainbow_up.bmp");
	texids[8] = loadimage("images/rainbow_dn.bmp");

	for (int i = 0; i < 10; ++i)
	{
		rands[i] = (rand() % 10 - 5);
	}

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		display();
	}

	glfwTerminate();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
