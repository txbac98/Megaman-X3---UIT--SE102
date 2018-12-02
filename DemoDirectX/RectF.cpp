#include "RectF.h"

float RectF::left()
{
	return x;
}

float RectF::right()
{
	return x + width;
}

float RectF::top()
{
	return y;
}

float RectF::bottom()
{
	return y + height;
}

float RectF::xCenter()
{
	return x + width / 2;
}

float RectF::yCenter()
{
	return y + height / 2;
}

RECT RectF::toRECT()
{
	RECT r;
	SetRect(&r, left(), top(), right(), bottom());
	return r;
}

RectF::RectF(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

RectF::RectF()
{
	x = y = width = height = 0;
}

RectF::~RectF()
{
}
