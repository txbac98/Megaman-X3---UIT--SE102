#include "EnemyBullet.h"
//#include "../../GameComponents/ViewPort.h"

EnemyBullet::EnemyBullet()
{
	mSprite1 = new Sprite("Resources/Enemies/EnemyBullet.png");
	this->Tag = EntityTypes::None;
	wasBorn = false;
	typeBullet = 0;
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Spawn(int type,float posx, float posy, float vx, float vy)
{
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
	}
	else if (type == 3) {
		ay = 0;
	}
	wasBorn = true;
	this->Tag = EntityTypes::EnemiesBullet;

}

void EnemyBullet::Update(float dt)
{
	if (wasBorn) {
		//gia tốc rơi
		vy += ay;
		Entity::Update(dt);
	}
	if (mExplosion!=NULL) {
		mExplosion->Update(dt);
	}
}

void EnemyBullet::OnCollision(Entity * other, SideCollisions side)
{
	if (this->Tag != EntityTypes::None) {
		mExplosion = new RedExplosion(posX, posY);
		wasBorn = false;
		this->Tag = EntityTypes::None;
	}
}

void EnemyBullet::Draw(D3DXVECTOR2 transform)
{
	if (wasBorn) {
		if (typeBullet == 1) {
			mSprite1->SetPosition(posX, posY);
			mSprite1->Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), transform);
		}
		else if (typeBullet == 2) {
			mAnimation2->SetPosition(posX, posY);
			mAnimation2->Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), transform);
		}
	}
	if (mExplosion) {
		mExplosion->Draw(transform);
	}
}
