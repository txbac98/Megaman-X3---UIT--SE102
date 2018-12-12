#pragma once
#include "GameMap.h"
#include "Camera.h"
#include "../GameObjects/Entity.h"
#include "../GameObjects/Player/Player.h"
#include "CollisionManager.h"

class ViewPort {
	static ViewPort* instance;
	public:	
		//ViewPort();
		//ViewPort(Player *player);
		//~ViewPort();
		

	static ViewPort* getInstance();
	void Init(Player *player);
		void Update(float dt);
		void UpdateCamera(float dt);
		void CheckCameraWithWouldMap();
		void Draw();
		void ChangeCurrentMap();
		void SetCamera(Camera *camera);
		void SetPlayer(Player *player);
		void SetCameraPositionX(float x);
		void SetCameraPositionY(float y);
		int GetHeightMap();
		int GetWidthMap();
		void GetMapObject(std::vector<Entity*> &entitiesOut, Entity *entity);
		Camera *mCamera;
		Player *mPlayer;
private:
		GameMap  *mCurrentMap, *mNextMap, *mBackMap;
		std::vector<GameMap*> mListMap;
		int iCurrentMap;
		float posCameraX, posCameraY;
		bool canUpdateCamera;
		
};