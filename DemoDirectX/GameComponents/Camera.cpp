#include "Camera.h"


Camera::Camera(int width, int height)
{
    mWidth = width ;
    mHeight = height ;

    mPosition = D3DXVECTOR2(0, 0);
}


Camera::~Camera()
{

}

void Camera::SetPosition(float x, float y)
{
    SetPosition(D3DXVECTOR2(x, y));
}

void Camera::SetPositionX(float x)
{
	mPosition.x = x;
}

void Camera::SetPositionY(float y)
{
	mPosition.y = y;
}

void Camera::SetPosition(D3DXVECTOR2 pos)
{
    mPosition = pos;
}

D3DXVECTOR2 Camera::GetPosition()
{
    return mPosition;
}

RECT Camera::GetBound()
{
    RECT bound; 

    bound.left = mPosition.x - mWidth / 2;
    bound.right = bound.left + mWidth;;
    bound.top = mPosition.y - mHeight / 2;
    bound.bottom = bound.top + mHeight;

    return bound;
}

int Camera::GetWidth()
{
    return mWidth;
}

int Camera::GetHeight()
{
    return mHeight;
}