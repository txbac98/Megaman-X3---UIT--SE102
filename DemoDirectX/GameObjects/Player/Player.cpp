#include "Player.h"


Player::Player()
{
	mAnimationSpawning = new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/Spawning.txt", 0.07f, false);
    mAnimationJumping = new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/Jumping.txt",0.2f,false);
	mAnimationFalling = new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/Falling.txt", 0.2f, false);
    mAnimationRunning = new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/Running.txt", 0.05f, true);
	mAnimationStanding = new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/Standing.txt",0.1f, true);	//0.3
	mAnimationDashing = new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/Dashing.txt", 0.01f, false);
	mAnimationCling= new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/Cling.txt", 0.1f, false);
	mAnimationBeingAttacked = new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/BeingAttacked.txt", 0.1f, false);
	mAnimationStandingAndShoot = new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/StandingAndShoot.txt", 0.05f, false);
	mAnimationRunningAndShoot= new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/RunningAndShoot.txt", 0.05f, false);
	mAnimationJumpingAndShoot = new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/JumpingAndShoot.txt", 0.05f, false);
	mAnimationClingAndShoot = new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/ClingAndShoot.txt", 0.05f, false);

	//Effect
	mAnimationEffect1 = new Animation("Resources/Megaman/Effect.png", "Resources/Megaman/Effect1.txt", 0.005f, true);
	mAnimationEffect2 = new Animation("Resources/Megaman/Effect.png", "Resources/Megaman/Effect2.txt", 0.005f, true);
	mAnimationEffect1->Start();
	mAnimationEffect2->Start();

	//Khởi tạo mảng Bullet
	mListBullet = new PlayerBullet[5];
	
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
	this->Tag = Entity::EntityTypes::Player;

	timeDownAttackKey = 0;
}

Player::~Player()
{
}

void Player::Update(float dt)
{    
	
	HandleKeyboard(dt);

	CheckNoCollisionWithBottom();

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
	
	//Update animation Effect
	if (mCurrentEffectAnimation != NULL) {
		mCurrentEffectAnimation->Update(dt);
	}
	
	//Update animation Bullet
	RECT rectCamera = mCamera->GetBound();
	for (int i=0; i < sizeof(mListBullet); i++) {
		mListBullet[i].Update(dt,rectCamera);
	}

	this->width = mCurrentAnimation->GetWidth();
	this->height = mCurrentAnimation->GetHeight();

	mCurrentAnimation->Update(dt);

    if (this->mPlayerData->state)
    {
        this->mPlayerData->state->Update(dt);
    }
	
    Entity::Update(dt);	

	
}
void Player::CheckNoCollisionWithBottom() {
	//rơi xuống
	if (mCurrentState == PlayerState::Falling && mCurrentState == PlayerState::Jumping)
		return;
	if (objectBottom == NULL) return;

	RECT rectBottom, mRect;
	rectBottom = objectBottom->GetBound();
	mRect = this->GetBound();
		
	if (objectBottom->Tag == EntityTypes::Elevator) {
		if (rectBottom.top < mRect.bottom)
			this->AddPositionY(rectBottom.top - mRect.bottom );
	}
	//nằm trên, chưa ra rìa
	if (rectBottom.left<= mRect.left && rectBottom.right>=mRect.right)
		return;
	//Phía left
	if (this->posX < objectBottom->posX) {
		if ((mRect.right - rectBottom.left) < this->width*0.1) {
			this->SetState(new PlayerFallingState(this->mPlayerData));
		}
		return;
	}
	//Phía right
	if (this->posX > objectBottom->posX) {
		if ((rectBottom.right - mRect.left ) < this->width*0.1) {
			this->SetState(new PlayerFallingState(this->mPlayerData));
		}
		return;
	}
	
}
void Player::HandleKeyboard(float dt) {

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
		for (int i = 0; i < sizeof(mListBullet); i++) {
			if (mListBullet[i].wasBorn) continue;
			mListBullet[i].Spawn(isFaceLeft, typeBullet);		//Cho phép bullet được vẽ, kiểu bullet
			if (mCurrentReverse)
				mListBullet[i].SetPosition(this->posX-10,this->posY-1);
			else mListBullet[i].SetPosition(this->posX + 10, this->posY - 1);
			break;
		}
		isDownKeyAttack = false;
		timeDownAttackKey=0;
		mCurrentEffectAnimation = NULL;
		switch (this->getState())
		{
		case PlayerState::Standing:
			this->SetState(new PlayerStandingAndShootState(mPlayerData));
			break;
		case PlayerState::Running:
			this->SetState(new PlayerRunningAndShootState(mPlayerData));
			break;
		case PlayerState::Jumping:
			this->SetState(new PlayerJumpingAndShootState(mPlayerData));
			break;
		case PlayerState::Cling:
			this->SetState(new PlayerClingAndShootState(mPlayerData));
			break;
		default:
			break;
		}
	}

	//Jump
  	if (KEY->keyJumpPress)
	{
		//if (allowJump)
		{
			if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing)
			{
				this->SetState(new PlayerJumpingState(this->mPlayerData));
			}

			allowJump = false;
		}
	}
}




void Player::OnAABBCheck(Entity* other) {

}
void Player::OnCollision(Entity * other, Entity::SideCollisions side) {
	//Chung

	if (side == SideCollisions::Bottom || side == SideCollisions::BottomLeft || side == SideCollisions::BottomRight) {
		
		objectBottom = other;
	}
	if (side == SideCollisions::Left || side == SideCollisions::Right )
	{
		this->mPlayerData->player->SetVx(0);
	}
	if (side == SideCollisions::BottomLeft || side == SideCollisions::BottomRight) {
		if (!this->getState() == PlayerState::Dashing)
			this->mPlayerData->player->SetVx(0);
	}
	if (side== SideCollisions::Left) this->mPlayerData->player->allowMoveLeft = false;
	if (side == SideCollisions::Right) this->mPlayerData->player->allowMoveRight = false;
	//Riêng từng state
	this->mPlayerData->state->OnCollision(other, side);
	
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

	/*if (mCamera)
	{*/
		//vị trí nhân vật với camera
		D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
			GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);

		//Draw bullet
		for (int i = 0; i < sizeof(mListBullet); i++) {
			mListBullet[i].Draw(trans);
		}

		//Draw player
		mCurrentAnimation->Draw(trans);

		//Effect
		if (mCurrentEffectAnimation) {
			mCurrentEffectAnimation->SetPosition(this->GetPosition());
			mCurrentEffectAnimation->Draw(trans);
		}
			
	/*}
	else
	{
		mCurrentAnimation->DrawSprite();
	}*/
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