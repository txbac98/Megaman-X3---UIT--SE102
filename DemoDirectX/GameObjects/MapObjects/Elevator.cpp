#include "Elevator.h"
#include "../../GameComponents/GameGlobal.h"


Elevator::Elevator(float posX, float posY)
{
	//// "Resources/MapObject/Elevator.png", "Resources/MapObject/Elevator.txt"
	mAnimation = new Animation("Resources/MapObject/Elevator.bmp", "Resources/MapObject/Elevator.txt", 0.1f, true);

	this->SetPosition(posX, posY);
	this->SetWidth(mAnimation->GetWidth());
	
	//mAnimation->SetScale(0.5, 0.5);
	mAnimation->Stop();
	this->SetHeight(mAnimation->GetHeight() - 20);
	this->Tag = Entity::EntityTypes::Elevator;
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
	mAnimation->Update(dt);
	this->SetHeight(mAnimation->GetHeight() - 20);
	Entity::Update(dt);
}

void Elevator::OnCollision(Entity * other, SideCollisions side)
{
	if (other->Tag == Entity::EntityTypes::Player && side == SideCollisions::Bottom)	//side đối với player
	{
		mAnimation->Start();
		this->SetVy(-80);
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

