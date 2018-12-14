#include "HeadGunner.h"
#include "../../GameComponents/ViewPort.h"

HeadGunner::~HeadGunner()
{
}

HeadGunner::HeadGunner(float posX, float posY, bool faceRight)
{
	mAnimationStand = new Animation("Resources/Enemies/Headgunner.png", "Resources/Enemies/HeadStand.txt", 0.3f, false);
	mAnimationShoot1= new Animation("Resources/Enemies/Headgunner.png", "Resources/Enemies/HeadShoot1.txt", 0.3f, false);
	mAnimationShoot2 = new Animation("Resources/Enemies/Headgunner.png", "Resources/Enemies/HeadShoot2.txt", 0.3f, false);

	mAnimationStand->Start();
	mAnimation = mAnimationStand;
	
	this->SetPosition(posX, posY);
	mAnimation->SetPosition(posX, posY);

	this->SetWidth(mAnimation->GetWidth());
	this->SetHeight(mAnimation->GetHeight());
	
	mPlayer= ViewPort::getInstance()->mPlayer;
	mBullet = new EnemyBullet();
	isFaceRight = faceRight;
	isAlive = true;
	hp = 4;
	this->Tag = EntityTypes::Headgunner;
}

void HeadGunner::Update(float dt)
{
	if (mBullet) {
		mBullet->Update(dt);
		CollisionManager::getInstance()->checkCollision(mPlayer, mBullet, dt);

		std::vector<Entity*> mListEntity;
		ViewPort::getInstance()->GetMapObject(mListEntity, mBullet);
		for (int j = 0; j < mListEntity.size(); j++)
			if (mListEntity[j] != this)
				CollisionManager::getInstance()->checkCollision(mListEntity[j], mBullet, dt);
	}
	if (explosion) {
		explosion->Update(dt);
	}
	if (this->isAlive) {
		this->SetWidth(mAnimation->GetWidth());
		this->SetHeight(mAnimation->GetHeight());
		mAnimation->Update(dt);

		//kiểm tra va chạm viên đạn player
		for (int i = 0; i < sizeof(mPlayer->mListBullet); i++) {
			CollisionManager::getInstance()->checkCollision(&mPlayer->mListBullet[i], this, dt / 1000);
		}
		//Kiểm tra va chạm với nhân vật
		if (mPlayer) {
			CollisionManager::getInstance()->checkCollision(mPlayer, this, dt);
		}

		if (hp <= 0) {
			isAlive = false;
			explosion = new RedExplosion(posX,posY);
		}
		
		if (mAnimation->mEndAnimate) {
			if (mAnimation == mAnimationStand) {
				mAnimationShoot1->Start();
				mAnimation = mAnimationShoot1;			
			}
			else if (mAnimation == mAnimationShoot1) {
				mAnimationShoot2->Start();
				mAnimation = mAnimationShoot2;
				if (isFaceRight)
					mBullet->Spawn(2, isFaceRight,posX, posY, HeadDefine::BULLET_SPEED_X, -HeadDefine::BULLET_SPEED_Y);
				else
					mBullet->Spawn(2, isFaceRight,posX, posY, -HeadDefine::BULLET_SPEED_X, -HeadDefine::BULLET_SPEED_Y);
			}
			else if (mAnimation == mAnimationShoot2) {
				mAnimationStand->Start();
				mAnimation = mAnimationStand;
				if (!mBullet->wasBorn)
					if (isFaceRight)
						mBullet->Spawn(2, isFaceRight, posX, posY, HeadDefine::BULLET_SPEED_X, -HeadDefine::BULLET_SPEED_Y);
					else
						mBullet->Spawn(2, isFaceRight, posX, posY, -HeadDefine::BULLET_SPEED_X, -HeadDefine::BULLET_SPEED_Y);
			}
		}
		
	}

	
}

void HeadGunner::OnCollision(Entity * other, SideCollisions side)
{
	if (other->Tag == EntityTypes::MegaBullet) {
		hp -= other->dame;
		other->Tag = EntityTypes::None;
		return;

	}
}

void HeadGunner::Draw(D3DXVECTOR2 transform)
{
	if (mBullet)	mBullet->Draw(transform);

	if (explosion) {
		explosion->Draw(transform);
	}
	if (isAlive) {
		mAnimation->FlipVertical(isFaceRight);
		mAnimation->SetPosition(this->GetPosition());
		mAnimation->Draw(transform);
	}
	
}
