#include "NotorBullet.h"
//#include "../../GameComponents/ViewPort.h"

NotorBullet::NotorBullet()
{
	mAnimation= new Animation("Resources/Enemies/NotorBullet.png", "Resources/Enemies/NotorBullet.txt", 0.01f, false);
	this->Tag = EntityTypes::None;
	this->SetWidth(mAnimation->GetWidth());
	this->SetHeight(mAnimation->GetHeight());
	wasBorn = false;
}

NotorBullet::~NotorBullet()
{
}

void NotorBullet::Spawn(float posx, float posy, float vx, float vy)
{
	mAnimation->Start();
	this->SetPosition(posx, posy);
	this->vx = vx;
	this->vy = vy;
	wasBorn = true;
	this->Tag = EntityTypes::EnemyBullet;

}

void NotorBullet::Update(float dt)
{
	if (wasBorn) {
		//gia tốc rơi
		vy += NotorDefine::BULLET_ACCELERATOR_Y;
		mAnimation->Update(dt);
		Entity::Update(dt);
	}
	if (mExplosion!=NULL) {
		mExplosion->Update(dt);
	}
}

void NotorBullet::OnCollision(Entity * other, SideCollisions side)
{
	if (this->Tag != EntityTypes::None) {
		mExplosion = new RedExplosion(posX, posY);
		wasBorn = false;
		this->Tag = EntityTypes::None;
	}
}

void NotorBullet::Draw(D3DXVECTOR2 transform)
{
	if (wasBorn) {
		mAnimation->SetPosition(posX, posY);
		mAnimation->Draw(transform);
	}
	if (mExplosion) {
		mExplosion->Draw(transform);
	}
}
