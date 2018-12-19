#include "Carryarm.h"
#include"../../GameComponents/ViewPort.h"
Carryarm::~Carryarm()
{
}

Carryarm::Carryarm(float posX, float posY)
{
	mDebris1 = new DebrisCarry(1, posX, posY);	//To
	mDebris2 = new DebrisCarry(2, posX+80, posY-10);	//Doc		x=1+80;
	mDebris3 = new DebrisCarry(3, mDebris2->posX-25, mDebris2->posY+45);	//Ngang	vị trí luôn bằng 2+(-25,45)
	mSub = new SubCarry(posX+10,posY-20,153);
	//mSubRight = new SubCarry(posX + 80, posY - 20, 148);
	//mSub = mSubLeft;
	this->Tag = EntityTypes::Carryarm;
	this->isAlive = true;
	this->isSpawn = true;	
	this->SetPosition(posX, posY);
	posY1 = posY;
	mPlayer = ViewPort::getInstance()->mPlayer;
	
}


void Carryarm::Update(float dt)
{
	
	if (mSub->isAlive ) {
		CollisionManager::getInstance()->checkCollision(mPlayer, mDebris1, dt / 1000);
		CollisionManager::getInstance()->checkCollision(mPlayer, mDebris2, dt / 1000);
		CollisionManager::getInstance()->checkCollision(mPlayer, mDebris3, dt / 1000);

		if (posX - mPlayer->posX < 40) mPlayer->noDownKey = true;

		if (posY < posY1 + mDebris1->height/2) {	//Xuống cả khối
			this->AddPositionY(0.1);
			mDebris1->AddPositionY(0.2);
			mDebris2->AddPositionY(0.2);
			mDebris3->AddPositionY(0.2);
			posY2 = mDebris2->posY;
			posY3 = mDebris3->posY;
		}
		else {	//Xuống 2 thanh
			if (mDebris2->posY < posY2 + mDebris2->height / 2 + mDebris1->height / 2 +5) {
				mDebris2->AddPositionY(0.5);
				mDebris3->AddPositionY(0.5);
			}
			else
			{	
				mPlayer->noDownKey = false;	
				mSub->Update(dt);
			}
		}
	}
	else {//Đi lên vị trí cũ
		if (mDebris2->posY > posY2 ) {
			mDebris2->AddPositionY(-0.5);
			mDebris3->AddPositionY(-0.5);
		}
		else {
			if (posY > posY1 -20) {	//Lên cả khối
				this->AddPositionY(-0.2);
				mDebris1->AddPositionY(-0.2);
				mDebris2->AddPositionY(-0.2);
				mDebris3->AddPositionY(-0.2);
			}
			else 
				isAlive = false;
		}
	}
	//Check collision player với các mảnh
}

void Carryarm::OnCollision(Entity * other, SideCollisions side)
{
}

void Carryarm::Draw(D3DXVECTOR2 transform)
{
	mDebris2->Draw(transform);
	mDebris3->Draw(transform);
	mDebris1->Draw(transform);
	mSub->Draw(transform);
}
