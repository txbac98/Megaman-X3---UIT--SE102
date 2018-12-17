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
	hp = 25;
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
}

void Genjibo::Update(float dt)
{
	if (isAlive) {
		//Con ong bay xuống
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
		}
		Entity::Update(dt);

		if (hp > 15) {
			typeAttack = 1;
		}
		else if (hp > 8) {
			typeAttack = 2;
		}
		else typeAttack = 3;

		if (hp <= 0) {
			//Die();
			this->Tag = EntityTypes::None;

			die = true;
		}

		//kiểm tra va chạm  object với map
		std::vector<Entity*> mListMapObject;
		ViewPort::getInstance()->GetMapObject(mListMapObject, this);
		for (size_t j = 0; j < mListMapObject.size(); j++) {

			CollisionManager::getInstance()->checkCollision(this, mListMapObject[j], dt);
		}

		//Kiểm tra va chạm với nhân vật
		if (mPlayer) {
			//kiểm tra va chạm viên đạn player
			for (int i = 0; i < sizeof(mPlayer->mListBullet); i++) {
				CollisionManager::getInstance()->checkCollision(&mPlayer->mListBullet[i], this, dt);
			}
			CollisionManager::getInstance()->checkCollision(mPlayer, this, dt);
		}

		
	}
	if (hp <= 0)
	{

		if (explosion) {
			/*Sleep(100);
			for (int j = 0; j < 5; j++)
			{
				explosion[j]->Update(dt);
			}
			if (explosion[4]->mEndAnimate)
				explosion = NULL;*/

			explosion[count]->Update(dt);
			
			//srand(time(NULL));

			if (explosion[count]->mEndAnimate)
			{
				int x = rand() % 50;
				int y = rand() % 40;
				count++;
				explosion[count]->ReStart(posX - 20 + x, posY - 20 + y);
				//explosion[count]->ReStart(x,y);
			}
			if (count == 6)
			{
				explosion = NULL;
				isAlive = false;
			}
		}
	}
}

void Genjibo::OnCollision(Entity * other, SideCollisions side)
{
	if (other->Tag == EntityTypes::Wall || other->Tag == EntityTypes::Door) {

		if (side == SideCollisions::Bottom)
			vy = 0;

		if (typeAttack == 1) {	//Chạy qua chạy lại phía dưới
			if (typeAttack == 1) {
				if (side == SideCollisions::Left || side == SideCollisions::Right) {
					vx = -vx;
				}
			}
		}
		else if (typeAttack == 2) //Đi vòng tròn
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
		else if (typeAttack == 3) {
			if (vy == 0 && posX < posX1) {
				vy = -GenjiboDefine::SPEED_Y;
			}
			if (side == SideCollisions::Left) {
				this->AddPositionX(2);
				vy = GenjiboDefine::SPEED_Y;
				vx = GenjiboDefine::SPEED_X;
			}
			if (side == SideCollisions::Right) {
				this->AddPositionX(-2);
				vx = GenjiboDefine::SPEED_X;
			}
			if (side == SideCollisions::Bottom) {
				this->AddPositionY(-2);
				vy = 0;
			}
			if (side == SideCollisions::Top) {
				this->AddPositionY(2);
				vx = 0;
				vy = GenjiboDefine::SPEED_Y;
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
}
void Genjibo::Die() {
	if (isAlive) {



		//int dx = 0, dy = -5;
	/*	for (int i = 0; i < 5; i++) {
			explosion[i] = new RedExplosion(posX + dx, posY + dy);
			dx += 10;
			dy += 10;
			if (i % 3 == 1)
			{
				dx = -10;
			}
		}*/

	}
}