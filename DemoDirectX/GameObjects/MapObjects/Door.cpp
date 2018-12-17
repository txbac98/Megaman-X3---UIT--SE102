#include "Door.h"

Door::~Door()
{
}

Door::Door(float posX, float posY)
{
	mAnimation = new Animation("Resources/MapObject/Door.png", "Resources/MapObject/Door.txt",0.1f, true);
	mAnimationDoorOpen= new Animation("Resources/MapObject/Door.png", "Resources/MapObject/DoorOpen.txt", 0.2f, false);
	mAnimationDoorClose = new Animation("Resources/MapObject/Door.png", "Resources/MapObject/DoorClose.txt", 0.2f, false);
	this->SetPosition(posX, posY);
	this->SetWidth(mAnimation->GetWidth());
	this->SetHeight(mAnimation->GetHeight());
	this->Tag = Entity::EntityTypes::Door;
	isOpening = false;
	isSpawn = true;
	isAlive = true;
}

void Door::Update(float dt)
{
	mAnimation->Update(dt);
	if (isOpening && mAnimation->mEndAnimate)
		this->Tag = EntityTypes::None;
}

void Door::OnCollision(Entity * other, SideCollisions side)
{
	if (other->Tag == EntityTypes::Megaman) {
		if (!isOpening) {
			mAnimation = mAnimationDoorOpen;
			isOpening = true;
		}		
	}
}

void Door::Draw(D3DXVECTOR2 transform)
{
	mAnimation->SetPosition(this->GetPosition());
	mAnimation->Draw(D3DXVECTOR2(transform));
}
