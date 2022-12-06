#pragma once

#include "Sphere.h"
#include "Cylinder.h"

class Person
{
public:
	Person();
	void Draw();
	void DrawMan(float x, float z, bool forward);
private:
	void SetColor(float red, float green, float blue);


	void DrawArm(float tval);

	void DrawLeg(float tval);
private:

	Sphere sphere;
	Cylinder cylinder;

	double _pre_time;
	double _distance;
	double _pre_distance;
	double _;
	double _angle;

	int rands[10];
};

