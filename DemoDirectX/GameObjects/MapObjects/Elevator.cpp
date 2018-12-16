#include "Elevator.h"
#include "../../GameComponents/GameGlobal.h"


Elevator::Elevator(float posX, float posY)
{
	//// "Resources/MapObject/Elevator.png", "Resources/MapObject/Elevator.txt"
	mAnimation = new Animation("Resources/MapObject/Elevator.bmp", "Resources/MapObject/Elevator.txt", 0.1f, true);
	this->SetPosition(posX, posY);
	this->SetWidth(mAnimation->GetWidth());
	this->SetHeight(mAnimation->GetHeight() - 20);
	this->Tag = Entity::EntityTypes::Elevator;
	isSpawn = true;
	isAlive = true;
}

Elevator::~Elevator()
{

}

void Elevator::OnSetPosition(D3DXVECTOR3 pos)
{
	mAnimation->SetPosition(pos);
}

void Elevator::Update(float dt)
{
	if (this->vy != 0) 
		mAnimation->Update(dt);
	if (this->posY > 195)  Entity::Update(dt);
	if (mPlayer!=NULL)
		CollisionManager::getInstance()->checkCollision(mPlayer, this, dt / 1000);
}

void Elevator::OnCollision(Entity * other, SideCollisions side)
{
	if (other->Tag == Entity::EntityTypes::Megaman && side == SideCollisions::Bottom)	//side đối với player
	{
		mPlayer = other;
		this->SetVy(-50);
	}
	
}

void Elevator::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	//mAnimation->Draw(D3DXVECTOR3(this->posX, this->posY, 0), sourceRect, scale, transform, angle, rotationCenter, colorKey);
	mAnimation->Draw();
}

void Elevator::Draw(D3DXVECTOR2 transform)
{
	mAnimation->SetPosition(this->GetPosition());
	mAnimation->Draw(D3DXVECTOR2(transform));
	//mAnimation->Draw(D3DXVECTOR3(this->posX, this->posY, 0));
}


