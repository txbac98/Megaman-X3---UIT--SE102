#pragma once
#include "PlayerState.h"


class PlayerStandAndShootState : public PlayerState
{
public:
	PlayerStandingState(PlayerData *playerData);
	~PlayerStandingState();

	void Update(float dt);
	void HandleKeyboard();
	//void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	void OnCollision(Entity * other, Entity::SideCollisions side);
	//void SetPositionWhenCollision(Entity *other, Entity::SideCollisions side);
	virtual StateName GetState();

protected:
};