#include "Genjibo.h"
#include "../../GameComponents/ViewPort.h"
Genjibo::~Genjibo()
{
}

Genjibo::Genjibo(float posX, float posY)
{
	mAnimationSpawn = new Animation("Resources/Boss/Genjibo.png", "Resources/Boss/GenjiboSpawn.txt", 0.1f, false);
	mAnimationRotate = new Animation("Resources/Boss/Genjibo.png", "Resources/Boss/GenjiboRotateLeft.txt", 0.001f, true);
	mAnimationSub = new Animation("Resources/Boss/Genjibo.png", "Resources/Boss/SubGenjibo.txt", 0.01f, false);
	mSpriteZone = new Sprite("Resources/Boss/GenjiboZone.png");

	mAnimation = mAnimationSpawn;
	isFaceRight = false;
	this->SetPosition(posX, posY);
	mAnimation->SetPosition(posX, posY);
	mSpriteZone->SetPosition(posX, posY - 5);
	mAnimationSub->SetPosition(posX, posY - 200);
	this->SetWidth(mAnimation->GetWidth());
	this->SetHeight(mAnimation->GetHeight());
	die = false;
	explosion = new RedExplosion*[7];
	for (int i = 0; i < 7; i++)
		explosion[i] = new RedExplosion(0, 0);
	posX1 = posX;
	posY1 = posY;
	mPlayer = ViewPort::getInstance()->mPlayer;
	posXMid = ViewPort::getInstance()->mCamera->GetPosition().x;
	hp = 30;
	vx = 100;
	vy = 20;
	dame = 2;
	isAlive = true;
	isSpawn = true;
	onDraw = false;
	die = false;
	typeAttack = 0;
	this->Tag = EntityTypes::Genjibo;
	count = 0;

	mDoor = new Door(2554, 923, false);
	mDoor->Tag = EntityTypes::Wall;
}

void Genjibo::Update(float dt)
{
	
	if (isAlive) {
		//Con ong bay xuống
		if (posX - mPlayer->posX < 120)
			mPlayer->noDownKey = true;
		if (abs(posY1 - mAnimationSub->GetPosition().y) > 30) {
			mAnimationSub->SetPosition(posX, mAnimationSub->GetPosition().y + 1);
			mAnimationSub->Update(dt);
			return;
		}
		else onDraw = true;
		
		if (!die) {
			mAnimation->SetPosition(posX, posY);
			mAnimation->Update(dt);
			
		}
		
		if (!mAnimationSpawn->mEndAnimate && mAnimation == mAnimationSpawn) {
			return;
		}
		else {
			if (mAnimation != mAnimationRotate) {
				mAnimation = mAnimationRotate;
				this->SetWidth(mAnimationRotate->GetWidth());
				this->SetHeight(mAnimationRotate->GetHeight());
			}
			mPlayer->noDownKey = false;
		}
		Entity::Update(dt);

		if (hp > 20) {
			typeAttack = 1;
		}
		else if (hp > 10) {
			typeAttack = 2;
		}
		else typeAttack = 3;

		if (hp <= 0) {
			//Die();
			this->Tag = EntityTypes::None;
			die = true;
		}


		//Tấn công:
		if (typeAttack == 2) {	//Tới giữa thì nhảy lên
			if (vy == 0 && vx < 0) {
				if (posX < posXMid) {
					vy = -GenjiboDefine::SPEED_Y;
				}
			}
		}

		//Va chạm cửa
		CollisionManager::getInstance()->checkCollision(this, mDoor, dt);

		//kiểm tra va chạm  object với map
		std::vector<Entity*> mListMapObject;
		ViewPort::getInstance()->GetMapObject(mListMapObject, this);
		for (size_t j = 0; j < mListMapObject.size(); j++) {

			CollisionManager::getInstance()->checkCollision(this, mListMapObject[j], dt/1000);
		}

		
		//kiểm tra va chạm viên đạn player
		for (int i = 0; i < sizeof(mPlayer->mListBullet); i++) {
			CollisionManager::getInstance()->checkCollision(&mPlayer->mListBullet[i], this, dt);
		}
		//Kiểm tra va chạm với nhân vật
		CollisionManager::getInstance()->checkCollision(mPlayer, this, dt);
				
	}
	
	if (hp <= 0)
	{

		if (explosion) {
			explosion[count]->Update(dt);		
			if (explosion[count]->mEndAnimate)
			{
				int x = rand() % mAnimation->GetWidth();
				int y = rand() % mAnimation->GetHeight();
				count++;
				explosion[count]->ReStart(mAnimation->GetPosition().x - mAnimation->GetWidth()/2 +x,mAnimation->GetPosition().y - mAnimation->GetHeight()/2 +y);
			}
			if (count == 6)
			{
				explosion = NULL;
				isAlive = false;
				mDoor->ChangeStatus();
				mDoor->Tag = EntityTypes::DoorObject;
			}
		}
	}
	CollisionManager::getInstance()->checkCollision(mPlayer, mDoor, dt);
	mDoor->Update(dt);
}

void Genjibo::OnCollision(Entity * other, SideCollisions side)
{
	if (other->Tag == EntityTypes::Wall || other->Tag == EntityTypes::DoorObject) {

		if (side == SideCollisions::Bottom)
			vy = 0;

		if (typeAttack == 1) {	//Chạy qua chạy lại phía dưới
			if (typeAttack == 1) {
				if (side == SideCollisions::Left || side == SideCollisions::Right) {
					vx = -vx;
				}
			}
		}
		else if (typeAttack == 3) //Đi vòng tròn
		{
			if (side == SideCollisions::Left && vy == 0) {
				this->AddPositionX(2);	//Tránh bị xét 2 va chạm ở góc
				vy = -GenjiboDefine::SPEED_Y;
				vx = 0;
			}

			if (side == SideCollisions::Right && vy == 0) {
				this->AddPositionX(-2);
				vy = GenjiboDefine::SPEED_Y;
				vx = 0;
			}

			if (side == SideCollisions::Bottom && vx == 0) {
				this->AddPositionY(-2);
				vx = -GenjiboDefine::SPEED_X;
				vy = 0;

			}
			if (side == SideCollisions::Top && vx == 0) {
				this->AddPositionY(2);
				vx = GenjiboDefine::SPEED_X;
				vy = 0;
			}
		}
		else if (typeAttack == 2) {
			if (side == SideCollisions::Left || side == SideCollisions::TopLeft || side == SideCollisions::BottomLeft) {
				vy = GenjiboDefine::SPEED_Y;
				vx = GenjiboDefine::SPEED_X;
			}
			if (side == SideCollisions::Bottom) {
				this->AddPositionY(-2);
				vy = 0;
			}
			if (side == SideCollisions::Right || side == SideCollisions::TopRight || side == SideCollisions::BottomRight) {
				this->AddPositionX(-2);
				vx = -GenjiboDefine::SPEED_X;
			}
		}
	}
	if (other->Tag == EntityTypes::MegaBullet) {
		hp -= other->dame;
		other->Tag = EntityTypes::None;
	}

}

void Genjibo::Draw(D3DXVECTOR2 transform)
{
	if (isAlive) {
		if (onDraw) {
			if (mAnimation == mAnimationSpawn) {
				mSpriteZone->Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), transform);
			}
			mAnimation->FlipVertical(isFaceRight);
			mAnimation->Draw(transform);
		}
		if (!mAnimationSpawn->mEndAnimate)
			mAnimationSub->Draw(transform);
	}

	if (explosion)
	{
		for (int i = 0; i < 7; i++)
		{
			explosion[i]->Draw(transform);
		}
	}
	mDoor->Draw(transform);
}