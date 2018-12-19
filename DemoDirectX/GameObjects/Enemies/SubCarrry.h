#pragma once
#include "./../../GameComponents/Animation.h"
#include "../Entity.h"
#include "../MapObjects/GameObject.h"
#include "RedExplosion.h"
#include "../Player/Player.h"
#include "BoxObject.h"

class SubCarry : public Entity
{
public:
	~SubCarry();
	SubCarry(float posX, float posY);
	SubCarry(float posX, float posY, float dty);
	void Update(float dt);
	void OnCollision(Entity * other, SideCollisions side);
	//void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	void Draw(D3DXVECTOR2 transform);
	bool onPosSpawn;
	Animation *mAnimation, *mAnimationFly, *mAnimationDrop;
protected:
	RedExplosion *mExplosion;
	Player *mPlayer;
	BoxObject *mBox;
	float posBoxX, posBoxY, posX1, posY1, dtY;
	bool haveBox;
};
