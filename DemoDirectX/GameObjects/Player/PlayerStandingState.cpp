#include "Player.h"
#include "../../GameDefines/GameDefine.h"

PlayerStandingState::PlayerStandingState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	this->mPlayerData->player->allowMoveLeft = true;
	this->mPlayerData->player->allowMoveRight = true;
	this->mPlayerData->player->beingAttacked = false;
}



PlayerStandingState::PlayerStandingState(PlayerData *playerData, bool allowLeft, bool allowRight)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	this->mPlayerData->player->allowMoveLeft = allowLeft;
	this->mPlayerData->player->allowMoveRight = allowRight;
	this->mPlayerData->player->beingAttacked = false;
}


PlayerStandingState::~PlayerStandingState()
{
}

void PlayerStandingState::Update(float dt)
{
	//HandleKeyboard();
}
void PlayerStandingState::HandleKeyboard() {
	if (KEY->keyLeft  && this->mPlayerData->player->allowMoveLeft)
	{
		this->mPlayerData->player->allowMoveRight = true;
		this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		return;
	}
	if (KEY->keyRight && this->mPlayerData->player->allowMoveRight) 
	{
		this->mPlayerData->player->allowMoveLeft = true;
		this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		return;
	}
	/*if (KEY->keyAttackPress) {
		this->mPlayerData->player->SetState(new PlayerStandingAndShootState(this->mPlayerData));
		return;
	}*/
	if (KEY->keyDassPress ) {
		if ((this->mPlayerData->player->allowMoveLeft && this->mPlayerData->player->mCurrentReverse)
			|| (this->mPlayerData->player->allowMoveRight && !this->mPlayerData->player->mCurrentReverse))
			this->mPlayerData->player->SetState(new PlayerDashingState(this->mPlayerData));
		return;
	}
}
void PlayerStandingState::OnCollision(Entity * other, Entity::SideCollisions side) {
	
}
PlayerState::StateName PlayerStandingState::GetState()
{
    return PlayerState::Standing;
}
