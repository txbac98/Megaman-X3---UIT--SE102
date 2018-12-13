#include "Deathorbs.h"

Deathorbs::~Deathorbs()
{
}

Deathorbs::Deathorbs(float posX, float posY, float vx, float vy)
{
	mAnimation = new Animation("Resources/Megaman/MegaEffect/Deathorbs.png", "Resources/Megaman/MegaEffect/Deathorbs.txt", 0.02f, false);
	this->SetPosition(posX, posY);
	posX1 = posX;
	posY1 = posY;
	this->vx = vx;
	this->vy = vy;
}

void Deathorbs::Update(float dt)
{

	Entity::Update(dt);
}

void Deathorbs::Draw(D3DXVECTOR2 transform)
{
	mAnimation->SetPosition(posX, posY);
	mAnimation->Draw(transform);
}
