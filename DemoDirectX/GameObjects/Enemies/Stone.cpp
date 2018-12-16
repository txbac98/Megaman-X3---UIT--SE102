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


	mAnimation5 = new Animation("Resources/Enemies/Stone5.png", "Resources/Enemies/Stone5.txt", 0.2f, false);
	mAnimation3 = new Animation("Resources/Enemies/Stone3.png", "Resources/Enemies/Stone3.txt", 0.2f, false);
	//mAnimation1 = new Animation("Resources/MapObject/Stone.png", "Resources/MapObject/Stone.txt", 0.1f, false);
	this->SetPosition(posx, posy);

	if (type == 5) {
		this->SetWidth(mAnimation5->GetWidth());
		this->SetHeight(mAnimation5->GetHeight());
		mAnimation = mAnimation5;
		this->Tag = EntityTypes::Stone5;

	}
	else if (type == 3) {
		this->SetWidth(mAnimation3->GetWidth());
		this->SetHeight(mAnimation3->GetHeight());
		mAnimation = mAnimation3;
		this->Tag = EntityTypes::Stone3;
	}
	/*else if (type == 1) {
		this->SetWidth(mAnimation1->GetWidth());
		this->SetHeight(mAnimation1->GetHeight());
		mAnimation = mAnimation1;
		this->SetVy(500);
	}*/

	
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
		this->SetWidth(mAnimation->GetWidth());
		this->SetHeight(mAnimation->GetHeight());
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
				mBox->Update(-1+dt);
				}
			else 
				mBox->Update(dt);
			/*	this->SetWidth(mAnimation1->GetWidth());
				this->SetHeight(mAnimation1->GetHeight());
				mAnimation = mAnimation1;*/
			/*this->SetVy(100);
			mAnimation->Update(dt);
			Entity::Update(dt);
			return;*/
		}
		mAnimation->Update(dt);
		Entity::Update(dt);
	}

	if (explosion)
		explosion->Update(dt);
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
			mAnimation5->SetPosition(this->GetPosition());
			mAnimation5->Draw(transform);
		}
		else if (mType == 3) {
			mAnimation3->SetPosition(this->GetPosition());
			mAnimation3->Draw(transform);
		}
	/*	else if (mType == 1) {
			mAnimation1->SetPosition(this->GetPosition());
			mAnimation1->Draw(transform);
		}*/
	}
	if (mBox->isSpawn) {
		mBox->Draw(transform);
	}
	//else {
	//	mAnimation1->SetPosition(this->GetPosition());
	//	mAnimation1->Draw(transform);
	//}
	if (explosion)
		explosion->Draw(transform);
}
void Stone::Die() {
	if (isAlive) {
		this->Tag = EntityTypes::None;
		explosion = new RedExplosion(posX, posY);
		isAlive = false;
	}
}