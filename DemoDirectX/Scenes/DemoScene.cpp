#include "DemoScene.h"
#include "../GameDefines/GameDefine.h"



DemoScene::DemoScene()
{
    LoadContent();
}

void DemoScene::LoadContent()
{
	
    //set mau backcolor cho scene o day la mau den
    mBackColor = 0x000000;
	
	mViewPort = new ViewPort();

	//kích thước bằng màn hình
    mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	//vị trí giữa màn hình
    mCamera->SetPosition(GameGlobal::GetWidth() / 2, mViewPort->GetHeightMap() - mCamera->GetHeight());

    //mMap->SetCamera(mCamera);

	
	mPlayer = new Player();

    mPlayer->SetPosition(100, 637);

    mPlayer->SetCamera(mCamera);

	mCamera->SetPosition(mPlayer->GetPosition());

	mViewPort->SetCamera(mCamera);

	mViewPort->SetPlayer(mPlayer);
}

void DemoScene::Update(float dt)
{
	checkCollision(dt);

	mViewPort->Update(dt);

    mPlayer->Update(dt);

}

void DemoScene::Draw()
{
	mViewPort->Draw();
	
   mPlayer->Draw();
}




void DemoScene::checkCollision(float dt)
{
    /*su dung de kiem tra xem khi nao mario khong dung tren 1 object hoac
    dung qua sat mep trai hoac phai cua object do thi se chuyen state la falling*/ 
    int widthBottom = 0;

    vector<Entity*> listMapObject;

	mViewPort->GetMapObject(listMapObject, mPlayer);
	RECT rect = mPlayer->GetBound();

	for (size_t i = 0; i < listMapObject.size(); i++)
	{
		//Entity::SideCollisions direction;
		CollisionManager::getInstance()->checkCollision(mPlayer, listMapObject.at(i), dt / 1000);	
	}

	
}
