#include "Entity.h"

Entity::Entity()
{
    Tag = None;
}

D3DXVECTOR2 Entity::GetPosition()
{
    return D3DXVECTOR2(posX, posY);
}

void Entity::Draw(D3DXVECTOR2 transform)
{

}

RECT Entity::GetBound()
{
    RECT bound;

    bound.left = posX - width / 2;
    bound.right = posX + width / 2;
    bound.top = posY - height / 2;
    bound.bottom = posY + height / 2;

    return bound;
}
RectF Entity::GetBoundF()
{
	RectF bound;
	bound.x = posX - width / 2;
	bound.y = posY - height / 2;
	bound.width = width;
	bound.height = height;
	return bound;
}

Entity::SideCollisions Entity::GetPhysicsBodySide() {
	return physicsSide;
}
void Entity::SetPhysicsBodySide(Entity::SideCollisions side)
{
	if (side != physicsSide)
		physicsSide = side;
}

void Entity::OnCollision(Entity * other, Entity::SideCollisions side) {

}
RECT Entity::getCollisionRect(RECT rect)
{
	RECT mRect,result;
	mRect = this->GetBound();
	//chon max Left
	result.left = mRect.left > rect.left ? mRect.left : rect.left;
	//chon max right
	result.right = mRect.right < rect.right ? mRect.right : rect.right;
	//chon min bottom
	result.bottom = mRect.bottom < rect.bottom ? mRect.bottom : rect.bottom;
	//chon max top
	result.top = mRect.top > rect.top ? mRect.top : rect.top;

	return result;
}
bool Entity::IntersectRect(RECT rect)		//Bullet with rect camera
{
	RECT myRect = this->GetBound();
	if (myRect.left > rect.right || myRect.right < rect.left) return false;
	return true;
}
void Entity::OnAABBCheck(Entity *other) {

}
void Entity::OnSetPosition(D3DXVECTOR2 pos)
{

}

void Entity::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{

}


void Entity::Update(float dt)
{
    //velocity = pixel / s
	//Rơi xuống
    posX += vx * dt;
    posY += vy * dt;
}

void Entity::SetPosition(float x, float y)
{
	this->posX = x;
	this->posY = y;
}

void Entity::SetPosition(D3DXVECTOR2 pos)
{
	this->posX = pos.x;
	this->posY = pos.y;
}

void Entity::AddPositionX(float x) {
	this->posX += x;
}
void Entity::AddPositionY(float Y) {
	this->posY += Y;
}
void Entity::AddPosition(D3DXVECTOR2 pos)
{
	posX += pos.x;
	posY += pos.y;
}

void Entity::AddPosition(float x, float y)
{
	posX += x;
	posY += y;
}

void Entity::SetWidth(int width)
{
    this->width = width;
}

int Entity::GetWidth()
{
    return width;
}

void Entity::SetHeight(int height)
{
    this->height = height;
}

int Entity::GetHeight()
{
    return height;
}

float Entity::GetVx()
{
    return vx;
}

void Entity::SetVx(float vx)
{
    this->vx = vx;
}

void Entity::AddVx(float vx)
{
    this->vx += vx;
}

float Entity::GetVy()
{
    return vy;
}

void Entity::SetVy(float vy)
{
    this->vy = vy;
}

void Entity::AddVy(float vy)
{
    this->vy += vy;
}
