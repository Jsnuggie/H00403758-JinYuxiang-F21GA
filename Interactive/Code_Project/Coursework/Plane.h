#pragma once

#include <vector>
#include "VertexStruct.h"


class Plane
{
public:
	Plane();

	void Draw();

	std::vector<VertexStruct> vertices;
};

