#include "Notorbanger.h"

Notorbanger::~Notorbanger()
{
}

Notorbanger::Notorbanger(float posX, float posY)
{
	mAnimation = new Animation("Resources/Enemies/Notorbanger.png", "Resources/Enemies/NotorbangerJumping.txt", 0.1f, true);
	this->SetPosition(posX, posY);
	this->SetWidth(mAnimation->GetWidth());
	this->SetHeight(mAnimation->GetHeight());
	this->Tag = Entity::EntityTypes::Enemy;
}

void Notorbanger::Update(float dt)
{
	mAnimation->Update(dt);
}

void Notorbanger::OnCollision(Entity * other, SideCollisions side)
{
}

void Notorbanger::Draw(D3DXVECTOR2 transform)
{
	mAnimation->SetPosition(this->GetPosition());
	mAnimation->Draw(transform);
}
