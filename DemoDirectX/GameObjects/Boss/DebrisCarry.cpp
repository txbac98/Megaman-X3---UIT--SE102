#include "DebrisCarry.h"

DebrisCarry::~DebrisCarry()
{
}

DebrisCarry::DebrisCarry(int type, float posX, float posY)
{
	if (type == 1) {
		//Mảng D to
		mSprite = new Sprite("Resources/Enemies/DebrisCarrryarm1.png");	
	}
	else if (type == 2) {
		//Thanh dọc
		mSprite = new Sprite("Resources/Enemies/DebrisCarrryarm2.png");
	}
	else if (type == 3) {
		//Thang ngang
		mSprite = new Sprite("Resources/Enemies/DebrisCarrryarm3.png");
	}
	this->SetWidth(mSprite->GetWidth());
	this->SetHeight(mSprite->GetHeight());
	this->SetPosition(posX, posY);
	this->isAlive = true;
	this->isSpawn = true;
	this->Tag = EntityTypes::DebrisCarryarm;
}

void DebrisCarry::Draw(D3DXVECTOR2 transform)
{
	mSprite->SetPosition(posX, posY);
	mSprite->Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(),transform);
}

