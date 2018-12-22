#include "Door.h"

Door::~Door()
{
}

Door::Door(float posX, float posY, bool st)
{
	mAnimation = new Animation("Resources/MapObject/Door.png", "Resources/MapObject/Door.txt",0.1f, true);
	mAnimationDoorOpen= new Animation("Resources/MapObject/Door.png", "Resources/MapObject/DoorOpen.txt", 0.2f, false);
	mAnimationDoorClose = new Animation("Resources/MapObject/Door.png", "Resources/MapObject/DoorClose.txt", 0.2f, false);
	this->SetPosition(posX, posY);
	this->SetWidth(mAnimation->GetWidth());
	this->SetHeight(mAnimation->GetHeight());
	this->Tag = Entity::EntityTypes::DoorObject;
	isOpening = false;
	isSpawn = true;
	isAlive = true;
	start = st;
}

void Door::Update(float dt)
{
	if(start)
		mAnimation->Update(dt);
	if (isOpening && mAnimation->mEndAnimate)
		this->Tag = EntityTypes::None;
}
void Door::ChangeStatus()
{
	if (start)
		start = false;
	else
		start = true;
}

void Door::OnCollision(Entity * other, SideCollisions side)
{
	if (other->Tag == EntityTypes::Megaman && this->Tag==EntityTypes::DoorObject) {
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
