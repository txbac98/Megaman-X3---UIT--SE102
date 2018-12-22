#include "DemoScene.h"
#include "../GameDefines/GameDefine.h"
#include "../GameComponents/Sound.h"
#include "../GameControllers/SceneManager.h"
#include "MenuScene.h"

DemoScene::DemoScene()
{
    LoadContent();
}

void DemoScene::LoadContent()
{
	
    //set mau backcolor cho scene o day la mau den
    mBackColor = 0x000000;
	
	timeDelayRestart = 0;

	
	Sound::getInstance()->play("Background", true, 0);

	//kích thước bằng màn hình
    mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());

	mPlayer = new Player();

	mPlayer->SetPosition(100, 637);

	ViewPort::getInstance()->Init(mPlayer);

	//vị trí giữa màn hình
    mCamera->SetPosition(GameGlobal::GetWidth() / 2, ViewPort::getInstance()->GetHeightMap() - mCamera->GetHeight());

    mPlayer->SetCamera(mCamera);

	ViewPort::getInstance()->SetCamera(mCamera);

}

void DemoScene::Update(float dt)
{
	if (mPlayer->isAlive)
		ViewPort::getInstance()->Update(dt);

    mPlayer->Update(dt);

	if (!mPlayer->isAlive) {
		timeDelayRestart += dt;
		if (timeDelayRestart > 5) {
			Sound::getInstance()->stop("Background");
			SceneManager::GetInstance()->ReplaceScene(new MenuScene());
		}
	}
	else if (mPlayer->hornetHP) {
		if (mPlayer->hornetHP->HP <= 0) {
			timeDelayRestart += dt;
			if (timeDelayRestart > 10) {
				Sound::getInstance()->stop("Background");
				SceneManager::GetInstance()->ReplaceScene(new MenuScene());
			}
		}	
	}
}

void DemoScene::Draw()
{
	ViewPort::getInstance()->Draw();
	
   mPlayer->Draw();
}



