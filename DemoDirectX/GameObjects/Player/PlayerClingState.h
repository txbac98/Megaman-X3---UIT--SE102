#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerClingState : public PlayerState
{
public:
	PlayerClingState(PlayerData *playerData);
	~PlayerClingState();

	void Update(float dt);

	void HandleKeyboard();

	void OnCollision(Entity *other, Entity::SideCollisions side);
	virtual StateName GetState();

protected:
	float acceleratorY;
	float acceleratorX;
	bool noPressed;
};

