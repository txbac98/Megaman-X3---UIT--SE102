#pragma once
#include "PlayerData.h"
#include "../Entity.h"
#include <map>


class PlayerState
{
public:
    enum StateName
    {
		Spawning,
        Standing,
        Running,
        Falling,
        Jumping,
		Dashing,
		Cling,
		ClingAndShoot,
		StandingAndShoot,
		RunningAndShoot,
		JumpingAndShoot,
		BeingAttacked,
        Die
    };

    ~PlayerState();

    virtual void Update(float dt);

	virtual void HandleKeyboard();

    //side va cham voi player
    

	virtual void OnCollision(Entity *other, Entity::SideCollisions side);

	//virtual void SetPositionWhenCollision(Entity* other, Entity::SideCollisions side);

    virtual StateName GetState() = 0;
	

protected:
    PlayerState(PlayerData *playerData);
    PlayerState();

    PlayerData *mPlayerData;
};

