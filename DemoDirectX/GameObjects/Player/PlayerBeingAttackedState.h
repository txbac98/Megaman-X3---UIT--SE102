#pragma once
#include "PlayerState.h"


class PlayerBeingAttackedState : public PlayerState
{
public:
	PlayerBeingAttackedState(PlayerData *playerData);
	// Vì các frame animation kích thước không bằng nhau khi check collision
	//PlayerBeingAttackedState(PlayerData *playerData, bool allowLeft, bool allowRight);
	~PlayerBeingAttackedState();

	void Update(float dt);
	void HandleKeyboard();
	void OnCollision(Entity * other, Entity::SideCollisions side);
	virtual StateName GetState();

protected:

};

