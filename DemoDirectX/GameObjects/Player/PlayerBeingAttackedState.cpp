#include "PlayerBeingAttackedState.h"
#include "Player.h"

PlayerBeingAttackedState::PlayerBeingAttackedState(PlayerData * playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->beingAttacked = true;
	this->mPlayerData->player->vx = 0;
}

PlayerBeingAttackedState::~PlayerBeingAttackedState()
{
	
}

void PlayerBeingAttackedState::Update(float dt)
{
	if (this->mPlayerData->player->mAnimationBeingAttacked->mEndAnimate) {
		this->mPlayerData->player->beingAttacked = false;
		this->mPlayerData->player->isImmortal = true;
		this->mPlayerData->player->SetState(new PlayerStandingState(mPlayerData));
		return;
	}
}

void PlayerBeingAttackedState::HandleKeyboard()
{
}

void PlayerBeingAttackedState::OnCollision(Entity * other, Entity::SideCollisions side)
{
}

PlayerState::StateName PlayerBeingAttackedState::GetState()
{
	return PlayerState::BeingAttacked;
}
