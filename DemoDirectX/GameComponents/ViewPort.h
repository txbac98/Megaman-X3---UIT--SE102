#pragma once
#include "GameMap.h"
#include "Camera.h"
#include "../GameObjects/Entity.h"
#include "../GameObjects/Player/Player.h"
#include "CollisionManager.h"

class ViewPort {

	public:	
		ViewPort();
		~ViewPort();
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
	private:
		GameMap  *mCurrentMap, *mNextMap, *mBackMap;
		std::vector<GameMap*> mListMap;
		Camera *mCamera;
		Player *mPlayer;
		int iCurrentMap;
		float posCameraX, posCameraY;
		bool canUpdateCamera;
		
};