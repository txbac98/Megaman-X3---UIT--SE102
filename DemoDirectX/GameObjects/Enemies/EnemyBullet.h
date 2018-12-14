#include "../Entity.h"
#include"../../GameComponents/Animation.h"
#include "RedExplosion.h"


class EnemyBullet : public Entity
{
public:
	EnemyBullet();
	~EnemyBullet();
	void Spawn(int type, float posx, float posy, float vx, float vy);
	void Update(float dt);
	void OnCollision(Entity * other, SideCollisions side);
	void Draw(D3DXVECTOR2 transform = D3DXVECTOR2());
	Sprite *mSprite1;
	Animation *mAnimation2;
	RedExplosion *mExplosion=NULL;
	bool wasBorn = false;		//Đã được sinh ra hay chưa
	int typeBullet = 0;
	float ay;
};
