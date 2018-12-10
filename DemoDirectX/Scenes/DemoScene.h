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


class DemoScene : public Scene
{
public:
    DemoScene();

    void Update(float dt);
    void LoadContent();
    void Draw();
	
 

protected:
    void checkCollision(float dt);
    void CheckCameraAndWorldMap();

    GameMap *mMap, *mMap0, *mMap1, *mMap2, *mMapBack, *mMapNext;
    Camera *mCamera;
    Player *mPlayer;
	ViewPort *mViewPort;
};

