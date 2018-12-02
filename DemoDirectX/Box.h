#pragma once
#include "RectF.h"
class Box : public RectF
{
public:
	float vx, vy, ay, dx, dy;

	Box();
	~Box();
};

