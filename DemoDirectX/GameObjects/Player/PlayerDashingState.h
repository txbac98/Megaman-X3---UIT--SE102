#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerDashingState : public PlayerState
{
public:
	PlayerDashingState(PlayerData *playerData);
	~PlayerDashingState();

	void Update(float dt);
	void HandleKeyboard();
	void OnCollision(Entity * other, Entity::SideCollisions side);
	virtual StateName GetState();
	float timeDashting, time;
protected:
}; 
