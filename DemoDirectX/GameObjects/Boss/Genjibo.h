#pragma once
#include "./../../GameComponents/Animation.h"
#include "../MapObjects/Door.h"
#include "../Entity.h"
#include "../MapObjects/GameObject.h"
#include "../Player/Player.h"
#include "../Enemies/RedExplosion.h"

#include <time.h> 
#include <vector>
class Genjibo : public Entity
{
public:
	~Genjibo();
	Genjibo(float posX, float posY);
	void Update(float dt);
	void OnCollision(Entity * other, SideCollisions side);
	//void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	void Die();
	void wait(float seconds);
	void Draw(D3DXVECTOR2 transform);
protected:
	Animation *mAnimation, *mAnimationSpawn, *mAnimationSub, *mAnimationRotate;
	Sprite *mSpriteZone;
	Player* mPlayer;
	Door *mDoor;	//Chặn cửa
	RedExplosion **explosion, **explosion2;
	int count;
	bool die;
	vector<RedExplosion*> mExplosion;
	int typeAttack;
	float posX1, posY1, posXMid;
	bool onDraw;
	bool boom = false;
};
