#include "PlayerClingAndShootState.h"

PlayerClingAndShootState::PlayerClingAndShootState(PlayerData * playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVy(50);
	this->mPlayerData->player->SetVx(0);
}

PlayerClingAndShootState::~PlayerClingAndShootState()
{
}

void PlayerClingAndShootState::Update(float dt)
{
	if (this->mPlayerData->player->EndCurrentAnimation()) {
		this->mPlayerData->player->SetState(new PlayerClingState(this->mPlayerData));
		return;
	}
	//HandleKeyboard();
}

void PlayerClingAndShootState::HandleKeyboard()
{
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

void PlayerClingAndShootState::OnCollision(Entity * other, Entity::SideCollisions side)
{
}

PlayerState::StateName PlayerClingAndShootState::GetState()
{
	return PlayerState::ClingAndShoot;
}