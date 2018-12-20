#pragma once

#include <math.h>
#include <vector>
#include <d3dx9.h>
#include <d3d9.h>

#include "../GameComponents/Scene.h"
#include "../GameComponents/Sprite.h"
#include "../GameComponents/Animation.h"
#include "../GameComponents/GameMap.h"
#include "../GameComponents/Camera.h"
#include "../GameObjects/Player/Player.h"
#include "../GameComponents/CollisionManager.h"
#include "../GameComponents/ViewPort.h"


class MenuScene : public Scene
{
public:
	MenuScene();

	void Update(float dt);
	void Draw();

protected:
	Sprite *mSprite;
	Animation *mAnimationPlayerStanding;
	Camera *mCamera;
	Player *mPlayer;
	//ViewPort *mViewPort;
};

