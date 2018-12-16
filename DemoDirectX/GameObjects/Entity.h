#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <map>

class Entity 
{

public:

    Entity();
	
    enum SideCollisions
    {
        Left, //0
        Right, //1
        Top, //2
        Bottom, //3
        TopLeft, //4
        TopRight, //5
        BottomLeft, //6
        BottomRight, //7
        NotKnow,
    };

    struct CollisionReturn
    {
        bool IsCollided;
        RECT RegionCollision;
    };

    enum EntityTypes
    {
        Megaman, MegaBullet, None, Wall, Box, SubCarryarm, Carryarm, DebrisCarryarm, Spine, Elevator, Door, Brick, Enemy, EnemiesBullet, Notorbanger,
		PosNotorbanger, HeadgunnerLeft, HeadgunnerRight, Helit, Genjibo, SlopingWall, ConveyorRight, ConveyorLeft, Stone5, Stone3
    };
	enum EntityKind
	{
		Static, Dynamic
	};

    EntityTypes Tag; //Tag de nhan vien loai Entity
	EntityKind	Kind; //Loại tĩnh hay động

    virtual RECT GetBound();
	//virtual RectF GetBoundF();
	virtual D3DXVECTOR2 GetPosition();

	virtual void Draw(D3DXVECTOR2 transform);

    virtual void SetPosition(float x, float y);

    virtual void SetPosition(D3DXVECTOR2 pos);

	virtual void AddPositionX(float x);

	virtual void AddPositionY(float y);

    virtual void AddPosition(D3DXVECTOR2 pos);

    virtual void AddPosition(float x, float y);

	virtual SideCollisions GetPhysicsBodySide();
	
	virtual void SetPhysicsBodySide(Entity::SideCollisions side);

    virtual void SetWidth(int width);

    virtual int GetWidth();

    virtual void SetHeight(int height);

    virtual int GetHeight();

    virtual float GetVx();

    virtual void SetVx(float vx);

    virtual void AddVx(float vx);

    virtual float GetVy();

    virtual void SetVy(float vy);

    virtual void AddVy(float vy);

   

    virtual void Update(float dt);
	
    //kiem soat viec va cham
	virtual void OnCollision(Entity * other, SideCollisions side);

	virtual void OnAABBCheck(Entity *other);

	RECT getCollisionRect(RECT rect);

	bool IntersectRect(RECT rect);

	//virtual bool AABBCheck(Entity * other);

    //duoc goi khi set position cua Entity, dung cho ke thua
    virtual void OnSetPosition(D3DXVECTOR2 pos);
	//virtual float checkCollision(Entity* object, float dt);
	virtual void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
    //vi tri tam position x va y
    float posX, posY;

	bool isCollision;
	bool isAlive=false;
	bool isSpawn = false;
	bool isCollisionCross;
	bool isFaceLeft;
	int dame;
	int hp;
	bool isFaceRight;
    //phan toc vx, vy
    float vx=0, vy=0;

    //size cua entity
    float width, height;

	//side 
	SideCollisions physicsSide;
};