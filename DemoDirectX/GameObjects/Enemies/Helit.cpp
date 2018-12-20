#include "Helit.h"
#include "../../GameComponents/ViewPort.h"

Helit::~Helit()
{
}

Helit::Helit(float posX, float posY)
{
	mAnimation = new Animation("Resources/Enemies/Helit.png", "Resources/Enemies/Helit.txt", 0.1f, true);
	
	this->SetPosition(posX, posY);
	this->SetWidth(mAnimation->GetWidth());
	this->SetHeight(mAnimation->GetHeight());
	this->Tag = Entity::EntityTypes::Helit;
	isFaceRight = false;
	mPlayer = ViewPort::getInstance()->mPlayer;
	mCamera = ViewPort::getInstance()->mCamera;
	//mGameMap = map;
	hp = 3;
	isAlive = true;
	isSpawn = true;
	direction = -1;
	iBullet = 0;
	posX1 = posX;
	posY1 = posY;
	dame = 1;
	//Bullet
	mBullet =new EnemyBullet();
}

void Helit::Update(float dt)
{
	if (isAlive) {
		//kiểm tra va chạm viên đạn player
		this->SetWidth(mAnimation->GetWidth());
		this->SetHeight(mAnimation->GetHeight());
		for (int i = 0; i < sizeof(mPlayer->mListBullet); i++) {
			CollisionManager::getInstance()->checkCollision(&mPlayer->mListBullet[i], this, dt / 1000);
		}
		if (hp <= 0) {
			Die();
			return;
		}
		if (posY <= posY1 && vy<0) {	//đi lên
			vy = 0;
		}
		if (abs(posX - mPlayer->posX) < 100 && abs(posY - mPlayer->posY)<100)	// khoảng cách dưới 100
		{
			if (mPlayer->posX < posX)	//bên trái
			{
				isFaceRight = false;
				direction = -1;
			}
			else
			{		//bên phải
				isFaceRight = true;
				direction = 1;
			}
			if ( vy==0) {
				vy = HelitDefine::SPEED_Y;
			}
			
		}
		if (posY > mPlayer->posY /*&& vy > 0*/) {
			vy = 0;
			if (!mBullet->isAlive || abs(mBullet->posX - posX) > 200) {
				mBullet->Spawn(3, isFaceRight, this->posX, this->posY, direction*HelitDefine::BULLET_SPEED_X, 0);
				vy = -HelitDefine::SPEED_Y;
			}
		}
		
		mAnimation->Update(dt);
		Entity::Update(dt);
	}

		////Kiểm tra va chạm
		std::vector<Entity*> mListEntity;

		mBullet->Update(dt);

		CollisionManager::getInstance()->checkCollision(mPlayer, mBullet, dt );
		CollisionManager::getInstance()->checkCollision(mPlayer, this, dt);

		ViewPort::getInstance()->GetMapObject(mListEntity, mBullet);
		for (int j = 0; j < mListEntity.size(); j++)
			if (mListEntity[j] != this)
				CollisionManager::getInstance()->checkCollision(mListEntity[j], mBullet, dt);
		
	
	if (explosion) {
		explosion->Update(dt);
	}
}


void Helit::OnCollision(Entity * other, SideCollisions side)
{
	if (isAlive) {
		if (other->Tag == EntityTypes::MegaBullet) {
			hp-=other->dame;
			other->Tag = EntityTypes::None;
			return;
		}
	}
}

void Helit::Draw(D3DXVECTOR2 transform)
{
	mBullet->Draw(transform);
	if (isAlive) {
		mAnimation->SetPosition(this->GetPosition());
		mAnimation->FlipVertical(isFaceRight);
		mAnimation->Draw(transform);
	}
	if (explosion)
		explosion->Draw(transform);
}

void Helit::Die()
{
	if (isAlive) {
		explosion = new RedExplosion(posX, posY);
		isAlive = false;
	}
}
