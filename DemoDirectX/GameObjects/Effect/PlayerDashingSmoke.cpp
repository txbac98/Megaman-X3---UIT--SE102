#include "PlayerDashingSmoke.h"

PlayerDashingSmoke::PlayerDashingSmoke()
{
	wasBorn = false;
	mAnimation = new Animation("Resources/Effect/DashingSmoke.png", "Resources/Effect/DashingSmoke.txt", 0.01f, false);
	mAnimation->Start();
}

PlayerDashingSmoke::~PlayerDashingSmoke()
{
}

void PlayerDashingSmoke::Spawn(float posX, float posY)
{
	wasBorn = true;
	this->SetPosition(posX, posY);
}

void PlayerDashingSmoke::Update(float dt)
{
	if (wasBorn) {
		mAnimation->Update(dt);
		if (mAnimation->mEndAnimate) {
			wasBorn = false;
			mAnimation->Start();		//trở về ban đầu
		}
	}
}

void PlayerDashingSmoke::Draw(D3DXVECTOR2 transform)
{
	if (wasBorn)
	{
		mAnimation->SetPosition(this->GetPosition());
		mAnimation->Draw(transform);
	}
		
}
