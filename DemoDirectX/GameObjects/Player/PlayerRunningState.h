#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerRunningState : public PlayerState
{
public:
    PlayerRunningState(PlayerData *playerData);
    ~PlayerRunningState();
	void Update(float dt);
	void HandleKeyboard();
	void OnCollision(Entity *object, Entity::SideCollisions side);
    virtual StateName GetState();

protected:
	bool isShooting;
    float acceleratorX;
};

