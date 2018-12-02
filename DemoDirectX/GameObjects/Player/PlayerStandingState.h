#pragma once
#include "PlayerState.h"


class PlayerStandingState : public PlayerState 
{
public:
    PlayerStandingState(PlayerData *playerData);
	// Vì các frame animation kích thước không bằng nhau khi check collision
	PlayerStandingState(PlayerData *playerData, bool allowLeft, bool allowRight);
    ~PlayerStandingState();

    void Update(float dt);
	void HandleKeyboard();
	void OnCollision(Entity * other, Entity::SideCollisions side);
    virtual StateName GetState();

protected:

};

