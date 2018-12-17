#pragma once
#include "./../../GameComponents/Animation.h"
#include "../Entity.h"
#include "../MapObjects/GameObject.h"
#include "../Player/Player.h"
#include "../Enemies/ChildHornet.h"
#include "HornetHP.h"

class Hornet : public Entity
{
public:
	~Hornet();
	Hornet(float posX, float posY);
	void Update(float dt);
	void OnCollision(Entity * other, SideCollisions side);
	//void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	void Draw(D3DXVECTOR2 transform);
protected:
	void SpawnChild1();
	void SpawnChildAndFollow();
	void Prepare();
	void Attack();
	Animation *mAnimation, *mAnimationAttack, *mAnimationSpawnChild, *mAnimationDie,
		*mAnimationFly,*mAnimationStand, *mAnimationPrepare;
	Player* mPlayer;
	Camera* mCamera;
	ChildHornet *mChild;
	std::vector<ChildHornet* > mListChild;
	RECT rectMove;
	int midRectY;
	int typeAttack, iExplosion;
	int direction; //Hướng
	float posX1, posY1;
	int posMegaX, posMegaY;
	bool toAttack;
	bool onDraw;
};
