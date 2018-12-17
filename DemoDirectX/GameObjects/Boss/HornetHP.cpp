#include "HornetHP.h"
HornetHP::HornetHP(float posx, float posy)
{
	this->SetPosition(posx, posy);
	mSprite = new Sprite("Resources/Boss/HornetHP1.png");
	mSprite->SetPosition(posX, posY);

	HP = 40;
	for (int i = 0; i < HP; i++) {
		mListSpriteLine.push_back(new Sprite("Resources/Boss/LineHP.png"));
		mListSpriteLine[i]->SetPosition(posX, (posY - 48 + (HP - i)*2));//(posY - 22 + (HP - i) * 2)
	}

}

HornetHP::~HornetHP()
{
}

void HornetHP::Update(float dt)
{
}

void HornetHP::Draw()
{
	mSprite->Draw();
	for (int i = 0; i < HP; i++) {
		mListSpriteLine[i]->Draw();
	}
}

void HornetHP::AddDame(int dame)
{
	HP -= dame;
}
