#ifndef __COLLISION_BODY__
#define __COLLISION_BODY__

#include "GameObjects/Entity.h"
//#include "../Framework/IComponent.h"

//class CollisionEventArg : public EventArg
//{
//public:
//	CollisionEventArg(Entity* object)
//	{
//		_otherObject = object;
//		_sideCollision =  Entity::SideCollisions::NONE;
//	}
//
//	Entity* _otherObject;
//	 Entity::SideCollisions _sideCollision;
//private:
//
//};

//[event_source(native)]
class CollisionBody 
{
public:
	CollisionBody(Entity* target);
	CollisionBody(Entity* target, RECT bodyRect);

	~CollisionBody();

	void checkCollision(Entity* otherObject, float dt, bool updatePosition = true);

	bool checkCollision(Entity* otherObject,  Entity::SideCollisions& direction, float dt, bool updatePosition = true);

	bool isColliding(Entity* otherObject);

	void update(float dt);

	//__event void onCollisionBegin(CollisionEventArg* e);
	//__event void onCollisionEnd(CollisionEventArg* e);

	RECT getCollisionRect();

	void updateTargetPosition(Entity* otherObject,  Entity::SideCollisions direction, bool withVelocity, D3DXVECTOR2 move = D3DXVECTOR2(0, 0));

	float isCollide(Entity* otherObject,  Entity::SideCollisions& direction, float dt);
	bool isColliding(RECT myRect, RECT otherRect);
	bool isColliding(Entity* otherObject, float& moveX, float& moveY, float dt);

	RECT getSweptBroadphaseRect(Entity* object, float dt);	//r
	 Entity::SideCollisions getSide(Entity* otherObject);	//r

private:
	Entity* _target;
	RECT _collisionBodyRect;

	float _dxEntry, _dyEntry, _dxExit, _dyExit;
	float _txEntry, _tyEntry, _txExit, _tyExit;

	//map<Entity*, bool> _listColliding;

};

#endif // !__COLLISION_BODY__
