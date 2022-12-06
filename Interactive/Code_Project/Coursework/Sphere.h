#pragma once

#include <vector>
#include "VertexStruct.h"

class Sphere
{
public: 

	Sphere();

	void Draw();

	std::vector<VertexStruct> vertices;
};

