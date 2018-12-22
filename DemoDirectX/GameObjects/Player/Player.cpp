#include "Player.h"
#include "../../GameComponents/ViewPort.h"
#include "../../GameComponents/Sound.h"

Player::Player()
{
	mHP = new PlayerHP(30,50);
	mAnimationSpawning = new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/Spawning.txt", 0.07f, false);
    mAnimationJumping = new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/Jumping.txt",0.2f,false);
	mAnimationFalling = new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/Falling.txt", 0.2f, false);
    mAnimationRunning = new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/Running.txt", 0.05f, true);
	mAnimationStanding = new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/Standing.txt",0.2f, true);	//0.3
	mAnimationDashing = new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/Dashing.txt", 0.01f, false);
	mAnimationCling= new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/Cling.txt", 0.1f, false);
	mAnimationBeingAttacked = new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/BeingAttacked.txt", 0.1f, false);
	mAnimationStandingAndShoot = new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/StandingAndShoot.txt", 0.05f, false);
	mAnimationRunningAndShoot= new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/RunningAndShoot.txt", 0.05f, false);
	mAnimationJumpingAndShoot = new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/JumpingAndShoot.txt", 0.05f, false);
	mAnimationClingAndShoot = new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/ClingAndShoot.txt", 0.05f, false);

	//Effect
	mAnimationEffect1 = new Animation("Resources/Megaman/MegaEffect/Effect.png", "Resources/Megaman/MegaEffect/Effect1.txt", 0.005f, true);
	mAnimationEffect2 = new Animation("Resources/Megaman/MegaEffect/Effect.png", "Resources/Megaman/MegaEffect/Effect2.txt", 0.005f, true);
	mAnimationEffect1->Start();
	mAnimationEffect2->Start();

	//Follow Boss
	mFollow = new Sprite("Resources/Megaman/MegaEffect/Follow.png");

	//Khởi tạo mảng Bullet
	mListBullet = new PlayerBullet[5];
	/*for (int i = 0; i < 5; i++) {
		mListBullet.push_back(new PlayerBullet());
	}*/

	//khởi tạo khói
	mListSmoke = new PlayerDashingSmoke[5];
	
    this->mPlayerData = new PlayerData();
    this->mPlayerData->player = this;
    this->vx = 0;
    this->vy = 0;
	mAnimationSpawning->Start();
	mCurrentAnimation = mAnimationSpawning;
    //this->SetState(new PlayerFallingState(this->mPlayerData));

    this->allowJump = true;
	this->allowMoveRight = true;
	this->allowMoveLeft = true;
	this->isCollisionBottom = false;
	this->isDownKeyAttack = false;
	this->isFaceLeft = false;
	this->isImmortal = false;
	this->turnDraw = false;
	this->isAlive = true;
	onFollow = false;
	noDownKey = false;
	//inSlopingWall = false;
	beingAttacked = false;
	dtImmortal = 0;
	this->Tag = Entity::EntityTypes::Megaman;

	timeDownAttackKey = 0;
}

Player::~Player()
{
}


void Player::Update(float dt)
{    
		//Miễn kháng
		if (isImmortal) {
			dtImmortal += dt;
			if (dtImmortal > PlayerDefine::TIME_IMMORTAL) {
				dtImmortal = 0;
				isImmortal = false;
			}
		}

		//Death
		if (mDeathEffect) {
			mDeathEffect->Update(dt);
		}

		//End animation spawn
		if (mAnimationSpawning->mEndAnimate) {
			this->SetState(new PlayerFallingState(this->mPlayerData));
			mAnimationSpawning->mEndAnimate = false;
		}
		else {
			if (this->getState() == PlayerState::Cling || this->getState() == PlayerState::ClingAndShoot)
				isFaceLeft = !mCurrentReverse;
			else
			{
				isFaceLeft = mCurrentReverse;
			}
		}
	
		//Update animation Bullet
		for (int i = 0; i < sizeof(mListBullet); i++) {
			mListBullet[i].Update(dt, mCamera->GetBound());
		}

		//Update list smoke
		for (int i = 0; i < sizeof(mListSmoke); i++) {
			mListSmoke[i].Update(dt);
		}

		if (isAlive) {
			
			//Update player
			this->width = mCurrentAnimation->GetWidth();
			this->height = mCurrentAnimation->GetHeight();

			

			//Kiểm tra va chạm player với object
			std::vector<Entity*> mListMapObject;
			ViewPort::getInstance()->GetMapObject(mListMapObject, this);
			for (size_t i = 0; i < mListMapObject.size(); i++)
			{
				//Entity::SideCollisions direction;	
				CollisionManager::getInstance()->checkCollision(this, mListMapObject[i], dt/1000);
			}

			//Update animation Effect
			if (mCurrentEffectAnimation != NULL) {
				mCurrentEffectAnimation->Update(dt);
			}

			if (this->mPlayerData->state)
			{
				this->mPlayerData->state->Update(dt);
			}

			mCurrentAnimation->Update(dt);

			HandleKeyboard(dt);

			CheckNoCollisionWithBottom();

			Entity::Update(dt);
		}
}
void Player::CheckNoCollisionWithBottom() {
	
	if (objectBottom == NULL) return;
	
	RECT rectBottom, mRect;
	rectBottom = objectBottom->GetBound();
	mRect = this->GetBound();

	

	//rơi xuống
	if (this->getState() == PlayerState::Falling && this->getState() == PlayerState::Jumping)
		return;

	if (objectBottom->Tag == EntityTypes::Elevator) {
		if (rectBottom.top < mRect.bottom && rectBottom.left<this->posX && rectBottom.right>this->posX)
		{
			this->AddPositionY(rectBottom.top - mRect.bottom);
			if (this->getState() == PlayerState::Falling) this->SetState(new PlayerStandingState(mPlayerData));
			return;
		}

	}

	if (objectBottom->Tag == EntityTypes::ConveyorRight) {
		if (mRect.right <= rectBottom.right)
		{
			this->AddPositionX(1);
			/*if (vx ==0  ) {
				if (allowMoveRight)
					vx = 5;
			}*/
			//else vx += 5;
			//this->AddPositionX(1);
		}
			
	}
	if (objectBottom->Tag == EntityTypes::ConveyorLeft) {
		if (mRect.left>= rectBottom.left)
			this->AddPositionX(-1);
			/*if (vx == 0) {
				vx = -5;
			}*/
	}

	
	
	//nằm trên, chưa ra rìa
	if (rectBottom.left<= mRect.left && rectBottom.right>=mRect.right)
		return;
	//Phía left
	if (this->posX < objectBottom->posX) {
		if ((mRect.right - rectBottom.left) < 0) {
			//this->AddPositionX(-1);
			this->SetState(new PlayerFallingState(this->mPlayerData));
		}
		return;
	}
	//Phía right
	if (this->posX > objectBottom->posX) {
		if ((rectBottom.right - mRect.left ) < 0) {
			//this->AddPositionX(1);
			this->SetState(new PlayerFallingState(this->mPlayerData));
		}
		return;
	}

	
	
	
	
}
void Player::Die()
{
	if (!mDeathEffect) {
		Sound::getInstance()->play("Die", false, 1);
		mHP->AddDame(mHP->HP);
		mDeathEffect = new PlayerDeathEffect(posX, posY);
		this->isAlive = false;
		return;
	}
}
void Player::HandleKeyboard(float dt) {

	if (!noDownKey) {
		if (this->getState() == PlayerState::BeingAttacked) {
			return;
		}
		//Effect when keep keyAttack
		if (KEY->keyAttack && !isDownKeyAttack) {
			timeDownAttackKey = 0;
			typeBullet = 0;
			isDownKeyAttack = true;
		}
		if (isDownKeyAttack) timeDownAttackKey += dt;
		if (timeDownAttackKey > PlayerDefine::TIME_EFFECT2) {
			mCurrentEffectAnimation = mAnimationEffect2;
			typeBullet = 2;
		}
		else if (timeDownAttackKey > PlayerDefine::TIME_EFFECT1) {
			mCurrentEffectAnimation = mAnimationEffect1;
			typeBullet = 1;
		}
		//Spawn bullet
		if (KEY->keyAttackUp && isDownKeyAttack) {
			
			isDownKeyAttack = false;
			timeDownAttackKey = 0;
			mCurrentEffectAnimation = NULL;
			switch (this->getState())
			{
			case PlayerState::Standing:
				this->SetState(new PlayerStandingAndShootState(mPlayerData));
				break;
			case PlayerState::Running:
				this->SetState(new PlayerRunningAndShootState(mPlayerData));
				break;
			case PlayerState::Jumping:	case PlayerState::Falling:
				this->SetState(new PlayerJumpingAndShootState(mPlayerData));
				break;
			case PlayerState::Cling:
				this->SetState(new PlayerClingAndShootState(mPlayerData));
				break;
			case PlayerState::Dashing:	//Dashing không cho bắn
				return;
			default:
				break;
			}
			for (int i = 0; i < sizeof(mListBullet); i++) {
				if (mListBullet[i].wasBorn) continue;
				if (typeBullet==0) 
					Sound::getInstance()->play("PlayerShoot", false, 1);
				else 
					Sound::getInstance()->play("PlayerShoot12", false, 1);
				mListBullet[i].Spawn(isFaceLeft, typeBullet);		//Cho phép bullet được vẽ, kiểu bullet
				if (mCurrentReverse)
					mListBullet[i].SetPosition(this->posX - 10, this->posY - 1);
				else mListBullet[i].SetPosition(this->posX + 10, this->posY - 1);
				break;
			}
		}

		//Jump
		if (KEY->keyJumpPress)
		{		
			if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing)
			{
				Sound::getInstance()->play("Jump", false, 1);
				this->SetState(new PlayerJumpingState(this->mPlayerData));
				return;
			}
		}
		//Gọi handlekey từng state
		if (this->mPlayerData->state)
		{
			this->mPlayerData->state->HandleKeyboard();
		}
	}
	else {
		if (vy != 0) {
			vx = 0;
			this->SetState(new PlayerFallingState(mPlayerData));
		}	
		else {
			if (this->getState()!=PlayerState::Standing)
				this->SetState(new PlayerStandingState(mPlayerData));
		}
		return;
	}
}




void Player::OnAABBCheck(Entity* other) {

}
void Player::OnCollision(Entity * other, Entity::SideCollisions side) {
	//Chung
	if (other->Tag == EntityTypes::None) return;
	

	//Enemies
	if (other->Tag == EntityTypes::Notorbanger 
		|| other->Tag== EntityTypes::HeadgunnerLeft || other->Tag==HeadgunnerRight || other->Tag == EntityTypes::EnemiesBullet
		||other->Tag==EntityTypes::Genjibo
		|| other->Tag==EntityTypes::Spine
		||other->Tag==EntityTypes::Box
		||other->Tag==EntityTypes::HornetBoss
		||other->Tag==EntityTypes::HornetChild
		|| other->Tag == EntityTypes::Stone5
		|| other->Tag == EntityTypes::Stone3
		|| other->Tag==EntityTypes::Helit) {
		if (isImmortal || beingAttacked) {
			return;
		}
		
		if (other->isAlive)
		{
			{
				if (other->Tag == EntityTypes::Spine) mHP->AddDame(1);
				else mHP->AddDame(other->dame);
				if (mHP->HP <= 0) {
					if (this->isAlive) {
						Die();
					}
				}
				if (!beingAttacked) {
					beingAttacked = true;
					this->SetState(new PlayerBeingAttackedState(mPlayerData));
					return;
				}
				
			}	
		}
			
	}
	
	//Tường xiên
	//if (other->Tag == SlopingWall) {
	//	if (this->getState()!=PlayerState::Falling) {	//không rơi 
	//		inSlopingWall = true;
	//		if (vx > 0) {
	//			this->AddPositionY(-0.5);
	//		}
	//		else if (vx < 0) {
	//			this->AddPositionY(0.5);
	//		}
	//	}
	//	else inSlopingWall = false;
	//}

	if (other->Tag == EntityTypes::Wall || other->Tag== EntityTypes::Elevator 
		|| other->Tag==EntityTypes::DoorObject || other->Tag==EntityTypes::ConveyorRight
		|| other->Tag== EntityTypes::ConveyorLeft
		|| other->Tag==EntityTypes::DebrisCarryarm) {
		if (other->Tag != EntityTypes::Elevator)objectBottom = NULL;
		if (side == SideCollisions::Top) {
			this->SetVy(PlayerDefine::JUMP_ACCELERATOR_Y);
			this->SetState(new PlayerFallingState(mPlayerData));
			return;
		}
		if (side == SideCollisions::Bottom ) {
			//|| side == SideCollisions::BottomLeft || side == SideCollisions::BottomRight
			objectBottom = other;
			this->AddPositionY(other->GetBound().top - this->GetBound().bottom);
			//inSlopingWall = false;
			//vy = 0;
		}
		if (side == SideCollisions::Left || side == SideCollisions::BottomLeft) {
			if (this->isFaceLeft ) {
				this->mPlayerData->player->allowMoveLeft = false;
				this->mPlayerData->player->SetVx(0);
			}
		}
		if (side == SideCollisions::Right || side == SideCollisions::BottomRight) {
			if (!this->isFaceLeft ) {
				this->mPlayerData->player->SetVx(0);
				this->mPlayerData->player->allowMoveRight = false;
			}
		}
		//Riêng từng state
		if (this->mPlayerData->state)
			this->mPlayerData->state->OnCollision(other, side);
		return;
	}	
	
	
}


void Player::changeAnimation(PlayerState::StateName state)
{
	if (mCurrentAnimation != NULL)
		mCurrentAnimation->Stop();
	switch (state)
	{
	case PlayerState::Spawning:
		break;
	case PlayerState::Standing:
		mCurrentAnimation = mAnimationStanding;
		break;
	case PlayerState::Running:
		mCurrentAnimation = mAnimationRunning;
		break;
	case PlayerState::Falling:
		mCurrentAnimation = mAnimationFalling;
		break;
	case PlayerState::Jumping:
		mCurrentAnimation = mAnimationJumping;
		break;
	case PlayerState::Dashing:
		mCurrentAnimation = mAnimationDashing;
		break;
	case PlayerState::Cling:
		mCurrentAnimation = mAnimationCling;
		break;
	case PlayerState::StandingAndShoot:
		mCurrentAnimation = mAnimationStandingAndShoot;
		break;
	case PlayerState::RunningAndShoot:
		mCurrentAnimation = mAnimationRunningAndShoot;
		break;
	case PlayerState::JumpingAndShoot:
		mCurrentAnimation = mAnimationJumpingAndShoot;
		break;
	case PlayerState::ClingAndShoot:
		mCurrentAnimation = mAnimationClingAndShoot;
		break;
	case PlayerState::BeingAttacked:
		mCurrentAnimation = mAnimationBeingAttacked;
		break;
	case PlayerState::Die:
		mCurrentAnimation = mAnimationDie;
		break;
	default:
		break;
	}
    this->width = mCurrentAnimation->GetWidth();
    this->height = mCurrentAnimation->GetHeight();
	mCurrentAnimation->Start();
}

void Player::StartCurrentAnimation()
{
	mCurrentAnimation->Start();
}


Player::MoveDirection Player::getMoveDirection()
{
    if (this->vx > 0)
    {
        return MoveDirection::MoveToRight;
    }
    else if (this->vx < 0)
    {
        return MoveDirection::MoveToLeft;
    }

    return MoveDirection::None;
}


void Player::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}

void Player::SetCamera(Camera *camera)
{
	this->mCamera = camera;
}

void Player::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
		mCurrentAnimation->FlipVertical(mCurrentReverse);
		mCurrentAnimation->SetPosition(this->GetPosition());

		if (mCamera)
		{
			//vị trí nhân vật với camera, int để không bị giật ảnh
			D3DXVECTOR2 trans = D3DXVECTOR2(int(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x),
				int(GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y)); // mCamera->GetPosition().y

			//mCurrentAnimation->SetPosition(posX+trans.x, posY+trans.y);

			
			//Draw bullet
			for (int i = 0; i < sizeof(mListBullet); i++) {
				mListBullet[i].Draw(trans);
			}

			//Draw smoke
			for (int i = 0; i < sizeof(mListSmoke); i++) {
				mListSmoke[i].Draw(trans);
			}

			if (isAlive) {
				//Draw player
				if (isImmortal) {
					if (turnDraw) {
						mCurrentAnimation->Draw(trans);
						turnDraw = false;
					}
					else turnDraw = true;
				}
				else mCurrentAnimation->Draw(trans);
				//Effect
				if (mCurrentEffectAnimation) {
					mCurrentEffectAnimation->SetPosition(this->GetPosition());
					mCurrentEffectAnimation->Draw(trans);
				}
			}
			
			//vẽ chêt
			if (mDeathEffect) {
				mDeathEffect->Draw(trans);
			}
			if (onFollow) {
				mFollow->SetPosition(this->GetPosition());
				mFollow->Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), trans);
			}

			//vẽ thanh máu
			if (mHP) {
				mHP->Draw();
			}

			//Máu boss
			if (hornetHP) {
				hornetHP->Draw();
			}

			

			
		}
		else
		{
			mCurrentAnimation->Draw();
		}
}


void Player::SetState(PlayerState *newState)
{
	delete this->mPlayerData->state;

	this->mPlayerData->state = newState;

	this->changeAnimation(newState->GetState());

	mCurrentState = newState->GetState();
}

RECT Player::GetBound()
{
	RECT rect;
	rect.left = this->posX - mCurrentAnimation->GetWidth() / 2;
	rect.right = rect.left + mCurrentAnimation->GetWidth();
	rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
	rect.bottom = rect.top + mCurrentAnimation->GetHeight();

	return rect;
}
bool Player::EndCurrentAnimation()
{
	return this->mCurrentAnimation->mEndAnimate;
}
PlayerState::StateName Player::getState()
{
    return mCurrentState;
}