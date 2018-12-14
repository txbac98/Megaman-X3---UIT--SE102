#include "Notorbanger.h"
#include "../../GameComponents/ViewPort.h"

Notorbanger::~Notorbanger()
{
}

Notorbanger::Notorbanger(float posX, float posY)
{
	mAnimationJump = new Animation("Resources/Enemies/Notorbanger.png", "Resources/Enemies/NotorJump.txt", 0.01f, false);
	mAnimationDie= new Animation("Resources/Effect/Explosions.bmp", "Resources/Effect/RedExplosion.txt", 0.1f, false);
	mAnimationStand = new Animation("Resources/Enemies/Notorbanger.png", "Resources/Enemies/NotorStand.txt", 0.2f, false);
	mAnimationShoot1= new Animation("Resources/Enemies/Notorbanger.png", "Resources/Enemies/NotorShoot1.txt", 0.3f, false);
	mAnimationShoot2 = new Animation("Resources/Enemies/Notorbanger.png", "Resources/Enemies/NotorShoot2.txt", 0.3f, false);
	mAnimationUp1= new Animation("Resources/Enemies/Notorbanger.png", "Resources/Enemies/NotorUp1.txt", 0.2f, false);
	mAnimationUp2 = new Animation("Resources/Enemies/Notorbanger.png", "Resources/Enemies/NotorUp2.txt", 0.2f, false);
	//mAnimationStand->Start();
	mAnimation = mAnimationStand;

	this->SetPosition(posX, posY);
	this->SetWidth(mAnimation->GetWidth());
	this->SetHeight(mAnimation->GetHeight());
	this->Tag = Entity::EntityTypes::Enemy;
	isFaceLeft = true;
	mPlayer = ViewPort::getInstance()->mPlayer;
	mCamera = ViewPort::getInstance()->mCamera;
	//mGameMap = map;
	hp = 3;
	this->SetVy(10);
	isAlive = true;
	allowMoveLeft = true;
	allowMoveRight = true;
	direction = -1;
	iBullet = 0;
	//Bullet
	mListBullet = new NotorBullet[4];
}

void Notorbanger::Update(float dt)
{
	if (isAlive) {
		this->SetWidth(mAnimation->GetWidth());
		this->SetHeight(mAnimation->GetHeight());

		//kiểm tra va chạm viên đạn player
		for (int i = 0; i < sizeof(mPlayer->mListBullet); i++) {
			CollisionManager::getInstance()->checkCollision(&mPlayer->mListBullet[i], this, dt / 1000);
		}

		if (hp <= 0) {
			Die();
			return;
		}
		if (abs(posX - mPlayer->posX )< 120 && mAnimation != mAnimationJump)	// khoảng cách dưới 100
		{
			if (type == 0) {
				type = 1;	//xiên
				if (abs(posX - mPlayer->posX) < 40) type = 2;	//thẳng đứng
				if (mPlayer->posX < posX)	//bên trái
				{
					isFaceLeft = true;
					direction = -1;
				}
				else
				{		//bên phải
					isFaceLeft = false;
					direction = 1;
				}
			}	
		}
		
		//Hết Stand ->Quay súng -> Shoot (3 vien) ->Trả súng -> Jump
		if (mAnimation->mEndAnimate) {
			if (mAnimation == mAnimationStand) {
				//Kiểm tra type để quay súng
				if (type == 1) {
					mAnimationUp1->Start();
					mAnimation = mAnimationUp1;
					this->AddPositionY(-6);
				}
				else if (type == 2) {
					mAnimationUp2->Start();
					mAnimation = mAnimationUp2;
					this->AddPositionY(-6);
				}
				else {
					mAnimationStand->Start();
					mAnimation = mAnimationStand;
				}

			}
			else if (mAnimation == mAnimationUp1 || mAnimation == mAnimationUp2) {
				if (type == 1) {
					mAnimationShoot1->Start();
					mAnimation = mAnimationShoot1;
					mAnimationShoot = mAnimationShoot1;
				}
				else if (type == 2) {
					mAnimationShoot2->Start();
					mAnimation = mAnimationShoot2;
					mAnimationShoot = mAnimationShoot2;
				}
				//this->AddPositionY(-8);
			}
			else if (mAnimation == mAnimationShoot)  //bullet 2 duoc spawn
			{
				if (iBullet > 2) {
					vy = -NotorDefine::JUMP_SPEED_Y;
					mAnimationJump->Start();
					mAnimation = mAnimationJump;
					iBullet = 0;
					type = 0;
					this->AddPositionY(6);
				}
				else {
					if (type==1)
						mListBullet[iBullet].Spawn(this->posX, this->posY, direction*NotorDefine::BULLET_SPEED_X_1,-NotorDefine::BULLET_SPEED_Y_1);
					else if (type==2)
						mListBullet[iBullet].Spawn(this->posX, this->posY, direction*NotorDefine::BULLET_SPEED_X_2, -NotorDefine::BULLET_SPEED_Y_2);
					mAnimationShoot->Start();
					mAnimation = mAnimationShoot;
					iBullet++;
				}
			}
		}
		
	}	

	if (explosion) explosion->Update(dt);

	if (mAnimation == mAnimationJump) {
		Jumping(dt);
	}

	//Xử lý đạn
	if (mListBullet )
	{
		//Kiểm tra va chạm
		std::vector<Entity*> mListEntity;

		for (int i = 0; i < sizeof(mListBullet); i++) {

			mListBullet[i].Update(dt);

			CollisionManager::getInstance()->checkCollision(mPlayer, &mListBullet[i], dt/1000);

			ViewPort::getInstance()->GetMapObject(mListEntity, &mListBullet[i]);
			for (int j = 0; j < mListEntity.size(); j++)
				if (mListEntity[j]!=this)
					CollisionManager::getInstance()->checkCollision(mListEntity[j], &mListBullet[i], dt/1000);
		}

		
	}
	
	mAnimation->Update(dt);
	Entity::Update(dt);
}

void Notorbanger::Jumping(float dt)
{
	vy +=NotorDefine::ACCELERATOR_Y;
	if (allowMoveLeft && isFaceLeft) {
		vx = -NotorDefine::JUMP_SPEED_X;
		allowMoveRight = true;
	}
		
	if (allowMoveRight && !isFaceLeft) {
		vx = NotorDefine::JUMP_SPEED_X;
		allowMoveLeft = true;
	}	
}

void Notorbanger::OnCollision(Entity * other, SideCollisions side)
{
	if (isAlive) {
		if (other->Tag == EntityTypes::MegaBullet) {
			hp--;
			other->Tag = EntityTypes::None;
			return;
		}
		if (other->Tag == EntityTypes::Wall) {
			vx = 0;
			if (side == SideCollisions::BottomLeft
				|| side == SideCollisions::Left
				|| side == SideCollisions::TopLeft) {
				allowMoveLeft = false;
			}
			if (side == SideCollisions::BottomRight
				|| side == SideCollisions::Right
				|| side == SideCollisions::TopRight) {
				allowMoveRight = false;
			}
			if (side == SideCollisions::Bottom) {
				vy = 0;
				if (mAnimation == mAnimationJump) {
					mAnimationStand->Start();
					mAnimation = mAnimationStand;
				}
			}
		}
	}
}

void Notorbanger::Draw(D3DXVECTOR2 transform)
{
	if (mListBullet)
	{
		for (int i = 0; i < sizeof(mListBullet); i++)
			mListBullet[i].Draw(transform);
	}
	if (isAlive) {
		mAnimation->SetPosition(this->GetPosition());
		mAnimation->FlipVertical(!isFaceLeft);
		mAnimation->Draw(transform);
	}
	if (explosion)
		explosion->Draw(transform);
	
}

void Notorbanger::Die()
{
	if (isAlive) {
		mAnimation = mAnimationDie;
		this->Tag = EntityTypes::None;
		explosion = new RedExplosion(posX, posY);
		isAlive = false;
	}
}
