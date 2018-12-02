#include "Player.h"
#include "PlayerRunningAndShootState.h"



PlayerRunningAndShootState::PlayerRunningAndShootState(PlayerData * playerData)
{
	this->mPlayerData = playerData;
	acceleratorX = 25.0f;
	//this->mPlayerData->player->isKeyAttack = false;
}

PlayerRunningAndShootState::~PlayerRunningAndShootState()
{
}

void PlayerRunningAndShootState::Update(float dt)
{
	if (this->mPlayerData->player->EndCurrentAnimation()) {
		//if (!this->mPlayerData->player->isDownKeyAttack)
			this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		//else this->mPlayerData->player->StartCurrentAnimation();
	}	
	else HandleKeyboard();
}

void PlayerRunningAndShootState::HandleKeyboard()
{

	if (KEY->keyDassPress) {
		if ((this->mPlayerData->player->allowMoveLeft && this->mPlayerData->player->mCurrentReverse)
			|| (this->mPlayerData->player->allowMoveRight && !this->mPlayerData->player->mCurrentReverse))
			this->mPlayerData->player->SetState(new PlayerDashingState(this->mPlayerData));
		return;
	}
	if (KEY->keyRight && mPlayerData->player->allowMoveRight)
	{
		mPlayerData->player->SetReverse(false);

		//di chuyen sang phai
		if (this->mPlayerData->player->GetVx() < PlayerDefine::MAX_RUNNING_SPEED)
		{
			this->mPlayerData->player->AddVx(acceleratorX);

			if (this->mPlayerData->player->GetVx() >= PlayerDefine::MAX_RUNNING_SPEED)
			{
				this->mPlayerData->player->SetVx(PlayerDefine::MAX_RUNNING_SPEED);
			}
		}	
	}
	else if (KEY->keyLeft && mPlayerData->player->allowMoveLeft)
	{
		mPlayerData->player->SetReverse(true);
		//di chuyen sang trai
		if (this->mPlayerData->player->GetVx() > -PlayerDefine::MAX_RUNNING_SPEED)
		{
			this->mPlayerData->player->AddVx(-acceleratorX);

			if (this->mPlayerData->player->GetVx() < -PlayerDefine::MAX_RUNNING_SPEED)
			{
				this->mPlayerData->player->SetVx(-PlayerDefine::MAX_RUNNING_SPEED);
			}
		}
	}
	else
	{
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
}

void PlayerRunningAndShootState::OnCollision(Entity * object, Entity::SideCollisions side)
{
	switch (side)
	{
	case Entity::SideCollisions::Left: //case Entity::SideCollisions::BottomLeft:
		//va cham phia ben trai player
		if (this->mPlayerData->player->getMoveDirection() == Player::MoveToLeft)	//Kiểm tra đang di chuyển qua trái
		{
			//day Player ra phia ben phai de cho player khong bi xuyen qua object
			//this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData, false, true));
		}
		break;
	case Entity::SideCollisions::Right: //case Entity::SideCollisions::BottomRight:
		//va cham phia ben phai player
		if (this->mPlayerData->player->getMoveDirection() == Player::MoveToRight)
		{
			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData, true, false));
			//this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);				
		}
		break;
	case Entity::SideCollisions::BottomRight:
		this->mPlayerData->player->allowMoveRight = true;
		break;
	case Entity::SideCollisions::BottomLeft:
		this->mPlayerData->player->allowMoveLeft = true;
		break;
	case Entity::SideCollisions::Top:
		break;

	case Entity::SideCollisions::Bottom:
		break;
	default:
		break;
	}

}

PlayerState::StateName PlayerRunningAndShootState::GetState()
{
	return PlayerState::RunningAndShoot;
}
