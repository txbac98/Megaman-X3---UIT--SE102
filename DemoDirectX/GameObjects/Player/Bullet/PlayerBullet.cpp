#include "PlayerBullet.h"

PlayerBullet::PlayerBullet()
{
	wasBorn = false;
	mAnimationBullet1= new Animation("Resources/Megaman/MegaBullet/MegaBullet.png", "Resources/Megaman/MegaBullet/MegaBullet1.txt", 0.001f, false);
	mAnimationBullet2 = new Animation("Resources/Megaman/MegaBullet/MegaBullet.png", "Resources/Megaman/MegaBullet/MegaBullet2.txt", 0.001f, false);	
	mAnimationBullet0 = new Animation("Resources/Megaman/MegaBullet/MegaBullet.png", "Resources/Megaman/MegaBullet/MegaBullet0.txt", 1.0f, false);		//1 frame
	mCurrentAnimation = mAnimationBullet0;
	this->Tag = Entity::EntityTypes::MegaBullet;
	//mAnimationBullet1->Start();
	//mAnimationBullet2->Start();
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Spawn(bool goLeft, int typeBullet)
{
	
	this->Tag = EntityTypes::MegaBullet;
	if (typeBullet == 0) {
		dame = 1;
		mCurrentAnimation = mAnimationBullet0;
	}
	if (typeBullet == 1) {
		dame = 2;
		mCurrentAnimation = mAnimationBullet1;
	}
	if (typeBullet == 2) {
		dame = 3;
		mCurrentAnimation = mAnimationBullet2;
	}
	mCurrentAnimation->Start();
	isGoLeft = goLeft;
	if (isGoLeft)
		this->SetVx(-BulletDefine::PLAYER_BULLET_SPEED);
	else this->SetVx(BulletDefine::PLAYER_BULLET_SPEED);
	wasBorn = true;
}

void PlayerBullet::Update(float dt, RECT rectCamera)
{
	if (wasBorn) {
		this->SetWidth(mCurrentAnimation->mWidth);
		this->SetHeight(mCurrentAnimation->mHeight);
		if (!this->IntersectRect(rectCamera)) {
			mCurrentAnimation->Stop();
			this->wasBorn = false;
			return;
		}
		mCurrentAnimation->Update(dt);
		Entity::Update(dt);
	}
}

void PlayerBullet::OnCollision(Entity * other, SideCollisions side)
{
		wasBorn = false;
}

void PlayerBullet::Draw(D3DXVECTOR2 transform)
{
	if (wasBorn) {
		mCurrentAnimation->FlipVertical(isGoLeft);
		mCurrentAnimation->SetPosition(this->GetPosition());

		mCurrentAnimation->Draw(transform);
	}
}
