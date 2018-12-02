#include "DemoScene.h"
#include "../GameDefines/GameDefine.h"



DemoScene::DemoScene()
{
    LoadContent();
}

void DemoScene::LoadContent()
{
	
    //set mau backcolor cho scene o day la mau xanh
    mBackColor = 0x54acd2;

    mMap = new GameMap("Resources/map64.tmx");

	//kích thước bằng màn hình
    mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	//vị trí giữa màn hình
    mCamera->SetPosition(GameGlobal::GetWidth() / 2, mMap->GetHeight() - mCamera->GetHeight());

    mMap->SetCamera(mCamera);

	mPlayer = new Player();

    mPlayer->SetPosition(150, 650);
    mPlayer->SetCamera(mCamera);
	mCamera->SetPosition(mPlayer->GetPosition());

}

void DemoScene::Update(float dt)
{
    checkCollision(dt);

    mMap->Update(dt);

    mPlayer->Update(dt);

    CheckCameraAndWorldMap();
}

void DemoScene::Draw()
{
    mMap->Draw();

   mPlayer->Draw();
}




void DemoScene::checkCollision(float dt)
{
    /*su dung de kiem tra xem khi nao mario khong dung tren 1 object hoac
    dung qua sat mep trai hoac phai cua object do thi se chuyen state la falling*/ 
    int widthBottom = 0;

    vector<Entity*> listMapObject;

	//Get object map
    mMap->GetQuadTree()->getEntitiesCollideAble(listMapObject, mPlayer);
	RECT rect = mPlayer->GetBound();

	for (size_t i = 0; i < listMapObject.size(); i++)
	{
		Entity::SideCollisions direction;
		CollisionManager::getInstance()->checkCollision(mPlayer, listMapObject.at(i), dt / 1000);	
	}

	
}
void DemoScene::CheckCameraAndWorldMap()
{
	mCamera->SetPosition(mPlayer->GetPosition());

	if (mCamera->GetBound().left < 0)
	{
		//vi position cua camera ma chinh giua camera
		//luc nay o vi tri goc ben trai cua the gioi thuc
		mCamera->SetPosition(mCamera->GetWidth() / 2, mCamera->GetPosition().y);
		return;
	}

	if (mCamera->GetBound().right > mMap->GetWidth())
	{
		//luc nay cham goc ben phai cua the gioi thuc
		mCamera->SetPosition(mMap->GetWidth() - mCamera->GetWidth() / 2,
			mCamera->GetPosition().y);
		return;
	}

	if (mCamera->GetBound().top < 0)
	{
		//luc nay cham goc tren the gioi thuc
		mCamera->SetPosition(mCamera->GetPosition().x, mCamera->GetHeight() / 2);
		return;
	}

	if (mCamera->GetBound().bottom > mMap->GetHeight())
	{
		//luc nay cham day cua the gioi thuc
		mCamera->SetPosition(mCamera->GetPosition().x,
			mMap->GetHeight() - mCamera->GetHeight() / 2);
		return;
	}
	
	return;
}