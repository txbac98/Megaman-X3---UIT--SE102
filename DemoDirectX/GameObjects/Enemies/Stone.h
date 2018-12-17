#pragma once

#include "../Enemies/RedExplosion.h"

#include "./../../GameComponents/Animation.h"
#include "../Entity.h"
#include "../Player/Player.h"
#include "../MapObjects/GameObject.h"
#include "BoxObject.h"
#include <vector>

class Stone : public Entity
{
public:
	~Stone();
	Stone(float posx, float posy, int type);

	Sprite *mSprite5, *mSprite3, *mSprite;
	Player *mPlayer;
	Camera *mCamera;
	BoxObject *mBox;
	void OnCollision(Entity * other, SideCollisions side);
	void Draw(D3DXVECTOR2 transform = D3DXVECTOR2());
	void Update(float dt);
	void Die();
	RedExplosion **explosion;
	bool wasBorn = false;
	float ay;
	int count;
	int mType;
};
