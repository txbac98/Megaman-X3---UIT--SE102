#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerJumpingState : public PlayerState
{
public:
    PlayerJumpingState(PlayerData *playerData);
    ~PlayerJumpingState();

    void Update(float dt);

    void HandleKeyboard();

	void OnCollision(Entity *other, Entity::SideCollisions side);
    virtual StateName GetState();

protected:
    float acceleratorY;
    float acceleratorX;
    bool noPressed;
};

