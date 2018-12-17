#include "ChildHornet.h"
#include "../../GameComponents/ViewPort.h"

ChildHornet::~ChildHornet()
{
}

ChildHornet::ChildHornet(int type, float posX, float posY, float vx, float vy)
{
	mAnimation = new Animation("Resources/Enemies/ChildHornet.png", "Resources/Enemies/ChildHornet.txt", 0.05f, true);
	this->vx = vx;
	this->vy = vy;
	if (vx < 0) {
		isFaceRight = true;
	}
	else isFaceRight = false;
	isAlive = true;
	isSpawn = true;
	waittingDie = false;
	tDelay = 0;
	dame = 1;
	typeAttack = type;
	this->SetPosition(posX, posY);
	mAnimation->SetPosition(posX, posY);
	this->SetWidth(mAnimation->GetWidth());
	this->SetHeight(mAnimation->GetHeight());
	mPlayer = ViewPort::getInstance()->mPlayer;
	this->Tag = EntityTypes::HornetChild;
}

ChildHornet::ChildHornet()
{
	isAlive = false;
}

void ChildHornet::Update(float dt)
{
	if (isAlive) {
		if (typeAttack == 1) {	//Lao thẳng 1 hướng
			if (waittingDie) {
				tDelay += dt;
				if (tDelay > ChildHornetDefine::TIME_DELAY) {
					Die();
				}
			}
		}
		else if (typeAttack == 2) {	//Bay thẳng tới nhân vật

		}
		mAnimation->Update(dt);
		Entity::Update(dt);

		//kiểm tra va chạm  object với map
		std::vector<Entity*> mListMapObject;
		ViewPort::getInstance()->GetMapObject(mListMapObject, this);
		for (size_t j = 0; j < mListMapObject.size(); j++) {
			CollisionManager::getInstance()->checkCollision(this, mListMapObject[j], dt);
		}

		//kiểm tra va chạm viên đạn player
		for (int i = 0; i < sizeof(mPlayer->mListBullet); i++) {
			CollisionManager::getInstance()->checkCollision(&mPlayer->mListBullet[i], this, dt);
		}
		CollisionManager::getInstance()->checkCollision(mPlayer, this, dt);


	}
	if (mExplosion) {
		mExplosion->Update(dt);
	}
}

void ChildHornet::OnCollision(Entity * other, SideCollisions side)
{
	if (other->Tag == EntityTypes::Wall) {
		waittingDie = true;
		vx = 0;
		vy = 0;
	}
	if (other->Tag == EntityTypes::Megaman) {
		Die();
	}
	else if (other->Tag == EntityTypes::MegaBullet) {		
		Die();
		other->Tag = EntityTypes::None;
	}
}

void ChildHornet::Die()
{
	waittingDie = false;
	isAlive = false;
	mExplosion = new RedExplosion(posX, posY);
}

void ChildHornet::Draw(D3DXVECTOR2 transform)
{
	if (isAlive) {
		mAnimation->SetPosition(posX, posY);
		mAnimation->FlipVertical(isFaceRight);
		mAnimation->Draw(transform);
	}
	
	if (mExplosion) mExplosion->Draw(transform);
}
