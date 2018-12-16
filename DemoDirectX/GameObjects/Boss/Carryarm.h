#pragma once
#include "./../../GameComponents/Animation.h"
#include "../Entity.h"
#include "../MapObjects/GameObject.h"
#include "../Player/Player.h"
#include "../Enemies/SubCarrry.h"
#include "DebrisCarry.h"


class Carryarm : public Entity
{
public:
	~Carryarm();
	Carryarm(float posX, float posY);
	void Update(float dt);
	void OnCollision(Entity * other, SideCollisions side);
	//void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	void Draw(D3DXVECTOR2 transform);
protected:
	//Animation *mAnimation, *mAnimationSpawn, *mAnimationSub, *mAnimationRotate;
	Sprite *mSpriteCarryarm, *mSpriteMove;
	Player* mPlayer;
	SubCarry* mSub;
	DebrisCarry *mDebris1, *mDebris2, *mDebris3;
};
