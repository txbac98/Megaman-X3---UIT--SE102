#include "SubCarrry.h"
#include "../../GameComponents/ViewPort.h"

SubCarry::~SubCarry()
{
}

SubCarry::SubCarry(float posX, float posY)
{
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
	posBoxY = this->height / 2 + mBox->GetHeight() / 2;
	hp = 5;
	dtY = 100;
	isAlive = true;
	isSpawn = true;
	haveBox = false;
	this->Tag = EntityTypes::SubCarryarm;
}

SubCarry::SubCarry(float posX, float posY, float dty)
{
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
	posBoxY = this->height / 2 + mBox->GetHeight() / 2;
	hp = 5;
	isAlive = true;
	isSpawn = true;
	haveBox = false;
	this->Tag = EntityTypes::SubCarryarm;
	dtY = dty;
}

void SubCarry::Update(float dt)
{
	//if (mBox)
	if (isAlive) {
		if (mBox->isSpawn) {
			mBox->Update(dt);
		}
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

		if (haveBox) {	//Dính liền	
			if (posY < posY1 + dtY) {		//dt: tính tay
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
	if (isAlive) {
		if (mBox->isSpawn) {
			mBox->Draw(transform);
		}
		mAnimation->SetPosition(posX, posY);
		mAnimation->Draw(transform);
	}
}
