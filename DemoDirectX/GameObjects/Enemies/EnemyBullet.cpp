#include "EnemyBullet.h"
#include "../../GameComponents/ViewPort.h"

EnemyBullet::EnemyBullet()
{
	mSprite1 = new Sprite("Resources/Enemies/EnemyBullet.png");
	mAnimation2 = new Animation("Resources/Enemies/HeadgunnerBullet.png", "Resources/Enemies/HeadBullet.txt", 0.2f, false);
	mAnimation3= new Animation("Resources/Enemies/HelitBullet.png", "Resources/Enemies/HelitBullet.txt", 0.2f, false);
	wasBorn = false;
	dame = 1;
	mPlayer = ViewPort::getInstance()->mPlayer;
	typeBullet = 0;
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Spawn(int type,bool faceRight, float posx, float posy, float vx, float vy)
{
	isAlive = true;
	isFaceRight = faceRight;
	this->SetPosition(posx, posy);
	this->vx = vx;
	this->vy = vy;
	typeBullet = type;
	if (type == 1) {
		ay = NotorDefine::BULLET_ACCELERATOR_Y;
		
		this->SetWidth(mSprite1->GetWidth());
		this->SetHeight(mSprite1->GetHeight());
	}
	else if (type == 2) {
		ay = HeadDefine::BULLET_ACCELERATOR_Y;
		this->SetWidth(mAnimation2->GetWidth());
		this->SetHeight(mAnimation2->GetHeight());
		mAnimation2->SetPosition(posx, posy);
	}
	else if (type == 3) {
		ay = 0;
		this->SetWidth(mAnimation3->GetWidth());
		this->SetHeight(mAnimation3->GetHeight());
		mAnimation3->SetPosition(posx, posy);
	}
	wasBorn = true;
	this->Tag = EntityTypes::EnemiesBullet;

}

void EnemyBullet::Update(float dt)
{
	if (isAlive) {
		for (int i = 0; i < sizeof(mPlayer->mListBullet); i++) {
			CollisionManager::getInstance()->checkCollision(&mPlayer->mListBullet[i], this, dt / 1000);
		}
		//gia tốc rơi
		vy += ay;
		Entity::Update(dt);
		if (typeBullet == 2) {
			this->SetWidth(mAnimation2->GetWidth());
			this->SetHeight(mAnimation2->GetHeight());
			mAnimation2->Update(dt);
		}
		else if (typeBullet == 3) {
			this->SetWidth(mAnimation3->GetWidth());
			this->SetHeight(mAnimation3->GetHeight());
			mAnimation3->Update(dt);
		}
	}
	if (mExplosion!=NULL) {
		mExplosion->Update(dt);
	}
}

void EnemyBullet::OnCollision(Entity * other, SideCollisions side)
{
	if (isAlive) {
		if (other->Tag != EntityTypes::Notorbanger  
			&& other->Tag != EntityTypes::HeadgunnerLeft
			&& other->Tag != EntityTypes::HeadgunnerRight
			&& other->Tag != EntityTypes::Helit) {
			mExplosion = new RedExplosion(posX, posY);
			//wasBorn = false;
			this->isAlive = false;
			this->Tag = EntityTypes::None;
		}
	}
	
}

void EnemyBullet::Draw(D3DXVECTOR2 transform)
{
	if (isAlive) {
		if (typeBullet == 1) {
			mSprite1->SetPosition(posX, posY);
			mSprite1->Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), transform);
		}
		else if (typeBullet == 2) {
			mAnimation2->SetPosition(posX, posY);
			mAnimation2->FlipVertical(isFaceRight);
			mAnimation2->Draw( transform);
		}
		else if (typeBullet == 3) {
			mAnimation3->SetPosition(posX, posY);
			mAnimation3->FlipVertical(isFaceRight);
			mAnimation3->Draw(transform);
		}
	}
	if (mExplosion) {
		mExplosion->Draw(transform);
	}
}
