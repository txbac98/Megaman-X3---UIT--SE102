#pragma once
#include "GameMap.h"
#include "ViewPort.h"

GameMap::GameMap(char* filePath, char *fileQuadTree, int posx, int posy)
{
    //mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	mCamera = ViewPort::getInstance()->mCamera;
	mPlayer = ViewPort::getInstance()->mPlayer;
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
			entity->isAlive = false;
			entity->isSpawn = false;
			entity->Kind = Entity::EntityKind::Static;
			float posX = PosX + object->GetX() + object->GetWidth() / 2;
			float posY = PosY + object->GetY() + object->GetHeight() / 2;

			if (object->GetName() == "Elevator") {
				entity->Tag = Entity::EntityTypes::Elevator;
				entity=new Elevator(mListEntity[i]->posX, mListEntity[i]->posY);
			}
			else if(object->GetName()=="Door"){
				entity->Tag = Entity::EntityTypes::DoorObject;
				entity = new Door(mListEntity[i]->posX, mListEntity[i]->posY);
			}
			else if (object->GetName() == "Spine") {
				entity->Tag= Entity::EntityTypes::Spine;
				entity->isAlive = true;			
			}
			else if (object->GetName() == "Conveyor Right") {
				entity->Tag = Entity::EntityTypes::ConveyorRight;
			}
			else if (object->GetName() == "Conveyor Left") {
				entity->Tag = Entity::EntityTypes::ConveyorLeft;
			}
			else if (object->GetName() == "Genjibo") {
				entity->Tag = Entity::EntityTypes::Genjibo;
			}
			else if (object->GetName() == "Notorbanger") {
				//Notorbanger *notor = new Notorbanger( posX, posY);
				entity->Tag = Entity::EntityTypes::Notorbanger;
			}
			else if (object->GetName() == "Headgunner Right") {
				entity->Tag = Entity::EntityTypes::HeadgunnerRight;
			}
			else if (object->GetName() == "Headgunner Left") {
				entity->Tag = Entity::EntityTypes::HeadgunnerLeft;
			}
			else if (object->GetName() == "Helit") {
				entity->Tag = Entity::EntityTypes::Helit;
			}
			else if (object->GetName() == "Sloping Wall") {
				entity->Tag = Entity::EntityTypes::SlopingWall;
			}		
			else if (object->GetName() == "Box") {
				entity->Tag = Entity::EntityTypes::Box;
			}
			else if (object->GetName() == "SubCarryarm") {
				entity->Tag = Entity::EntityTypes::SubCarryarm;
			}
			else if (object->GetName() == "Carryarm") {
				entity->Tag = Entity::EntityTypes::Carryarm;
			}
			else if (object->GetName() == "Hornet") {
				entity->Tag = Entity::EntityTypes::HornetBoss;
			}
			else if (object->GetName() == "Stone5") {
				entity->Tag = Entity::EntityTypes::Stone5;
			}
			else if (object->GetName() == "Stone3") {
				entity->Tag = Entity::EntityTypes::Stone3;
			}
			else if (object->GetName() == "ItemHP") {
				entity->Tag = Entity::EntityTypes::ItemHP;
			}
			entity->SetPosition(posX, posY);
			entity->SetWidth(object->GetWidth());
			entity->SetHeight(object->GetHeight());
			mListEntity.push_back(entity);
			mQuadTree->insertEntity(entity, object->GetId());
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
	RECT rectCamera = mCamera->GetBound();

	for (size_t i = 0; i < mListEntity.size(); i++) {
		/*if (mListEntity[i]->Tag == Entity::EntityTypes::Elevator || mListEntity[i]->Tag == Entity::EntityTypes::Door) {
			mListEntity[i]->Update(dt);
		}
		else */
		if (mListEntity[i]->isSpawn) mListEntity[i]->Update(dt);

		if (!CollisionManager::getInstance()->AABBCheck(mCamera->GetBound(), mListEntity[i]->GetBound())) {
			if (!mListEntity[i]->isAlive) mListEntity[i]->isSpawn = false;
			//Không ở trong màn hình
			continue;
		}

		if (!mListEntity[i]->isAlive && !mListEntity[i]->isSpawn) {
			if (mListEntity[i]->Tag == Entity::EntityTypes::Notorbanger) {
				mListEntity[i] = new Notorbanger(mListEntity[i]->posX, mListEntity[i]->posY);
				continue;
			}
			if (mListEntity[i]->Tag == Entity::EntityTypes::Genjibo) {
				mListEntity[i] = new Genjibo(mListEntity[i]->posX, mListEntity[i]->posY);
				continue;
			}
			if (mListEntity[i]->Tag == Entity::EntityTypes::HeadgunnerLeft) {
				mListEntity[i] = new HeadGunner(mListEntity[i]->posX, mListEntity[i]->posY,false);
				continue;
			}
			if (mListEntity[i]->Tag == Entity::EntityTypes::HeadgunnerRight) {
				mListEntity[i] = new HeadGunner(mListEntity[i]->posX, mListEntity[i]->posY, true);
				continue;
			}
			if (mListEntity[i]->Tag == Entity::EntityTypes::Helit) {
				mListEntity[i] = new Helit(mListEntity[i]->posX, mListEntity[i]->posY);
				continue;
			}
			if (mListEntity[i]->Tag == Entity::EntityTypes::Box) {
				mListEntity[i] = new BoxObject(mListEntity[i]->posX, mListEntity[i]->posY);
				continue;
			}
			if (mListEntity[i]->Tag == Entity::EntityTypes::SubCarryarm) {
				mListEntity[i] = new SubCarry(mListEntity[i]->posX, mListEntity[i]->posY);
				continue;
			}
			if (mListEntity[i]->Tag == Entity::EntityTypes::Carryarm) {
				mListEntity[i] = new Carryarm(mListEntity[i]->posX, mListEntity[i]->posY);
				continue;
			}
			if (mListEntity[i]->Tag == Entity::EntityTypes::HornetBoss) {
				mListEntity[i] = new Hornet(mListEntity[i]->posX, mListEntity[i]->posY);
				continue;
			}
			if (mListEntity[i]->Tag == Entity::EntityTypes::DoorObject) {
				mListEntity[i] = new Door(mListEntity[i]->posX, mListEntity[i]->posY);
				continue;
			}
			if (mListEntity[i]->Tag == Entity::EntityTypes::Elevator) {
				mListEntity[i] = new Elevator(mListEntity[i]->posX, mListEntity[i]->posY);
				continue;
			}
			if (mListEntity[i]->Tag == Entity::EntityTypes::Stone5) {
				mListEntity[i] = new Stone(mListEntity[i]->posX, mListEntity[i]->posY, 5);
				continue;
			}
			if (mListEntity[i]->Tag == Entity::EntityTypes::Stone3) {
				mListEntity[i] = new Stone(mListEntity[i]->posX, mListEntity[i]->posY, 3);
				continue;
			}
			if (mListEntity[i]->Tag == Entity::EntityTypes::ItemHP) {
				mListEntity[i] = new ItemHP(mListEntity[i]->posX, mListEntity[i]->posY);
				continue;
			}
		}
	}
	
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
		if (mListEntity[i]->Tag != Entity::EntityTypes::Wall || mListEntity[i]->Tag!=Entity::EntityTypes::ConveyorLeft  
			|| mListEntity[i]->Tag != Entity::EntityTypes::ConveyorRight
				|| mListEntity[i]->Tag != Entity::EntityTypes::Spine){
			//if (!CollisionManager::getInstance()->AABBCheck(mCamera->GetBound(), mListEntity[i]->GetBound()))
			//	//Không va chạm thì không vẽ
			//	continue;
			if (mListEntity[i]->isSpawn)
				mListEntity[i]->Draw(trans);
		}
		
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
