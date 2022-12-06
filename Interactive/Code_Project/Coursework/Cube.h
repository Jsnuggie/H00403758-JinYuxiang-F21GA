#pragma once

#include <vector>
#include "VertexStruct.h"

class Cube
{
public:

	Cube();

	void Draw();

	std::vector<VertexStruct> vertices;
};

