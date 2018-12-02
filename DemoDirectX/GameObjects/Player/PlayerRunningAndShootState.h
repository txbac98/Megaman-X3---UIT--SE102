#pragma once
#include "PlayerState.h"

class PlayerRunningAndShootState :  public PlayerState
{
public:
	PlayerRunningAndShootState(PlayerData *playerData);
	~PlayerRunningAndShootState();
	void Update(float dt);
	void HandleKeyboard();
	void OnCollision(Entity *object, Entity::SideCollisions side);
	virtual StateName GetState();
protected:

	float acceleratorX;
};