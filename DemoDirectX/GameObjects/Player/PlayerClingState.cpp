#include "PlayerClingState.h"

PlayerClingState::PlayerClingState(PlayerData * playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVy(50);
	this->mPlayerData->player->SetVx(0);
}

PlayerClingState::~PlayerClingState()
{
}

void PlayerClingState::Update(float dt)
{
	
	//HandleKeyboard();
}

void PlayerClingState::HandleKeyboard()
{
	/*if (KEY->keyAttackPress) {
		this->mPlayerData->player->SetState(new PlayerClingAndShootState(mPlayerData));
		return;
	}*/
	if (KEY->keyJumpPress) {
		if (this->mPlayerData->player->mCurrentReverse)
			this->mPlayerData->player->AddPositionX(5);
		else
			this->mPlayerData->player->AddPositionX(-5);
		this->mPlayerData->player->SetState(new PlayerJumpingState(mPlayerData));
		return;
	}
	if (KEY->keyLeftUp && this->mPlayerData->player->mCurrentReverse) {	//Rơi xuống khi nhả phím Left, khi bám bên Left
		//this->mPlayerData->player->AddPositionX(5);
		this->mPlayerData->player->SetState(new PlayerFallingState(mPlayerData));
		return;
	}
	if (KEY->keyRightUp && !this->mPlayerData->player->mCurrentReverse) {
		//this->mPlayerData->player->AddPositionX(-5);
		this->mPlayerData->player->SetState(new PlayerFallingState(mPlayerData));
		return;
	}
	if (KEY->keyRight && this->mPlayerData->player->allowMoveRight)
	{
		if (this->mPlayerData->player->mCurrentReverse)
		{
			this->mPlayerData->player->SetState(new PlayerFallingState(mPlayerData));
			return;
		}		
	}
	if (KEY->keyLeft && this->mPlayerData->player->allowMoveLeft)
	{
		if (!this->mPlayerData->player->mCurrentReverse)
		{
			this->mPlayerData->player->SetState(new PlayerFallingState(mPlayerData));
			return;
		}
	}
}

void PlayerClingState::OnCollision(Entity * other, Entity::SideCollisions side)
{
	if (side == Entity::Bottom) {
		this->mPlayerData->player->SetState(new PlayerStandingState(mPlayerData));
		return;
	}
}
PlayerState::StateName PlayerClingState::GetState()
{
	return PlayerState::Cling;
}