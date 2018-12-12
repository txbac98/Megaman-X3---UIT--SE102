#include "../Entity.h"
#include "../../GameComponents/Sprite.h"
#include"../../GameComponents/Animation.h"

class EnemyBullet : public Entity
{
public:
	EnemyBullet();
	~EnemyBullet();
	void Spawn(float vx, float vy, int typeBullet);
	void Update(float dt, RECT rectCamera);
	void OnCollision(Entity * other, SideCollisions side);
	void Draw(D3DXVECTOR2 transform = D3DXVECTOR2());
	Animation *mAnimation;
	bool wasBorn = false;		//Đã được sinh ra hay chưa
};
