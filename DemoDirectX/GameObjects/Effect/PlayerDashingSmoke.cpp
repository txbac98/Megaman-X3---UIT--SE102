#include "PlayerDashingSmoke.h"

PlayerDashingSmoke::PlayerDashingSmoke()
{
	wasBorn = false;
	mAnimation = new Animation("Resources/Megaman/Effect.png", "Resources/Megaman/DashingSmoke.txt", 0.05f, false);
	this->SetVy(-2);	//Bay lên
	mAnimation->Start();
}

PlayerDashingSmoke::~PlayerDashingSmoke()
{
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
		mAnimation->Draw(transform);
}
