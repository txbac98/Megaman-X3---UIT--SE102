#include "ViewPort.h"


ViewPort* ViewPort::instance = 0;
ViewPort* ViewPort::getInstance()
{
	if (instance == 0)
		instance = new ViewPort();
	return instance;
}

void ViewPort::Init(Player *player)
{
	mPlayer = player;
	mListMap.push_back(new GameMap("Resources/Map/NewMap/Map0.tmx", 0, 512));	//0	ngang, không chuyển map, khóa: trái
	mListMap.push_back(new GameMap("Resources/Map/NewMap/Map1.tmx", 768, 0));	//1	doc, không chuyển map, khóa trái, phải ở phía trên <600
	mListMap.push_back(new GameMap("Resources/Map/NewMap/Map2.tmx", 1024, 0));	//2	ngang, chuyển map phái dướt, khóa: phải
	mListMap.push_back(new GameMap("Resources/Map/NewMap/Map3.tmx", 1536, 255));	//3	doc, chuyển map phía trên, khóa trái, phải phía trên
	mListMap.push_back(new GameMap("Resources/Map/NewMap/Map4.tmx", 2304, 769));	//4	Boss 1
	mListMap.push_back(new GameMap("Resources/Map/NewMap/Map5.tmx", 2559, 610));	//5	ngang, 
	mListMap.push_back(new GameMap("Resources/Map/NewMap/Map6.tmx", 5631, 769));	//6	doc
	mListMap.push_back(new GameMap("Resources/Map/NewMap/Map7.tmx", 5887, 1527));	//7	ngang
	mListMap.push_back(new GameMap("Resources/Map/NewMap/Map8.tmx", 7167, 1537));	//8 Boss hornet

	iCurrentMap = 0;
	//mPlayer->SetPosition(7190, 1620);  //Test Boss 8
	//mPlayer->SetPosition(5700, 800);		//Test map 6
	//mPlayer->SetPosition(2559, 610);		//Map 5:: Carry
	//mPlayer->SetPosition(2390, 800);		//Genji
	mCurrentMap = mListMap.at(iCurrentMap);
	mNextMap = mListMap.at(iCurrentMap+1);
	canUpdateCamera = false;
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
			if (iCurrentMap == 4 || iCurrentMap==5 || iCurrentMap==6 || iCurrentMap==8) mPlayer->AddPositionX(20);
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

		//mCamera->SetPosition(mPlayer->GetPosition());	//Test map
		
		if (mPlayer->posY > mCurrentMap->GetWorldMapBound().bottom)
			mPlayer->Die();
		else 
		switch (iCurrentMap)
		{
		case 0:	//Done		//Ngang
			this->SetCameraPositionX(mPlayer->posX + 30);
			if (mCamera->GetBound().left <= mCurrentMap->PosX)
				this->SetCameraPositionX(mCurrentMap->PosX + mCamera->GetWidth() / 2);
			this->SetCameraPositionY(mCurrentMap->PosY + mCamera->GetHeight() / 2);
				//640
			break;
		case 1:		//Doc	//Thang may
			if (mPlayer->posY < 600) {
				if (mPlayer->posY > 167) {
					posCameraY = mPlayer->posY -30;
					this->SetCameraPositionX(mCurrentMap->PosX + mCamera->GetWidth() / 2);
				}
				else {
					posCameraY = mCurrentMap->PosY+ mCamera->GetHeight()/2;
					//this->SetCameraPositionY(mPlayer->posY - 20);
					posCameraX = mPlayer->posX + 30;
					if (posCameraX - mCamera->GetWidth() / 2 < mCurrentMap->PosX) {	//phía bên trái
						this->SetCameraPositionX(mCurrentMap->PosX + mCamera->GetWidth() / 2);
					}
				}
			}
			else {	//Phía dưới
				posCameraY = mCurrentMap->GetWorldMapBound().bottom - mCamera->GetHeight() / 2;//640
				if (mCamera->GetBound().right >= mCurrentMap->GetWidth() + mCurrentMap->PosX  )
				{
					this->SetCameraPositionX(mCurrentMap->PosX + mCamera->GetWidth() / 2);
				}
				else this->SetCameraPositionX(mPlayer->posX + 30);
			}
			break;
		case 2:	//ngang	//done
			this->SetCameraPositionX(mPlayer->posX +30);
			this->SetCameraPositionY(mCurrentMap->PosY + mCamera->GetHeight() / 2);
			if (mCamera->GetBound().right > mCurrentMap->GetWidth() + mCurrentMap->PosX) {	//bên phải
				this->SetCameraPositionX(mCurrentMap->GetWorldMapBound().right - mCamera->GetWidth() / 2);
			}
			break;
		case 3:	//doc	//done
			this->SetCameraPositionX(mPlayer->posX + 30);
			if (mCamera->GetBound().left < mCurrentMap->PosX) {	//phía bên trái
				this->SetCameraPositionX(mCurrentMap->PosX + mCamera->GetWidth() / 2);
			}
			if (mPlayer->posY > mCurrentMap->GetWorldMapBound().bottom- 256)	//chạm đáy cho map dọc	//256 cho 1 màn hình
			{
				this->SetCameraPositionY(mCurrentMap->GetWorldMapBound().bottom - mCamera->GetHeight() / 2);
				//posCameraY=(mCurrentMap->GetWorldMapBound().bottom - mCamera->GetHeight() / 2);		
			}
			else this->SetCameraPositionY(mPlayer->posY - 20);
			if (mCamera->GetBound().right > mCurrentMap->GetWidth() + mCurrentMap->PosX) {	//bên phải
				this->SetCameraPositionX(mCurrentMap->GetWorldMapBound().right - mCamera->GetWidth() / 2);
			}
			break;
		case 4:	//boss	//done
			this->SetCameraPositionX(mCurrentMap->PosX + mCamera->GetWidth() / 2);
			this->SetCameraPositionY(mCurrentMap->PosY + mCamera->GetHeight() / 2);
			break;
		case 5:	//ngang  //can xet lai vi tri
			this->SetCameraPositionX(mPlayer->posX + 30);
			if (posCameraX - mCamera->GetWidth() / 2 < mCurrentMap->PosX) {	//phía bên trái
				this->SetCameraPositionX(mCurrentMap->PosX + mCamera->GetWidth() / 2);
			}
			if (mCamera->GetBound().right > mCurrentMap->GetWidth() + mCurrentMap->PosX) {	//bên phải
				this->SetCameraPositionX(mCurrentMap->GetWorldMapBound().right - mCamera->GetWidth() / 2);
			}
			if (mPlayer->posY > mCurrentMap->GetWorldMapBound().bottom - 256)	//chạm đáy cho map dọc	//256 cho 1 màn hình
			{
				posCameraY=mCurrentMap->GetWorldMapBound().bottom - mCamera->GetHeight() / 2;
				//posCameraY=(mCurrentMap->GetWorldMapBound().bottom - mCamera->GetHeight() / 2);		
			}
			else if (mPlayer->posY < mCurrentMap->GetWorldMapBound().top + 256)	//chạm top
			{
				posCameraY=mCurrentMap->GetWorldMapBound().top + mCamera->GetHeight() / 2;
				//posCameraY=(mCurrentMap->GetWorldMapBound().bottom - mCamera->GetHeight() / 2);		
			}
			else posCameraY = mPlayer->posY - 20;
			break;
		case 6:	//doc	//done
			this->SetCameraPositionX(mPlayer->posX + 30);
			if (mPlayer->posY > mCurrentMap->GetWorldMapBound().bottom - 256)	//chạm đáy cho map dọc	//256 cho 1 màn hình
			{
				posCameraY = (mCurrentMap->GetWorldMapBound().bottom - mCamera->GetHeight() / 2 - 10);
			}
			else if(mPlayer->posY < mCurrentMap->GetWorldMapBound().top + 256) {	// ở trên
				posCameraY = (mCurrentMap->GetWorldMapBound().top + mCamera->GetHeight() / 2);	
				if (mCamera->GetBound().right > mCurrentMap->GetWidth() + mCurrentMap->PosX) {	//bên phải
					this->SetCameraPositionX(mCurrentMap->GetWorldMapBound().right - mCamera->GetWidth() / 2);
				}
			}
			else {// ở giữa
				this->SetCameraPositionY(posCameraY=mPlayer->posY);
				if (mCamera->GetBound().right > mCurrentMap->GetWidth() + mCurrentMap->PosX) {	//bên phải
					this->SetCameraPositionX(mCurrentMap->GetWorldMapBound().right - mCamera->GetWidth() / 2);
				}
			}
			if (mCamera->GetBound().left < mCurrentMap->PosX) {	//phía bên trái
				this->SetCameraPositionX(mCurrentMap->PosX + mCamera->GetWidth() / 2);
			}
			
			
			break;
		case 7:	//ngang //done
			this->SetCameraPositionX(mPlayer->posX + 30);
			this->SetCameraPositionY(mCurrentMap->GetWorldMapBound().bottom - mCamera->GetHeight() / 2);
			if (mCamera->GetBound().right > mCurrentMap->GetWidth() + mCurrentMap->PosX) {	//bên phải
				this->SetCameraPositionX(mCurrentMap->GetWorldMapBound().right - mCamera->GetWidth() / 2);
			}
			break;
		case 8:	//boss	//done
			this->SetCameraPositionX(mCurrentMap->PosX + mCamera->GetWidth() / 2);
			this->SetCameraPositionY(mCurrentMap->PosY + mCamera->GetHeight() / 2);
			break;
		default:
			/*this->SetCameraPositionX(mPlayer->posX + 30);
			this->SetCameraPositionY(mPlayer->posY - 20);*/
			break;
		}
	}
	return;
}
void ViewPort::GetMapObject(std::vector<Entity*>& entitiesOut, Entity * entity)
{
	std::vector<Entity*> mListObjectMap;
	mCurrentMap->GetQuadTree()->getEntitiesCollideAble(mListObjectMap, entity);
	for (size_t i = 0; i < mListObjectMap.size(); i++) {
		entitiesOut.push_back(mListObjectMap.at(i));
	}
	/*if (mNextMap) {
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
	}*/
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


