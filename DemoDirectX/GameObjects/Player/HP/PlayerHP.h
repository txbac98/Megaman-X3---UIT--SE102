#include "../../Entity.h"
#include "../../../GameComponents/Sprite.h"
#include <vector>

class PlayerHP : public Entity
{
public:
	PlayerHP(float posx, float posy);
	~PlayerHP();
	//void Spawn(float posX, float posY);
	void Update(float dt);
	void Draw();
	void AddDame(int dame);
	int HP;
	Sprite *mSprite,*mSpriteLine;
	std::vector<Sprite*> mListSpriteLine;
};
