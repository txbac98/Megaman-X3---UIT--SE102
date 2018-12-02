#pragma once
#include"../GameObjects/Entity.h"

class CollisionManager
{
	static CollisionManager* instance;
public:
	static CollisionManager* getInstance();

	//RECT getBroadphaseBox(Box& boxM);
	RECT getBroadphaseRect(Entity* object, float deltaTime);
	RECT getCollisionRect(RECT rectM, RECT rectS);
	bool AABBCheck(RECT& rectM, RECT& rectS);
	float sweptAABB(Entity* M, Entity* S, Entity::SideCollisions& side, float deltaTime);
	void checkCollision(Entity* M, Entity* S,float deltaTime);
	
	Entity::SideCollisions getSideCollision(Entity* M, Entity* S);
	void preventMove(Entity* M, Entity* S);

	CollisionManager();
	~CollisionManager();
};

