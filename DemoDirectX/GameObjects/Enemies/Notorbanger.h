#pragma once

#include "./../../GameComponents/Animation.h"
#include "../Entity.h"
#include "../Player/Player.h"
#include "../MapObjects/GameObject.h"
//#include "RedExplosion.h"
//#include "../../GameComponents/GameMap.h"
#include "EnemyBullet.h"
//Để viewport đây sẽ bị lỗi, class tĩnh phải khai báo trong .cpp

//Súng đơn
class Notorbanger : public Entity
{
public:
	~Notorbanger();
	Notorbanger(float posx, float posy);
	void Update(float dt);
	void Jumping(float dt);
	void OnCollision(Entity * other, SideCollisions side);
	//void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	void Draw(D3DXVECTOR2 transform);
	void Die();
protected:
	Player *mPlayer;
	Camera *mCamera;
	RedExplosion *explosion;
	Animation *mAnimation,*mAnimationShoot,*mAnimationShoot1, *mAnimationShoot2, *mAnimationJump, 
		*mAnimationUp1,*mAnimationUp2,*mAnimationStand;
	int  direction, iBullet;
	int type;	//Loại nòng quay: 1 xiên, 2 thẳng để gọi khi bắn viên đạn
	bool isFaceLeft;
	bool allowMoveLeft, allowMoveRight;
	//bool isAlive;
	//std::vector<EnemyBullet*> mListBullet;
	EnemyBullet* mListBullet;
};
