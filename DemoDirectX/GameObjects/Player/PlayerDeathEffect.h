#include "./../../GameComponents/Animation.h"
#include "../Entity.h"
#include "../MapObjects/GameObject.h"
#include "Deathorbs.h"

class PlayerDeathEffect : public Entity
{
public:
	~PlayerDeathEffect();
	PlayerDeathEffect(float posX, float posY);
	void Update(float dt);
	//void OnCollision(Entity * other, SideCollisions side);
	//void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	void Draw(D3DXVECTOR2 transform);
protected:
	std::vector<Animation*> mListAnimation;
	std::vector<Deathorbs*> mListDeathorbs;
	float vx, vy;
};
