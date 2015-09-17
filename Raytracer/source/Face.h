#pragma once

#include <vector>

#include "Point.h"

typedef unsigned int UINT;

struct Face
{
	UINT index1, index2, index3;

	bool Intersect(const std::vector<Point<>>& vertices);
};