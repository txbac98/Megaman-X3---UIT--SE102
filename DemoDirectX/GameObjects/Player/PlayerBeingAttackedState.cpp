#include "PlayerBeingAttackedState.h"
#include "Player.h"

PlayerBeingAttackedState::PlayerBeingAttackedState(PlayerData * playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->vx = 0;
	//if (this->mPlayerData->player->vy<0)
	this->mPlayerData->player->vy = 50;
}

PlayerBeingAttackedState::~PlayerBeingAttackedState()
{
	
}

void PlayerBeingAttackedState::Update(float dt)
{
	if (this->mPlayerData->player->mAnimationBeingAttacked->mEndAnimate) {
		this->mPlayerData->player->isImmortal = true;
		this->mPlayerData->player->beingAttacked = false;
		this->mPlayerData->player->SetState(new PlayerFallingState(mPlayerData));
		return;
	}
}

void PlayerBeingAttackedState::HandleKeyboard()
{
}

void PlayerBeingAttackedState::OnCollision(Entity * other, Entity::SideCollisions side)
{
	if (other->Tag == Entity::EntityTypes::Wall || Entity::EntityTypes::Elevator) {
		if (side == Entity::SideCollisions::Bottom) {
			this->mPlayerData->player->vy = 0;
		}
	}
}

PlayerState::StateName PlayerBeingAttackedState::GetState()
{
	return PlayerState::BeingAttacked;
}
