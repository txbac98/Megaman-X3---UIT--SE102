#include "ViewPort.h"

ViewPort::ViewPort()
{

	mListMap.push_back(new GameMap("Resources/Map/NewMap/Map0.tmx", 0, 512));	//0	ngang
	mListMap.push_back(new GameMap("Resources/Map/NewMap/Map1.tmx", 768, 0));	//1	doc
	mListMap.push_back(new GameMap("Resources/Map/NewMap/Map2.tmx", 1024, 0));	//2	ngang
	mListMap.push_back(new GameMap("Resources/Map/NewMap/Map3.tmx", 1536, 255));	//3	doc
	mListMap.push_back(new GameMap("Resources/Map/NewMap/Map4.tmx", 2304, 768));	//4	Boss 1
	mListMap.push_back(new GameMap("Resources/Map/NewMap/Map5.tmx", 2559, 580));	//5	ngang
	mListMap.push_back(new GameMap("Resources/Map/NewMap/Map6.tmx", 5631, 766));	//6	doc
	mListMap.push_back(new GameMap("Resources/Map/NewMap/Map7.tmx", 5887, 1523));	//7	ngang
	mListMap.push_back(new GameMap("Resources/Map/NewMap/Map8.tmx", 7167, 1535));	//8 Boss hornet

	iCurrentMap = 0;
	mCurrentMap = mListMap.at(iCurrentMap);
	mNextMap = mListMap.at(iCurrentMap+1);
	canUpdateCamera = false;
}

ViewPort::~ViewPort()
{
}

void ViewPort::Update(float dt)
{
	mCurrentMap->Update(dt);
	if (mBackMap) mBackMap->Update(dt);
	if (mNextMap) mNextMap->Update(dt);
	CheckCameraWithWouldMap();
	UpdateCamera(dt);
}

void ViewPort::UpdateCamera(float dt)
{
	/*if (canUpdateCamera) {*/
		if (mCamera->GetPosition().y == posCameraY && mCamera->GetPosition().x == posCameraX) {
			canUpdateCamera = false;
			return;
		}
		if (mCamera->GetPosition().y != posCameraY)
			if (mCamera->GetPosition().y < posCameraY) 
			{
				if (mCamera->GetPosition().y + 100*dt > posCameraY)
					mCamera->SetPositionY(posCameraY);
				else mCamera->SetPositionY(mCamera->GetPosition().y + 100*dt);
			}
			else {
				if (mCamera->GetPosition().y - 100 * dt < posCameraY)
					mCamera->SetPositionY(posCameraY);
				else mCamera->SetPositionY(mCamera->GetPosition().y - 100 * dt);
			}
		if (mCamera->GetPosition().x != posCameraX)
			if (mCamera->GetPosition().x < posCameraX)
			{
				if (mCamera->GetPosition().x + 100 * dt > posCameraX)
					mCamera->SetPositionX(posCameraX);
				else mCamera->SetPositionX(mCamera->GetPosition().x + 100 * dt);
			}
			else {
				if (mCamera->GetPosition().x - 100 * dt < posCameraX)
					mCamera->SetPositionX(posCameraX);
				else mCamera->SetPositionX(mCamera->GetPosition().x - 100 * dt);
			}
}

void ViewPort::ChangeCurrentMap()
{
	//Change Map
	D3DXVECTOR2 posCamera, posPlayer;
	posCamera = mCamera->GetPosition();

	
	if (mBackMap) {
		RECT rectBackMap = mBackMap->GetWorldMapBound();
		//Xét đã vào trong Back map hay chưa
		if (mPlayer->posX > rectBackMap.left && mPlayer->posX < rectBackMap.right
			&& mPlayer->posY < rectBackMap.bottom && mPlayer->posY > rectBackMap.top) {
			iCurrentMap--;
			mNextMap = mCurrentMap;
			mCurrentMap = mBackMap;
			if (iCurrentMap < 1)
				mBackMap = NULL;
			else mBackMap = mListMap.at(iCurrentMap - 1);
		}
	}
	if (mNextMap) {
		RECT rectNextMap = mNextMap->GetWorldMapBound();
		//Xét đã vào trong next map hay chưa
		if (mPlayer->posX > rectNextMap.left && mPlayer->posX < rectNextMap.right
			&& mPlayer->posY < rectNextMap.bottom && mPlayer->posY > rectNextMap.top) {
			iCurrentMap++;
			mBackMap = mCurrentMap;
			mCurrentMap = mNextMap;
			if (iCurrentMap < mListMap.size() - 1)
				mNextMap = mListMap.at(iCurrentMap + 1);
			else mNextMap = NULL;
		}
	}
}
void ViewPort::CheckCameraWithWouldMap()
{
	ChangeCurrentMap();

	//Set position camera
	if (mCamera && mPlayer) {
		//mCamera->SetPositionX(mPlayer->posX + 30);
		//mCamera->SetPositionY(mPlayer->posY);
		switch (iCurrentMap)
		{
		case 0:	//Done
			this->SetCameraPositionX(mPlayer->posX + 30);
			if (mCamera->GetBound().left <= mCurrentMap->PosX)
				this->SetCameraPositionX(mCurrentMap->PosX + mCamera->GetWidth() / 2);
			this->SetCameraPositionY(640);
			break;
		case 1:		//Đi lên thang máy
			if (mPlayer->posY < 600) {
				if (mPlayer->posY > 167) {
					posCameraY = mPlayer->posY -30;
					this->SetCameraPositionX(mCurrentMap->PosX + mCamera->GetWidth() / 2);
				}
				else {
					posCameraY = mCurrentMap->PosY + mCamera->GetHeight() / 2;
					posCameraX = mPlayer->posX + 30;
					if (posCameraX - mCamera->GetWidth() / 2 <= mCurrentMap->PosX) {	//phía bên trái, không cho qua
						this->SetCameraPositionX(mCurrentMap->PosX + mCamera->GetWidth() / 2);
					}
				}
			}
			else {	//Phía dưới
				this->SetCameraPositionY(640);
				if (mCamera->GetBound().right >= mCurrentMap->GetWidth() + mCurrentMap->PosX  )
				{
					this->SetCameraPositionX(mCurrentMap->PosX + mCamera->GetWidth() / 2);
				}
				else this->SetCameraPositionX(mPlayer->posX + 30);
			}
			break;
		case 2:
			this->SetCameraPositionX(mPlayer->posX +30);
			this->SetCameraPositionY(mCurrentMap->PosY + mCamera->GetHeight() / 2);
			break;
		case 3:
			this->SetCameraPositionX(mPlayer->posX + 30);
			this->SetCameraPositionY(mPlayer->posY - 20);
			break;
		case 4:
			this->SetCameraPositionX(mPlayer->posX + 30);
			this->SetCameraPositionY(mPlayer->posY - 20);
			break;

		default:
			this->SetCameraPositionX(mPlayer->posX + 30);
			this->SetCameraPositionY(mPlayer->posY - 20);
			break;
		}
	}
		

	//if (mCamera->GetBound().left < mCurrentMap->PosX)
	//{
	//	//if (iNextMap != 5)	//map current ==4 la boss
	//	//luc nay o vi tri goc ben trai cua the gioi thuc
	//	mCamera->SetPosition(mCurrentMap->PosX + mCamera->GetWidth() / 2, mCamera->GetPosition().y);
	//	return;
	//}

	//if (mCamera->GetBound().right > mCurrentMap->GetWidth() + mCurrentMap->PosX)
	//{
	//	//if (iNextMap != 5)	//map current ==4 la boss
	//		//luc nay cham goc ben phai cua the gioi thuc
	//		mCamera->SetPosition(mCurrentMap->GetWidth() + mCurrentMap->PosX - mCamera->GetWidth() / 2,
	//			mCamera->GetPosition().y);
	//		return;
	//}
	

	//if (mCamera->GetBound().top < 0)
	//{
	//	//luc nay cham goc tren the gioi thuc
	//	//mCamera->SetPosition(mCamera->GetPosition().x, mCamera->GetHeight() / 2);
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

void ViewPort::Draw()
{
	if (mCurrentMap)	mCurrentMap->Draw();
	if (mNextMap) mNextMap->Draw();
	if (mBackMap) mBackMap->Draw();
}



void ViewPort::SetCamera(Camera * camera)
{
	mCamera = camera;
	for (size_t i = 0; i < mListMap.size(); i++) {
		mListMap.at(i)->SetCamera(camera);
	}
	if (mCurrentMap)
		mCurrentMap->SetCamera(camera);
	if (mNextMap)
		mNextMap->SetCamera(camera);
	if (mBackMap)
		mBackMap->SetCamera(camera);
}

void ViewPort::SetPlayer(Player * player)
{
	mPlayer = player;
}

void ViewPort::SetCameraPositionX(float x)
{
	posCameraX = x;
	mCamera->SetPositionX(x);
}

void ViewPort::SetCameraPositionY(float y)
{
	posCameraY = y;
	mCamera->SetPositionY(y);
}

int ViewPort::GetHeightMap()
{
	return mCurrentMap->GetHeight();
}

int ViewPort::GetWidthMap()
{
	return mCurrentMap->GetWidth();
}

void ViewPort::GetMapObject(std::vector<Entity*>& entitiesOut, Entity * entity)
{
	std::vector<Entity*> mListObjectMap;
	mCurrentMap->GetQuadTree()->getEntitiesCollideAble(mListObjectMap, entity);
	for (size_t i = 0; i < mListObjectMap.size(); i++) {
		entitiesOut.push_back(mListObjectMap.at(i));
	}
	if (mNextMap) {
		std::vector<Entity*> mListObjectMap;
		mNextMap->GetQuadTree()->getEntitiesCollideAble(entitiesOut, entity);
		for (size_t i = 0; i < mListObjectMap.size(); i++) {
			entitiesOut.push_back(mListObjectMap.at(i));
		}
	}
	if (mBackMap) {
		std::vector<Entity*> mListObjectMap;
		mBackMap->GetQuadTree()->getEntitiesCollideAble(entitiesOut, entity);
		for (size_t i = 0; i < mListObjectMap.size(); i++) {
			entitiesOut.push_back(mListObjectMap.at(i));
		}
	}
}
