#pragma once
#include "./../../GameComponents/Animation.h"
#include "../Entity.h"
#include "../MapObjects/GameObject.h"
#include "../Player/Player.h"

class ItemHP : public Entity
{
public:
	~ItemHP();
	ItemHP(float posX, float posY);
	void Update(float dt);
	void OnCollision(Entity * other, SideCollisions side);
	void Draw(D3DXVECTOR2 transform);
protected:
	Animation* mItemHP;
	Player *mPlayer;
};
