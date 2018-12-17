#include "Stone.h"
#include "../../GameComponents/ViewPort.h"

Stone::Stone(float posx, float posy, int type)
{
	/*mStone5 = new Sprite("Resources/MapObject/Stone5.png");
	this->SetPosition(posx, posy);
	this->SetWidth(mStone5->GetWidth());
	this->SetHeight(mStone5->GetHeight());
	bool wasBorn = false;
	this->Tag = Entity::EntityTypes::Enemy;
	mPlayer = ViewPort::getInstance()->mPlayer;
	mCamera = ViewPort::getInstance()->mCamera;
	hp = 5;
	dame = 1;
	isAlive = true;*/


	mSprite5 = new Sprite("Resources/Enemies/Stone5.png");
	mSprite3 = new Sprite("Resources/Enemies/Stone3.png");
	//mSprite1 = new Sprite("Resources/MapObject/Stone.png", "Resources/MapObject/Stone.txt", 0.1f, false);
	this->SetPosition(posx, posy);

	if (type == 5) {
		this->SetWidth(mSprite5->GetWidth());
		this->SetHeight(mSprite5->GetHeight());
		mSprite = mSprite5;
		this->Tag = EntityTypes::Stone5;
		count = 15;
	}
	else if (type == 3) {
		this->SetWidth(mSprite3->GetWidth());
		this->SetHeight(mSprite3->GetHeight());
		mSprite = mSprite3;
		this->Tag = EntityTypes::Stone3;
		count = 9;
	}


	mPlayer = ViewPort::getInstance()->mPlayer;
	mCamera = ViewPort::getInstance()->mCamera;
	mBox = new BoxObject();
	hp = 5;
	isAlive = true;
	isSpawn = true;
	dame = 1;
	mType = type;
}
Stone::~Stone() {

}
void Stone::Update(float dt) {
	if (mBox->isSpawn) {
		mBox->Update(dt);
	}
	if (isAlive) {
		this->SetWidth(mSprite->GetWidth());
		this->SetHeight(mSprite->GetHeight());
		for (int i = 0; i < sizeof(mPlayer->mListBullet); i++) {
			CollisionManager::getInstance()->checkCollision(&mPlayer->mListBullet[i], this, dt / 1000);
		}
		if (mPlayer) {
			CollisionManager::getInstance()->checkCollision(mPlayer, this, dt);
		}

		if (hp <= 0) {
			Die();

			if (!mBox->isAlive) {
				mBox->Spawn(posX, posY - 150);
				mBox->SetVy(450);
				mBox->Update(-1 + dt);
			}
			else
				mBox->Update(dt);

		}
		Entity::Update(dt);
	}
	if (explosion)
		for (int i = 0; i < count; i++) {
			explosion[i]->Update(dt);
		}
}
void Stone::OnCollision(Entity * other, SideCollisions side)
{
	if (isAlive) {
		if (other->Tag == EntityTypes::MegaBullet) {
			hp -= other->dame;
			other->Tag = EntityTypes::None;
			return;
		}
	}
}
void Stone::Draw(D3DXVECTOR2 transform)
{
	if (this->isAlive) {
		if (mType == 5) {
			mSprite5->SetPosition(this->GetPosition());
			mSprite5->Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), transform);
		}
		else if (mType == 3) {
			mSprite3->SetPosition(this->GetPosition());
			mSprite3->Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), transform);
		}
	}
	if (mBox->isSpawn) {
		mBox->Draw(transform);
	}
	if (explosion)
		for (int i = 0; i < count; i++) {
			explosion[i]->Draw(transform);
		}
	//if (explosion)
	//	explosion->Draw(transform);
}
void Stone::Die() {
	if (isAlive) {
		this->Tag = EntityTypes::None;

		explosion = new RedExplosion*[count];
		int dx = -10, dy;
		if (count == 15)
			dy = -150;
		else
			dy = -90;
		for (int i = 0; i < count; i++) {
			explosion[i] = new RedExplosion(posX + dx, posY + dy);
			dx += 10;
			dy += 20;
			if (i % 3 == 2)
			{
				dx = -10;
			}
		}

		isAlive = false;
	}
}