 #include "PlayerJumpingState.h"
#include "../../GameDefines/GameDefine.h"
#include "../../KeyGame.h"

PlayerJumpingState::PlayerJumpingState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVy(PlayerDefine::MIN_JUMP_VELOCITY);
    acceleratorY = 15.0f;
    acceleratorX = 14.0f;
    noPressed = false;
	this->mPlayerData->player->allowMoveLeft = true;
	this->mPlayerData->player->allowMoveRight = true;
	this->mPlayerData->player->objectBottom = NULL;
	//this->mPlayerData->player->isCollisionBottom = false;
}


PlayerJumpingState::~PlayerJumpingState()
{

}

void PlayerJumpingState::Update(float dt)
{
    this->mPlayerData->player->AddVy(acceleratorY);   

    if (mPlayerData->player->GetVy() >= 0)
    {
        mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));

        return;
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
	//HandleKeyboard();
}

void PlayerJumpingState::HandleKeyboard()
{
	/*if (KEY->keyAttackPress) {
		mPlayerData->player->SetState(new PlayerJumpingAndShootState(this->mPlayerData));
		return;
	}*/
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

void PlayerJumpingState::OnCollision(Entity* object, Entity::SideCollisions side) {
	switch (side)
	{
	case Entity::Left: 
		if ( KEY->keyLeft)	//mặt xoay vào bên trái
			this->mPlayerData->player->SetState(new PlayerClingState(mPlayerData,object->GetBound().bottom));
		break;
	case Entity::BottomLeft:
		break;
	case Entity::Right:  
		if ( KEY->keyRight)	//mặt xoay vào bên phải
			this->mPlayerData->player->SetState(new PlayerClingState(mPlayerData,object->GetBound().bottom));
		break;
	case Entity::BottomRight:
		break;
	case Entity::Top:
		break;
	case Entity::Bottom:
		break;
	case Entity::TopLeft:
		break;
	case Entity::TopRight:
		break;
	case Entity::NotKnow:
		break;
	default:
		break;
	}
}

PlayerState::StateName PlayerJumpingState::GetState()
{
    return PlayerState::Jumping;
}
