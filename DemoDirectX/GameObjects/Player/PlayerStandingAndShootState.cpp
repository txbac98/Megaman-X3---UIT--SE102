#include "Player.h"
#include "../../GameDefines/GameDefine.h"
#include "PlayerStandingAndShootState.h"

PlayerStandingAndShootState::PlayerStandingAndShootState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	//this->mPlayerData->player->isCollisionBottom = false;
}

PlayerStandingAndShootState::~PlayerStandingAndShootState()
{
}
void PlayerStandingAndShootState::Update(float dt)
{
	if (this->mPlayerData->player->EndCurrentAnimation()) {
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
	HandleKeyboard();
}
void PlayerStandingAndShootState::HandleKeyboard()
{
	if (KEY->keyLeft  && this->mPlayerData->player->allowMoveLeft)
	{
		if (this->mPlayerData->player->isDownKeyAttack)
			this->mPlayerData->player->SetState(new PlayerRunningAndShootState(this->mPlayerData));
		else this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		return;
	}
	if (KEY->keyRight && this->mPlayerData->player->allowMoveRight)
	{
		if (this->mPlayerData->player->isDownKeyAttack)
			this->mPlayerData->player->SetState(new PlayerRunningAndShootState(this->mPlayerData));
		else this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		return;
	}
	
}
void PlayerStandingAndShootState::OnCollision(Entity * other, Entity::SideCollisions side)
{
}
PlayerStandingAndShootState::StateName PlayerStandingAndShootState::GetState()
{
	return PlayerStandingAndShootState::StandingAndShoot;
}