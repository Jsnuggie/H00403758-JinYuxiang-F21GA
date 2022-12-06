#pragma once


#include <vector>
#include "VertexStruct.h"

class Cylinder
{
public:
	Cylinder();
	void Draw();
	std::vector<VertexStruct> vertices;
};

