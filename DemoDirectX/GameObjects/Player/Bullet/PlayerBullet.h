#include "../../Entity.h"
#include "../../../GameComponents/Sprite.h"
#include"../../../GameComponents/Animation.h"

class PlayerBullet : public Entity
{
	public:
	PlayerBullet();
	~PlayerBullet();
	void Spawn(bool goLeft, int typeBullet);
	void Update(float dt, RECT rectCamera);
	void OnCollision(Entity * other, SideCollisions side);
	void Draw( D3DXVECTOR2 transform = D3DXVECTOR2());
	Animation *mCurrentAnimation, *mAnimationBullet0, *mAnimationBullet1, *mAnimationBullet2;
	bool isGoLeft;
	bool wasBorn = false;		//Đã được sinh ra hay chưa
};
