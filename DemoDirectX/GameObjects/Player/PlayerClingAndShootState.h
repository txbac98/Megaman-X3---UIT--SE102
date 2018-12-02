#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerClingAndShootState : public PlayerState
{
public:
	PlayerClingAndShootState(PlayerData *playerData);
	~PlayerClingAndShootState();

	void Update(float dt);

	void HandleKeyboard();

	void OnCollision(Entity *other, Entity::SideCollisions side);
	virtual StateName GetState();

protected:
	float acceleratorY;
	float acceleratorX;
	bool noPressed;
};

