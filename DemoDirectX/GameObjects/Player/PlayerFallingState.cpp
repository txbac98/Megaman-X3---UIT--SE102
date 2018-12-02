#include "PlayerFallingState.h"
#include "Player.h"
#include "../../GameDefines/GameDefine.h"
#include "../../KeyGame.h"

PlayerFallingState::PlayerFallingState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
	
    acceleratorY =15.0f;
    acceleratorX = 8.0f;

	//vận tốc x
    if (this->mPlayerData->player->GetVx() == 0)
    {
        allowMoveX = false;
    }
    else
    {
        allowMoveX = true;
    }
	mPlayerData->player->allowMoveRight = true;
	mPlayerData->player->allowMoveLeft = true;
}


PlayerFallingState::~PlayerFallingState()
{
}

void PlayerFallingState::Update(float dt)
{
	//vận tốc rơi xuống
    this->mPlayerData->player->AddVy(acceleratorY);

    if (mPlayerData->player->GetVy() > PlayerDefine::MAX_JUMP_VELOCITY)
    {
        mPlayerData->player->SetVy(PlayerDefine::MAX_JUMP_VELOCITY);
    }
	HandleKeyboard();
}

void PlayerFallingState::HandleKeyboard()
{
	if (KEY->keyAttackPress) {
		mPlayerData->player->SetState(new PlayerJumpingAndShootState(this->mPlayerData));
		return;
	}
    if (KEY->keyRight && this->mPlayerData->player->allowMoveRight)
    {
        mPlayerData->player->SetReverse(false);

        isLeftOrRightKeyPressed = true;
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
    else if (KEY->keyLeft && this->mPlayerData->player->allowMoveLeft)
    {
        mPlayerData->player->SetReverse(true);

        isLeftOrRightKeyPressed = true;
        //di chuyen sang trai
        if (this->mPlayerData->player->GetVx() > -PlayerDefine::MAX_RUNNING_SPEED)
        {
            this->mPlayerData->player->AddVx(-acceleratorX);

            if (this->mPlayerData->player->GetVx() <= -PlayerDefine::MAX_RUNNING_SPEED)
            {
                this->mPlayerData->player->SetVx(-PlayerDefine::MAX_RUNNING_SPEED);
            }
        }
    }
    else
    {
        isLeftOrRightKeyPressed = false;    
    }
}


void PlayerFallingState::OnCollision(Entity * other, Entity::SideCollisions side) {
	
	switch (side)
	{
	case Entity::NotKnow:
		break;
	case Entity::Left: 
		if ( KEY->keyLeft)	//mặt xoay vào bên trái
			this->mPlayerData->player->SetState(new PlayerClingState(mPlayerData));
		break;
	case Entity::BottomLeft:
		break;
	case Entity::Right:
		if ( KEY->keyRight)	//mặt xoay vào bên phải
			this->mPlayerData->player->SetState(new PlayerClingState(mPlayerData));
		break;
	case Entity::BottomRight:
		break;
	case Entity::Top:
		break;
	case Entity::Bottom:	
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));

		break;
	default:
		break;
	}
}

PlayerState::StateName PlayerFallingState::GetState()
{
    return PlayerState::Falling;
}
