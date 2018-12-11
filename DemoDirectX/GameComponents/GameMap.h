#pragma once
#ifndef __GAME_MAP__
#define __GAME_MAP__

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "../GameComponents/Sprite.h"
#include "../MapReader/Tmx.h.in"
#include "Camera.h"
#include "GameGlobal.h"
#include "CollisionManager.h"
#include "QuadTree.h"
#include "../GameObjects/MapObjects/Elevator.h"
#include "../GameObjects/MapObjects/Door.h"
#include "../GameObjects/Enemies/Notorbanger.h"
using namespace std;
class GameMap
{
public:
    GameMap(char* filePath, char *fileQuadTree, int posx=0, int posy=0);
	GameMap(char* filePath, char *fileQuadTree, Camera *camera, int posx = 0, int posy = 0);
	GameMap();
    void SetCamera(Camera* camera);
    void Update(float dt);
    void Draw();
	Entity GetEntityWithIdObject(int ID);
    Tmx::Map* GetMap();
    RECT GetWorldMapBound();
    int GetWidth();
    int GetHeight();
    int GetTileWidth();
    int GetTileHeight();
	int PosX, PosY;
    std::map<int, Sprite*> getListTileSet();

    bool IsBoundLeft(); //kiem tra luc nay Camera o vi bien ben trai so voi WorldMap
    bool IsBoundRight(); // kiem tra xem co o vi tri bien ben phai worldmap khong
    bool IsBoundTop(); // kiem tra xem co o vi tri bien ben trai worldmap khong
    bool IsBoundBottom(); // kiem tra xem co o vi tri bien ben phai worldmap khong
    ~GameMap();


    QuadTree* GetQuadTree();

private:
    void LoadMap(char* filePath, char *fileQuadTree);

    Tmx::Map                        *mMap;
    std::map<int, Sprite*>          mListTileset;
    LPD3DXSPRITE                    mSpriteHandler;
    Camera                          *mCamera;
    QuadTree                        *mQuadTree;
	std::vector<Elevator*>			mListElevator;
	std::vector<Entity*>			mListEntity;
	std::vector<Door*>				mListDoor;
	std::vector<Notorbanger*>		mListNotor;
    Sprite                          *mSpriteBricks, *mSpriteBrickGold;
};

#endif

