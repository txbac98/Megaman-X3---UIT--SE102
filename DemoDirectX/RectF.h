#pragma once
#include <Windows.h>

class RectF 
{
public:
	float x, y, width, height;

	float left();
	float right();
	float top();
	float bottom();
	float xCenter();
	float yCenter();
	RECT toRECT();
	RectF(float x, float y, float width, float height);

	RectF();
	~RectF();
};

