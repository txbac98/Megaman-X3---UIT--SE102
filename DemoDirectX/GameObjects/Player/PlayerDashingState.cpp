#include "PlayerDashingState.h"

PlayerDashingState::PlayerDashingState(PlayerData * playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->AddPositionY(4.5);
	if (this->mPlayerData->player->mCurrentReverse)	//Face on the left
		this->mPlayerData->player->SetVx(-150);
	else this->mPlayerData->player->SetVx(150);
	time = 0;
	timeDashting = 0.5;
}

PlayerDashingState::~PlayerDashingState()
{
}

void PlayerDashingState::Update(float dt)
{
	HandleKeyboard();
	time += dt;
	/*if (this->mPlayerData->player->EndCurrentAnimation())
		this->mPlayerData->player->mCurrentAnimation->SetIndex(1);*/
	if (time>=timeDashting)
	 {
		this->mPlayerData->player->AddPositionY(-4.5);
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
	}
	
}

void PlayerDashingState::HandleKeyboard()
{
}

void PlayerDashingState::OnCollision(Entity * other, Entity::SideCollisions side)
{
	switch (side)
	{
	case Entity::Left:
		if (this->mPlayerData->player->mCurrentReverse) {
			this->mPlayerData->player->AddPositionY(-4.5);
			this->mPlayerData->player->AddPositionX(-3);
			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		}	
		break;
	case Entity::Right:
		if (!this->mPlayerData->player->mCurrentReverse) {
			this->mPlayerData->player->AddPositionY(-4.5);
			this->mPlayerData->player->AddPositionX(3);
			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		}
		break;
	case Entity::Top:
		break;
	case Entity::Bottom:
		break;
	case Entity::TopLeft:
		break;
	case Entity::TopRight:
		break;
	case Entity::BottomLeft:
		break;
	case Entity::BottomRight:
		break;
	case Entity::NotKnow:
		break;
	default:
		break;
	}
}

PlayerState::StateName PlayerDashingState::GetState()
{
	return PlayerState::Dashing;
}
