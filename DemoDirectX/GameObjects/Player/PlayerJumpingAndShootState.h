#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerJumpingAndShootState : public PlayerState
{
public:
	PlayerJumpingAndShootState(PlayerData *playerData);
	~PlayerJumpingAndShootState();
	void Update(float dt);
	void HandleKeyboard();
	void OnCollision(Entity *object, Entity::SideCollisions side);
	virtual StateName GetState();
protected:

protected:
	float acceleratorY;
	float acceleratorX;
	bool noPressed;
};