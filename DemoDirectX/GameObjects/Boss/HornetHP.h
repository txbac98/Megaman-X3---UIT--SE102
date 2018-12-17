#pragma once
#include "../Entity.h"
#include "../../GameComponents/Sprite.h"
#include <vector>

class HornetHP : public Entity
{
public:
	HornetHP(float posx, float posy);
	~HornetHP();
	//void Spawn(float posX, float posY);
	void Update(float dt);
	void Draw();
	void AddDame(int dame);
	int HP;
	Sprite *mSprite, *mSpriteLine;
	std::vector<Sprite*> mListSpriteLine;
};
