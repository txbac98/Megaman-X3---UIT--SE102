#include "../Entity.h"
//#include "../../GameComponents/Sprite.h"
#include"../../GameComponents/Animation.h"

class PlayerDashingSmoke : public Entity
{
public:
	PlayerDashingSmoke();
	~PlayerDashingSmoke();
	void Spawn(float posX, float posY);
	void Update(float dt);
	void Draw(D3DXVECTOR2 transform = D3DXVECTOR2());
	Animation *mAnimation;
	bool wasBorn = false;		//Đã được sinh ra hay chưa
};
