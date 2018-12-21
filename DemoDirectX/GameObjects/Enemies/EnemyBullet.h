#pragma once
#include "../Entity.h"
#include"../../GameComponents/Animation.h"
#include "RedExplosion.h"
#include "../Player/Player.h"


class EnemyBullet : public Entity
{
public:
	EnemyBullet();
	~EnemyBullet();
	void Spawn(int type,bool faceRight, float posx, float posy, float vx, float vy);
	void Update(float dt);
	void OnCollision(Entity * other, SideCollisions side);
	void Draw(D3DXVECTOR2 transform = D3DXVECTOR2());
	Sprite *mSprite1;
	Animation *mAnimation2, *mAnimation3;
	Player *mPlayer;
	RedExplosion *mExplosion=NULL;
	bool wasBorn = false;		//Đã được sinh ra hay chưa
	int typeBullet = 0;
	bool isFaceRight=false;
	float ay;
};
