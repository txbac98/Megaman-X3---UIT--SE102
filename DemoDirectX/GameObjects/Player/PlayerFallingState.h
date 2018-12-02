#pragma once
#include "PlayerState.h"


class PlayerFallingState : public PlayerState
{
public:
    PlayerFallingState(PlayerData *playerData);
    ~PlayerFallingState();

    void Update(float dt);

	void HandleKeyboard();

	void OnCollision(Entity * other, Entity::SideCollisions side);
    virtual StateName GetState();

protected:
    float acceleratorY;
    float acceleratorX;

    //neu nhu van toc ban dau = khong thi se khong cho giam toc do
    bool allowMoveX;

    bool isLeftOrRightKeyPressed;

};

