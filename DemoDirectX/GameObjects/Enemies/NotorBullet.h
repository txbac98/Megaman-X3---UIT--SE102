#include "../Entity.h"
#include"../../GameComponents/Animation.h"
#include "RedExplosion.h"


class NotorBullet : public Entity
{
public:
	NotorBullet();
	~NotorBullet();
	void Spawn(float posx, float posy, float vx, float vy);
	void Update(float dt);
	void OnCollision(Entity * other, SideCollisions side);
	void Draw(D3DXVECTOR2 transform = D3DXVECTOR2());
	Animation *mAnimation;
	RedExplosion *mExplosion=NULL;
	bool wasBorn = false;		//Đã được sinh ra hay chưa
	int typeBullet = 0;
};
