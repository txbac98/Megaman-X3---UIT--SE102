#include "DemoScene.h"
#include "../GameDefines/GameDefine.h"



DemoScene::DemoScene()
{
    LoadContent();
}

void DemoScene::LoadContent()
{
	
    //set mau backcolor cho scene o day la mau xanh
    mBackColor = 0x000000;

    //mMap0 = new GameMap("Resources/Map/NewMap0.tmx");
	//mMap1 = new GameMap("Resources/Map/NewMap1.tmx");

	//mMap = mMap0;
	
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

	//mMap->Update(dt);

	/*if (mMapNext != NULL)
		mMapNext->Update(dt);*/
	

    mPlayer->Update(dt);

	CheckCameraAndWorldMap();
}

void DemoScene::Draw()
{
	/*mMap->Draw();
	if (mMapNext != NULL)
		mMapNext->Draw();*/
	mViewPort->Draw();
	
   mPlayer->Draw();
}




void DemoScene::checkCollision(float dt)
{
    /*su dung de kiem tra xem khi nao mario khong dung tren 1 object hoac
    dung qua sat mep trai hoac phai cua object do thi se chuyen state la falling*/ 
    int widthBottom = 0;

    vector<Entity*> listMapObject;

	//Get object map
    //mMap->GetQuadTree()->getEntitiesCollideAble(listMapObject, mPlayer);
	mViewPort->GetMapObject(listMapObject, mPlayer);
	RECT rect = mPlayer->GetBound();

	for (size_t i = 0; i < listMapObject.size(); i++)
	{
		//Entity::SideCollisions direction;
		CollisionManager::getInstance()->checkCollision(mPlayer, listMapObject.at(i), dt / 1000);	
	}

	//if (mMapNext) {
	//	//Get object map
	//	mMapNext->GetQuadTree()->getEntitiesCollideAble(listMapObject, mPlayer);
	//	RECT rect = mPlayer->GetBound();

	//	for (size_t i = 0; i < listMapObject.size(); i++)
	//	{
	//		CollisionManager::getInstance()->checkCollision(mPlayer, listMapObject.at(i), dt / 1000);
	//	}

	//}
	
}
void DemoScene::CheckCameraAndWorldMap()
{
	//Position Camera có liên quan tới position của player là không lag

	//mCamera->SetPositionX(mPlayer->GetPosition().x);
	//if (mPlayer->posY>800 )
	//mCamera->SetPosition(mPlayer->GetPosition().x,600.0f); //.x,mCamera->GetPosition().y
	//mPlayer->SetCamera(mCamera);
		
	//else mCamera->SetPosition(mPlayer->GetPosition().x + 30, mPlayer->GetPosition().y-60);
	//else 
		//mCamera->SetPosition(mPlayer->GetPosition().x, mCamera->GetPosition().y);
	//mCamera->SetPosition(mPlayer->GetPosition());
	/*if (mCamera->GetPosition().x!= mPlayer->GetPosition().x + 30)
		mCamera->SetPosition(mPlayer->GetPosition().x + 30, 600);
	if (mCamera->GetPosition().y>mPlayer->posY+20)
		mCamera->SetPosition(mPlayer->GetPosition().x + 30, mMap->GetHeight()-20);*/
	//if (mCamera->GetBound().left < 0)
	//{
	//	//vi position cua camera ma chinh giua camera
	//	//luc nay o vi tri goc ben trai cua the gioi thuc
	//	mCamera->SetPosition(mCamera->GetWidth() / 2, mCamera->GetPosition().y);
	//	return;
	//}

	//if (mCamera->GetBound().right > mMap->GetWidth())
	//{
	//	//mMap1 = new GameMap("Resources/Map/NewMap1.tmx",mCamera->GetPosition().x,mCamera->GetPosition().y);
	//	if (mMapNext == NULL) {
	//		mMapNext = new GameMap("Resources/Map/NewMap1.tmx", 2300, 750);
	//		mMapNext->SetCamera(mCamera);
	//	}
	//}
	//	//mMap = new GameMap("Resources/Map/NewMap0.tmx");
	//	//luc nay cham goc ben phai cua the gioi thuc
	//	//mCamera->SetPosition(mMap->GetWidth() - mCamera->GetWidth() / 2,
	//		//mCamera->GetPosition().y);
	//		//kích thước bằng màn hình
	//	//mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	//	//vị trí giữa màn hình
	//	//mCamera->SetPosition(GameGlobal::GetWidth() / 2, mMapNext->GetHeight() - mCamera->GetHeight());
	//	return;
	//}

	//if (mCamera->GetBound().top < 0)
	//{
	//	//luc nay cham goc tren the gioi thuc
	//	mCamera->SetPosition(mCamera->GetPosition().x, mCamera->GetHeight() / 2);
	//	return;
	//}

	//if (mCamera->GetBound().bottom > mMap->GetHeight())
	//{
	//	//luc nay cham day cua the gioi thuc
	//	mCamera->SetPosition(mCamera->GetPosition().x,
	//		mMap->GetHeight() - mCamera->GetHeight() / 2);
	//	return;
	//}
	//
	return;
}