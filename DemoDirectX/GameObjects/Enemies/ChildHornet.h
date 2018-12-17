#pragma once
#include "./../../GameComponents/Animation.h"
#include "../Entity.h"
#include "../MapObjects/GameObject.h"
#include"RedExplosion.h"
#include "../Player/Player.h"

class ChildHornet : public Entity
{
public:
	~ChildHornet();
	ChildHornet(int type,float posX, float posY, float vx, float vy);
	ChildHornet();
	void Update(float dt);
	void OnCollision(Entity * other, SideCollisions side);
	void Die();
	//void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	void Draw(D3DXVECTOR2 transform);
	Animation *mAnimation;
protected:
	RedExplosion* mExplosion;
	Player* mPlayer;
	int typeAttack;
	float tDelay;
	bool waittingDie;
};
