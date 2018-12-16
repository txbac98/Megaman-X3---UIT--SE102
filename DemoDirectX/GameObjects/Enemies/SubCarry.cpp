#include "SubCarrry.h"
#include "../../GameComponents/ViewPort.h"

SubCarry::~SubCarry()
{
}

SubCarry::SubCarry(float posX, float posY)
{
	//mSprite = new Sprite("Resources/Enemies/Box1.png");
	mAnimationFly = new Animation("Resources/Boss/SubCarryarm.png", "Resources/Boss/SubCarryarmFly.txt", 0.1f, true);
	mAnimationDrop = new Animation("Resources/Boss/SubCarryarm.png", "Resources/Boss/SubCarryarmDrop.txt", 0.1f, false);

	mAnimation = mAnimationFly;
	this->SetPosition(posX, posY);
	posX1 = posX;
	posY1 = posY;
	this->SetWidth(mAnimation->GetWidth());
	this->SetHeight(mAnimation->GetHeight());
	mAnimation->SetPosition(posX, posY);
	mBox = new BoxObject();
	//posBoxX = this->width / 2 + mBox->GetWidth()/2;
	posBoxY = this->height / 2 + mBox->GetHeight() / 2;
	hp = 5;
	isAlive = true;
	isSpawn = true;
	haveBox = false;
	this->Tag = EntityTypes::SubCarryarm;
}

void SubCarry::Update(float dt)
{
	if (mBox->isSpawn) {
		mBox->Update(dt);
	}
	if (isAlive) {
		if (hp <= 0) {
			isAlive = false;
			return;
		}
		if (!mBox->isAlive) {
			if (posY <= posY1) {
				hp--;
				mBox->Spawn(posX, posY + posBoxY);
				haveBox = true;
			}
		}
		else mBox->Update(dt);



		if (haveBox) {	//Dính liền	
			if (posY < posY1 + 80) {		//80: tính ở map sau
				this->AddPositionY(0.5);
				mBox->AddPositionY(0.5);
			}
			else {
				haveBox = false;
			}
		}
		else {
			/*mAnimationDrop->Start();
			mAnimation = mAnimationDrop;*/
			if (posY > posY1) {
				this->AddPositionY(-0.5);
			}
		}
		mAnimation->Update(dt);
	}

}

void SubCarry::OnCollision(Entity * other, SideCollisions side)
{
	
}

void SubCarry::Draw(D3DXVECTOR2 transform)
{
	if (mBox->isSpawn) {
		mBox->Draw(transform);
	}
	if (isAlive) {
		mAnimation->SetPosition(posX, posY);
		mAnimation->Draw(transform);
	}
}
