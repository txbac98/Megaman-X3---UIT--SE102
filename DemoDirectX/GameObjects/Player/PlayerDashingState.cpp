#include "PlayerDashingState.h"
#include "../../GameComponents/Sound.h"

PlayerDashingState::PlayerDashingState(PlayerData * playerData)
{
	this->mPlayerData = playerData;
	//this->mPlayerData->player->AddPositionY(4.5);
	if (this->mPlayerData->player->mCurrentReverse)	//Face on the left
		this->mPlayerData->player->SetVx(-PlayerDefine::DASHING_SPEED);
	else this->mPlayerData->player->SetVx(PlayerDefine::DASHING_SPEED);
	dtTimeDashing = 0;
	dtTimeSmoke = 0;
	timeSmoke = 0.1;
	timeDashting = PlayerDefine::DASHING_TIME;
	Sound::getInstance()->play("Dass", false, 1);
}

PlayerDashingState::~PlayerDashingState()
{
}

void PlayerDashingState::Update(float dt)
{
	//HandleKeyboard();
	dtTimeDashing += dt;
	dtTimeSmoke += dt;
	
	if (dtTimeDashing>=timeDashting)
	 {
		//this->mPlayerData->player->AddPositionY(-4.5);
		Sound::getInstance()->stop("Dass");
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
	//Spawn smoke
	if (dtTimeSmoke >= timeSmoke) {
		for (int i = 0; i < sizeof(this->mPlayerData->player->mListSmoke); i++) {
			if (this->mPlayerData->player->mListSmoke[i].wasBorn) continue;
			this->mPlayerData->player->mListSmoke[i].Spawn(this->mPlayerData->player->posX, this->mPlayerData->player->posY + 4);
			break;
		}
		dtTimeSmoke = 0;
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
			//this->mPlayerData->player->AddPositionY(-4.5);
			this->mPlayerData->player->AddPositionX(-3);
			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		}	
		break;
	case Entity::Right:
		if (!this->mPlayerData->player->mCurrentReverse) {
			//this->mPlayerData->player->AddPositionY(-4.5);
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
