﻿#include "DemoScene.h"
#include "../GameDefines/GameDefine.h"



DemoScene::DemoScene()
{
    LoadContent();
}

void DemoScene::LoadContent()
{
	
    //set mau backcolor cho scene o day la mau den
    mBackColor = 0x000000;
	
	

	//kích thước bằng màn hình
    mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());

	mPlayer = new Player();

	mPlayer->SetPosition(100, 637);

	ViewPort::getInstance()->Init(mPlayer);
	//mViewPort = new ViewPort(mPlayer);

	//vị trí giữa màn hình
    mCamera->SetPosition(GameGlobal::GetWidth() / 2, ViewPort::getInstance()->GetHeightMap() - mCamera->GetHeight());

    //mMap->SetCamera(mCamera);

    mPlayer->SetCamera(mCamera);

	ViewPort::getInstance()->SetCamera(mCamera);

	//ViewPort::getInstance()->SetPlayer(mPlayer);
}

void DemoScene::Update(float dt)
{
	ViewPort::getInstance()->Update(dt);

    mPlayer->Update(dt);

	checkCollision(dt);

}

void DemoScene::Draw()
{
	ViewPort::getInstance()->Draw();
	
   mPlayer->Draw();
}




void DemoScene::checkCollision(float dt)
{

    vector<Entity*> listMapObject;

	ViewPort::getInstance()->GetMapObject(listMapObject, mPlayer);
	RECT rect = mPlayer->GetBound();

	for (size_t i = 0; i < listMapObject.size(); i++)
	{
		//Entity::SideCollisions direction;
		if (listMapObject[i]->Tag==Entity::EntityTypes::Wall || listMapObject[i]->Tag == Entity::EntityTypes::Elevator)	//va chạm quái được kiểm tra trong từng con quái
		CollisionManager::getInstance()->checkCollision(mPlayer, listMapObject.at(i), dt / 1000);	
	}

	
}
