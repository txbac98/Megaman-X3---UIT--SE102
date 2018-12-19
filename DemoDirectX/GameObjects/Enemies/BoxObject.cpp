#include "BoxObject.h"
#include "../../GameComponents/ViewPort.h"
BoxObject::~BoxObject()
{
}

BoxObject::BoxObject()
{
	mSprite = new Sprite("Resources/Enemies/Box1.png");
	this->SetWidth(mSprite->GetWidth());
	this->SetHeight(mSprite->GetHeight());
	mPlayer = ViewPort::getInstance()->mPlayer;
	isAlive = false;
	isSpawn = false;
	dame = 1;
	this->Tag = EntityTypes::Box;
}

BoxObject::BoxObject(float posX, float posY)
{
	mSprite = new Sprite("Resources/Enemies/Box1.png");
	//mAnimation = new Animation("Resources/Enemies/BoxObject.png", "Resources/Enemies/BoxObject.txt", 0.07f, false);
	this->SetPosition(posX, posY);
	this->SetWidth(mSprite->GetWidth());
	this->SetHeight(mSprite->GetHeight());
	mSprite->SetPosition(posX, posY);
	hp = 3;
	isAlive = true;
	isSpawn = true;
	mPlayer = ViewPort::getInstance()->mPlayer;
	this->Tag = EntityTypes::Box;
}

void BoxObject::Spawn(float posX, float posY)
{
	isAlive = true;
	isSpawn = true;
	hp = 3;
	this->SetPosition(posX, posY);
	mSprite->SetPosition(posX, posY);
}

void BoxObject::Update(float dt)
{
	if (mExplosion)
		mExplosion->Update(dt);
	if (isAlive) {
		//kiểm tra va chạm viên đạn, player
		for (int i = 0; i < sizeof(mPlayer->mListBullet); i++) {
			CollisionManager::getInstance()->checkCollision(&mPlayer->mListBullet[i], this, dt);
		}
		CollisionManager::getInstance()->checkCollision(mPlayer, this, dt);
	}
	if (vy > 0)
		Entity::Update(dt);
}

void BoxObject::OnCollision(Entity * other, SideCollisions side)
{
	if (other->Tag == EntityTypes::MegaBullet) {
		hp -= other->dame;
		other->Tag = EntityTypes::None;
		if (hp <= 0) {
			isAlive = false;
			mExplosion = new RedExplosion(posX,posY);
		}
	}
}

void BoxObject::Draw(D3DXVECTOR2 transform)
{
	if (mExplosion)
		mExplosion->Draw(transform);
	if (isAlive)
	{
		mSprite->SetPosition(posX, posY);
		mSprite->Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), transform);
	}
		
}
