#include "PlayerJumpingAndShootState.h"

PlayerJumpingAndShootState::PlayerJumpingAndShootState(PlayerData * playerData)
{

	this->mPlayerData = playerData;
	//this->mPlayerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	acceleratorY = 15.0f;
	acceleratorX = 14.0f;
	noPressed = false;
	this->mPlayerData->player->allowMoveLeft = true;
	this->mPlayerData->player->allowMoveRight = true;
}

PlayerJumpingAndShootState::~PlayerJumpingAndShootState()
{
}

void PlayerJumpingAndShootState::Update(float dt)
{
	
		this->mPlayerData->player->AddVy(acceleratorY);

		//Lặp lại animation khi bấm phím bắn
		if (this->mPlayerData->player->EndCurrentAnimation()) {
			//if (this->mPlayerData->player->isDownKeyAttack) {
			//	this->mPlayerData->player->StartCurrentAnimation();
			//}
			//else
			//{
				if (mPlayerData->player->GetVy() >= 0) {
					this->mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));
					return;
				}
		}

		if (noPressed)
		{
			if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
			{
				//player dang di chuyen sang ben trai      
				if (mPlayerData->player->GetVx() < 0)
				{
					this->mPlayerData->player->AddVx(acceleratorX);

					if (mPlayerData->player->GetVx() > 0)
						this->mPlayerData->player->SetVx(0);
				}
			}
			else if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
			{
				//player dang di chuyen sang phai   
				if (mPlayerData->player->GetVx() > 0)
				{
					this->mPlayerData->player->AddVx(-acceleratorX);

					if (mPlayerData->player->GetVx() < 0)
						this->mPlayerData->player->SetVx(0);
				}
			}
		}
		
		HandleKeyboard();
}

void PlayerJumpingAndShootState::HandleKeyboard()
{
	if (KEY->keyRight && this->mPlayerData->player->allowMoveRight)
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

		noPressed = false;
	}
	else if (KEY->keyLeft && this->mPlayerData->player->allowMoveLeft)
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

		noPressed = false;
	}
	else
	{
		noPressed = true;
	}
}

void PlayerJumpingAndShootState::OnCollision(Entity * object, Entity::SideCollisions side)
{
	if (side == Entity::BottomLeft || side == Entity::BottomRight || side == Entity::Bottom) {
		this->mPlayerData->player->SetState(new PlayerStandingState(mPlayerData));
		return;
	}
}
PlayerState::StateName PlayerJumpingAndShootState::GetState()
{
	return PlayerState::JumpingAndShoot;
}