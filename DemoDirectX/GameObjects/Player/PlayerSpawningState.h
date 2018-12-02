#pragma once
#include "PlayerState.h"


class PlayerSpawningState : public PlayerState
{
public:
	PlayerSpawningState(PlayerData *playerData);
	~PlayerSpawningState();

	void Update(float dt);
	void HandleKeyboard();
	//void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	void OnCollision(Entity * other, Entity::SideCollisions side);
	//void SetPositionWhenCollision(Entity *other, Entity::SideCollisions side);
	virtual StateName GetState();

protected:
};

