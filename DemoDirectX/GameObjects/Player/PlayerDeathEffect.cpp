#include "PlayerDeathEffect.h"

PlayerDeathEffect::~PlayerDeathEffect()
{
}

PlayerDeathEffect::PlayerDeathEffect(float posX, float posY)
{
	this->SetPosition(posX, posY);
	for (int i = 0; i < 16; i++) {
		if (i==0)	mListDeathorbs.push_back(new Deathorbs(posX, posY,0,-70));
		if (i == 1)	mListDeathorbs.push_back(new Deathorbs(posX, posY, 70, 0));
		if (i == 2)	mListDeathorbs.push_back(new Deathorbs(posX, posY, 0, 70));
		if (i == 3)	mListDeathorbs.push_back(new Deathorbs(posX, posY, -70,0));

		if (i == 4)	mListDeathorbs.push_back(new Deathorbs(posX, posY, 20, -20));
		if (i == 5)	mListDeathorbs.push_back(new Deathorbs(posX, posY, 20, 20));
		if (i == 6)	mListDeathorbs.push_back(new Deathorbs(posX, posY, -20, 20));
		if (i == 7)	mListDeathorbs.push_back(new Deathorbs(posX, posY, -20, -20));
		if (i == 8)	mListDeathorbs.push_back(new Deathorbs(posX, posY, 0, -30));
		if (i == 9)	mListDeathorbs.push_back(new Deathorbs(posX, posY, 30, 0));
		if (i == 10)	mListDeathorbs.push_back(new Deathorbs(posX, posY, 0, 30));
		if (i == 11)	mListDeathorbs.push_back(new Deathorbs(posX, posY, -30, 0));

		if (i == 12)	mListDeathorbs.push_back(new Deathorbs(posX, posY, 50, -50));
		if (i == 13)	mListDeathorbs.push_back(new Deathorbs(posX, posY, 50, 50));
		if (i == 14)	mListDeathorbs.push_back(new Deathorbs(posX, posY, -50, 50));
		if (i == 15)	mListDeathorbs.push_back(new Deathorbs(posX, posY, -50, -50));
		//mListAnimation.push_back( new Animation("Resources/Megaman/MegaEffect/DeathEffect2.png", "Resources/Megaman/MegaEffect/DeathEffect2.txt",0.2f, false));
		//mListAnimation[i]->SetPosition(posX, posY);
	}
	
}

void PlayerDeathEffect::Update(float dt)
{
	//for (int i = 0; i < mListAnimation.size(); i++) {
	//	if (i == 0 || i == 2 || i == 4) {
	//		mListAnimation[i]->SetRotation(mListAnimation[i]->GetRotation() + dt);
	//		//mListAnimation[i]->SetScale(mListAnimation[i]->GetScale().x +dt, mListAnimation[i]->GetScale().y + dt); 
	//	}
	//	else {
	//		mListAnimation[i]->SetRotation(mListAnimation[i]->GetRotation() - dt);
	//		//mListAnimation[i]->SetScale(mListAnimation[i]->GetScale().x + dt, mListAnimation[i]->GetScale().y + dt);
	//	}
	//}
	for (int i = 0; i < mListDeathorbs.size(); i++) {
		mListDeathorbs[i]->Update(dt);
	}
}

void PlayerDeathEffect::Draw(D3DXVECTOR2 transform)
{
	//for (int i = 0; i < mListAnimation.size(); i++) {
	//	//if (!mListAnimation[i]->mEndAnimate)
	//		mListAnimation[i]->Draw(transform);
	//}
	for (int i = 0; i < mListDeathorbs.size(); i++) {
		mListDeathorbs[i]->Draw(transform);
	}
}
