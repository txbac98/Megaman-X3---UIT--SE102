#include "RedExplosion.h"

RedExplosion::~RedExplosion()
{
}

RedExplosion::RedExplosion(float posX, float posY)
{
	mAnimation= new Animation("Resources/Effect/RedExplosion.png", "Resources/Effect/RedExplosion.txt", 0.05f, false);
	this->SetPosition(posX, posY);
	mEndAnimate = mAnimation->mEndAnimate;
	mAnimation->SetPosition(posX, posY);
}

void RedExplosion::ReStart(float posX, float posY)
{
	mAnimation->Start();
	this->SetPosition(posX, posY);
	mAnimation->SetPosition(posX, posY);
}

void RedExplosion::Update(float dt)
{
	mAnimation->Update(dt);
	mEndAnimate = mAnimation->mEndAnimate;
}

void RedExplosion::Draw(D3DXVECTOR2 transform)
{
	if (!mAnimation->mEndAnimate)
	mAnimation->Draw(transform);
}
