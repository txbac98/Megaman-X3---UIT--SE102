﻿#include "DemoScene.h"
#include "../GameDefines/GameDefine.h"
#include "../GameComponents/Sound.h"


DemoScene::DemoScene()
{
    LoadContent();
}

void DemoScene::LoadContent()
{
	
    //set mau backcolor cho scene o day la mau den
    mBackColor = 0x000000;
	
	Sound::getInstance()->loadSound("Resources/Sounds/Background.wav", "Background");
	Sound::getInstance()->loadSound("Resources/Sounds/Explosion.wav", "Explosion");
	Sound::getInstance()->loadSound("Resources/Sounds/Jump.wav", "PlayerShoot");
	Sound::getInstance()->loadSound("Resources/Sounds/PlayerShoot.wav", "PlayerShoot12");
	Sound::getInstance()->loadSound("Resources/Sounds/Jump.wav", "Jump");
	Sound::getInstance()->loadSound("Resources/Sounds/Die.wav", "Die");
	Sound::getInstance()->play("Background", true, 0);

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

    

	
}
