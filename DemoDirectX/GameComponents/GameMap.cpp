#pragma once
#include "GameMap.h"

GameMap::GameMap(char* filePath, char *fileQuadTree, int posx, int posy)
{
    mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	PosX = posx;
	PosY = posy;
	//Xoa du lieu fie quadtree
	ofstream fQuadTree;
	fQuadTree.open(fileQuadTree, ios::out | ios::trunc);
	fQuadTree.close();

    LoadMap(filePath,fileQuadTree);
}

GameMap::GameMap(char * filePath, char *fileQuadTree, Camera * camera, int posx, int posy)
{
	mCamera = camera;
	PosX = posx;
	PosY = posy;
	LoadMap(filePath, fileQuadTree);
}

GameMap::GameMap()
{
}

GameMap::~GameMap()
{
    delete mMap;
    for (size_t i = 0; i < mListTileset.size(); i++)
    {
        if (mListTileset[i])
            delete mListTileset[i];
    }
    mListTileset.clear();

    delete mQuadTree;
}

void GameMap::LoadMap(char* filePath, char* fileQuadTree)
{
    mMap = new Tmx::Map();
    mMap->ParseFile(filePath);

    RECT r;
    r.left = PosX;
    r.top = PosY;
    r.right = PosX+ this->GetWidth();
    r.bottom = PosY + this->GetHeight();

    mQuadTree = new QuadTree(0, 0, r, fileQuadTree);

	//nạp từng viên gạch vào listTileset
    for (size_t i = 0; i < mMap->GetNumTilesets(); i++)
    {
        const Tmx::Tileset *tileset = mMap->GetTileset(i);

        Sprite *sprite = new Sprite(tileset->GetImage()->GetSource().c_str());
        mListTileset.insert(pair<int, Sprite*>(i, sprite));
    }

    //khoi tao cac khoi Brick (vien gach)
#pragma region -BRICK AND COIN LAYER-
    //for (size_t i = 0; i < GetMap()->GetNumTileLayers(); i++)
    //{
    //    const Tmx::TileLayer *layer = mMap->GetTileLayer(i);

    //    if (layer->IsVisible())
    //        continue;

    //    //xac dinh layer Brick bi an di de tu do tao ra cac vien gach trong game, nhung vien gach khong phai la 1 physic static nos co the bi pha huy duoc

    //    if (layer->GetName() == "brick" || layer->GetName() == "coin")
    //    {
    //        for (size_t j = 0; j < mMap->GetNumTilesets(); j++)
    //        {
    //            const Tmx::Tileset *tileSet = mMap->GetTileset(j);

    //            int tileWidth = mMap->GetTileWidth();
    //            int tileHeight = mMap->GetTileHeight();

    //            int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
    //            int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

    //            for (size_t m = 0; m < layer->GetHeight(); m++)
    //            {
    //                for (size_t n = 0; n < layer->GetWidth(); n++)
    //                {
    //                    if (layer->GetTileTilesetIndex(n, m) != -1)
    //                    {
    //                        int tileID = layer->GetTileId(n, m);

    //                        int y = tileID / tileSetWidth;
    //                        int x = tileID - y * tileSetWidth;

    //                        RECT sourceRECT;
    //                        sourceRECT.top = y * tileHeight;
    //                        sourceRECT.bottom = sourceRECT.top + tileHeight;
    //                        sourceRECT.left = x * tileWidth;
    //                        sourceRECT.right = sourceRECT.left + tileWidth;

    //                        RECT bound;
    //                        bound.left = n * tileWidth;
    //                        bound.top = m * tileHeight;
    //                        bound.right = bound.left + tileWidth;
    //                        bound.bottom = bound.top + tileHeight;

    //                        D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2, 0);

    //                        Brick *brick = nullptr;

    //                        if (layer->GetName() == "coin")
    //                        {
    //                            brick = new BrickGold(position);
    //                            brick->Tag = Entity::EntityTypes::BrickGoldNormal;
    //                            mListBricks.push_back(brick);
    //                        }
    //                        else
    //                        {
    //                            brick = new BrickNormal(position);
    //                            brick->Tag = Entity::EntityTypes::Brick;
    //                            mListBricks.push_back(brick);
    //                        }


    //                        if (brick)
    //                            mQuadTree->insertEntity(brick);
    //                    }
    //                }
    //            }
    //        }
    //    }
    //}

#pragma endregion

#pragma region -OBJECTGROUP, STATIC OBJECT-

    for (size_t i = 0; i < mMap->GetNumObjectGroups(); i++)
    {
        const Tmx::ObjectGroup *objectGroup = mMap->GetObjectGroup(i);

        for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
        {
            //lay object group chu khong phai layer
            //object group se chua nhung body
            Tmx::Object *object = objectGroup->GetObjects().at(j);
			
			Entity *entity = new Entity();
			entity->Tag = Entity::EntityTypes::Wall;
			float posX = PosX + object->GetX() + object->GetWidth() / 2;
			float posY = PosY + object->GetY() + object->GetHeight() / 2;

			if (object->GetName() == "Elevator") {
				 Elevator *elevator= new Elevator(posX, posY);
				 mListEntity.push_back(elevator);
				 mQuadTree->insertEntity(elevator, object->GetId());
			}
			else if(object->GetName()=="Door"){
				Door *door = new Door(posX, posY);
				mListEntity.push_back(door);
				mQuadTree->insertEntity(door, object->GetId());
			}
			else if (object->GetName() == "Notorbanger") {
				//Notorbanger *notor = new Notorbanger( posX, posY);
				entity->Tag = Entity::EntityTypes::Notorbanger;
				entity->SetPosition(posX, posY);
				entity->SetWidth(object->GetWidth());
				entity->SetHeight(object->GetHeight());
				mListEntity.push_back(entity);
				mQuadTree->insertEntity(entity, object->GetId());
			}
			else if (object->GetName() == "Headgunner Right") {
				HeadGunner *head = new HeadGunner(posX, posY, true);
				mListEntity.push_back(head);
				mQuadTree->insertEntity(head, object->GetId());
			}
			else if (object->GetName() == "Headgunner Left") {
				HeadGunner *head = new HeadGunner(posX, posY, false);
				mListEntity.push_back(head);
				mQuadTree->insertEntity(head, object->GetId());
			}
			else if (object->GetName() == "Helit") {
				Helit *helit = new Helit(posX, posY);
				mListEntity.push_back(helit);
				mQuadTree->insertEntity(helit, object->GetId());
			}
			else {
				entity->SetPosition(posX, posY);
				entity->SetWidth(object->GetWidth());
				entity->SetHeight(object->GetHeight());
				mQuadTree->insertEntity(entity, object->GetId());
			}
        }
    }
#pragma endregion
}

void GameMap::SetCamera(Camera* camera)
{
    mCamera = camera;
}

Tmx::Map* GameMap::GetMap()
{
    return mMap;
}

RECT GameMap::GetWorldMapBound()
{
    RECT bound;
	bound.left = PosX;
	bound.top = PosY;
    bound.right = PosX+ mMap->GetWidth() * mMap->GetTileWidth();
    bound.bottom = PosY +mMap->GetHeight() * mMap->GetTileHeight();

    return bound;
}

int GameMap::GetWidth()
{
    return mMap->GetWidth() * mMap->GetTileWidth();
}

int GameMap::GetHeight()
{
    return mMap->GetHeight() * mMap->GetTileHeight();
}

int GameMap::GetTileWidth()
{
    return mMap->GetTileWidth();
}

int GameMap::GetTileHeight()
{
    return mMap->GetTileHeight();
}

bool GameMap::IsBoundLeft()
{
    return (mCamera->GetBound().left == 0);
}

bool GameMap::IsBoundRight()
{
    return (mCamera->GetBound().right == this->GetWidth());
}

bool GameMap::IsBoundTop()
{
    return (mCamera->GetBound().top == 0);
}

bool GameMap::IsBoundBottom()
{
    return (mCamera->GetBound().bottom == this->GetHeight());
}

void GameMap::Update(float dt)
{
	for (size_t i = 0; i < mListEntity.size(); i++) {
		mListEntity[i]->Update(dt);
			if (mListEntity[i]->Tag == Entity::EntityTypes::Notorbanger) {
				RECT rectCamera = mCamera->GetBound();
				RECT rectEntity = mListEntity[i]->GetBound();
				//va chạm với rìa camera
				if (rectCamera.left==rectEntity.right || rectCamera.right==rectEntity.left ||
					rectCamera.top==rectEntity.bottom || rectCamera.bottom==rectEntity.top) 
				{
					if (!mListEntity[i]->isAlive)	//Chưa sinh ra hoặc đã chết
						mListEntity[i] = new Notorbanger(mListEntity[i]->posX, mListEntity[i]->posY);
				}
				
				//if (!mListEntity[i]->isSpawn)	
				
			}
			
			//va chạm map
			std::vector<Entity*> mListObjectMap;
			this->GetQuadTree()->getEntitiesCollideAble(mListObjectMap, mListEntity[i]);
			for (size_t j = 0; j < mListObjectMap.size(); j++) {
				CollisionManager::getInstance()->checkCollision(mListEntity[i], mListObjectMap[j], dt);
			
		}
		
	}
	for (size_t i = 0; i < mListElevator.size(); i++)
	{
		mListElevator[i]->Update(dt);
	}
	for (size_t i = 0; i < mListDoor.size(); i++)
	{
		mListDoor[i]->Update(dt);
	}

	

	//check collision
	
}

void GameMap::Draw()
{
    D3DXVECTOR2 trans = D3DXVECTOR2(int(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x ),
       int( GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y ));


#pragma region DRAW TILESET
    for (size_t i = 0; i < mMap->GetNumTileLayers(); i++)
    {
        const Tmx::TileLayer *layer = mMap->GetTileLayer(i);

        if (!layer->IsVisible())
        {
            continue;
        }

        for (size_t j = 0; j < mMap->GetNumTilesets(); j++)
        {
            const Tmx::Tileset *tileSet = mMap->GetTileset(j);

            RECT sourceRECT;

            int tileWidth = mMap->GetTileWidth();
            int tileHeight = mMap->GetTileHeight();

            int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
            int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

            for (size_t m = 0; m < layer->GetHeight(); m++)
            {
                for (size_t n = 0; n < layer->GetWidth(); n++)
                {
                    if (layer->GetTileTilesetIndex(n, m) != -1)
                    {
                        int tileID = layer->GetTileId(n, m);

                        int y = tileID / tileSetWidth;
                        int x = tileID - y * tileSetWidth;

                        sourceRECT.top = y * tileHeight;
                        sourceRECT.bottom = sourceRECT.top + tileHeight;
                        sourceRECT.left = x * tileWidth;
                        sourceRECT.right = sourceRECT.left + tileWidth;

                        Sprite* sprite = mListTileset[j];

                        //tru tilewidth/2 va tileheight/2 vi Sprite ve o vi tri giua hinh anh cho nen doi hinh de cho
                        //dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);
                        D3DXVECTOR3 position(PosX +  n * tileWidth + tileWidth / 2,PosY + m * tileHeight + tileHeight / 2, 0);

                        if (mCamera != NULL)
                        {
                            RECT objRECT;
                            objRECT.left = position.x - tileWidth / 2;
                            objRECT.top = position.y - tileHeight / 2;
                            objRECT.right = objRECT.left + tileWidth;
                            objRECT.bottom = objRECT.top + tileHeight;

							if (!CollisionManager::getInstance()->AABBCheck(mCamera->GetBound(), objRECT))
								//Không va chạm thì không vẽ
                                continue;
                        }

                        sprite->SetWidth(tileWidth);
                        sprite->SetHeight(tileHeight);

                        sprite->Draw(position, sourceRECT, D3DXVECTOR2(), trans);
                    }
                }
            }
        }
    }
#pragma endregion

#pragma region DRAW Entity

	for (size_t i = 0; i < mListEntity.size(); i++)
	{
		mListEntity[i]->Draw(trans);
	}
	for (size_t i = 0; i < mListDoor.size(); i++) {
		mListDoor[i]->Draw(trans);
	}
	for (size_t i = 0; i < mListNotor.size(); i++) {
		mListNotor[i]->Draw(trans);
	}
#pragma endregion
}

std::map<int, Sprite*> GameMap::getListTileSet()
{
    return mListTileset;
}


QuadTree * GameMap::GetQuadTree()
{
    return mQuadTree;
}
