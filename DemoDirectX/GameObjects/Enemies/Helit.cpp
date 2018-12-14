#include "Helit.h"
#include "../../GameComponents/ViewPort.h"

Helit::~Helit()
{
}

Helit::Helit(float posX, float posY)
{
	mAnimationStand = new Animation("Resources/Enemies/Helit.png", "Resources/Enemies/HelitStanding.txt", 0.1f, false);
	mAnimationMove = new Animation("Resources/Enemies/Helit.png", "Resources/Enemies/HelitMoving.txt", 0.02f, false);
	mAnimationDie = new Animation("Resources/Effect/Explosions.bmp", "Resources/Effect/RedExplosion.txt", 0.1f, false);
	/*mAnimationDie = new Animation("Resources/Effect/Explosions.bmp", "Resources/Effect/RedExplosion.txt", 0.1f, false);
	mAnimationStand = new Animation("Resources/Enemies/Helit.png", "Resources/Enemies/NotorStand.txt", 0.2f, false);
	mAnimationShoot1 = new Animation("Resources/Enemies/Helit.png", "Resources/Enemies/NotorShoot1.txt", 0.3f, false);
	mAnimationShoot2 = new Animation("Resources/Enemies/Helit.png", "Resources/Enemies/NotorShoot2.txt", 0.3f, false);
	mAnimationUp1 = new Animation("Resources/Enemies/Helit.png", "Resources/Enemies/NotorUp1.txt", 0.2f, false);
	mAnimationUp2 = new Animation("Resources/Enemies/Helit.png", "Resources/Enemies/NotorUp2.txt", 0.2f, false);*/
	mAnimationStand->Start();
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
	moveDown = true;
	shooted = false;
	direction = -1;
	iBullet = 0;
	//Bullet
	mListBullet = new EnemyBullet[2];
}

void Helit::Update(float dt)
{
	if (isAlive) {
		//kiểm tra va chạm viên đạn player
	/*	for (int i = 0; i < sizeof(mPlayer->mListBullet); i++) {
			CollisionManager::getInstance()->checkCollision(&mPlayer->mListBullet[i], this, dt / 1000);
		}*/

		//if (hp <= 0) {
		//	Die();
		//	return;
		//}
		//if (abs(posX - mPlayer->posX) < 100 && mAnimation != mAnimationStand)	// khoảng cách dưới 100
		//{
		//	type = 1;	//xiên
		//	if (abs(posX - mPlayer->posX) < 20) type = 2;	//thẳng đứng
		//	if (mPlayer->posX < posX)	//bên trái
		//	{
		//		isFaceLeft = true;
		//		direction = -1;
		//	}
		//	else
		//	{		//bên phải
		//		isFaceLeft = false;
		//		direction = 1;
		//	}
		//}
		//Hết Stand ->Quay súng -> Shoot (3 vien) ->Trả súng -> Jump
		if (mAnimation->mEndAnimate) {
			if (mAnimation == mAnimationStand) {
				mAnimationMove->Start();
				mAnimation = mAnimationMove;
			}
			else if (mAnimation == mAnimationMove) {
				mAnimationMove->Start();
				mAnimation = mAnimationMove;
			}
		}
		//	else if (posY >= mPlayer->posY) {
		//		moveDown = false;
		//		mAnimationStand->Start();
		//		mAnimation = mAnimationStand;
		//		//
		//		//
		//		//
		//	}
		//}
	/*	else if (mAnimation == mAnimationStand && !moveDown) {
			mAnimationMove->Start();
			this->AddPositionY(+8);
			mAnimation = mAnimationMove;
		}*/
		//mListBullet[iBullet].Spawn(3, this->posX, this->posY, direction*HelitDefine::BULLET_SPEED_X, 0);
		if (posY >= mPlayer->posY) {
			moveDown = false;
			
			shooted = true;
		}
		else {
			moveDown = true;
		}
		if (moveDown)
			this->SetVy(20);
		else
			this->SetVy(-20);


		//if (mListBullet)
		//{
		//	//Kiểm tra va chạm
		//	std::vector<Entity*> mListEntity;

		//	for (int i = 0; i < sizeof(mListBullet); i++) {

		//		mListBullet[i].Update(dt);

		//		CollisionManager::getInstance()->checkCollision(mPlayer, &mListBullet[i], dt / 1000);

		//		ViewPort::getInstance()->GetMapObject(mListEntity, &mListBullet[i]);
		//		for (int j = 0; j < mListEntity.size(); j++)
		//			if (mListEntity[j] != this)
		//				CollisionManager::getInstance()->checkCollision(mListEntity[j], &mListBullet[i], dt / 1000);
		//	}
		//}

		mAnimation->Update(dt);
		if (abs(posX - mPlayer->posX) < 200) {
			Entity::Update(dt);
		}
		//this->AddPositionY(-8);
		   //}
		   //else if (mAnimation == mAnimationShoot)  //bullet 2 duoc spawn
		   //{
		   //	if (iBullet > 2) {
		   //		vy = -NotorDefine::JUMP_SPEED_Y;
		   //		mAnimationStand->Start();
		   //		mAnimation = mAnimationStand;
		   //		iBullet = 0;
		   //		this->AddPositionY(8);
		   //	}
		   //	else {
		   //		if (type == 1)
		   //			mListBullet[iBullet].Spawn(this->posX, this->posY, direction*NotorDefine::BULLET_SPEED_X_1, -NotorDefine::BULLET_SPEED_Y_1);
		   //		else if (type == 2)
		   //			mListBullet[iBullet].Spawn(this->posX, this->posY, direction*NotorDefine::BULLET_SPEED_X_2, -NotorDefine::BULLET_SPEED_Y_2);
		   //		mAnimationShoot->Start();
		   //		mAnimation = mAnimationShoot;
		   //		iBullet++;
		   //	}
	}

	/*if (explosion) explosion->Update(dt);



	if (mListBullet)
	{
		for (int i = 0; i < sizeof(mListBullet); i++)
			mListBullet[i].Update(dt);
	}
*/
}

//void Helit::Moving(float dt)
//{
//	//if (moveDown) {
//	//	vy += HelitDefine::ACCELERATOR_Y;
//	//	//moveDown = false;
//	//}
//	//else
//	//	vy -= HelitDefine::ACCELERATOR_Y;
//	/*vy += HelitDefine::ACCELERATOR_Y;
//	mAnimationStand->Update(dt);*/
//	//if (allowMoveLeft && isFaceLeft) {
//	//	vy = -NotorDefine::JUMP_SPEED_X;
//	//	allowMoveRight = true;
//	//}
//
//	//if (allowMoveRight && !isFaceLeft) {
//	//	vy = NotorDefine::JUMP_SPEED_X;
//	//	allowMoveLeft = true;
//	//}
//}

void Helit::OnCollision(Entity * other, SideCollisions side)
{
	if (isAlive) {
		if (other->Tag == EntityTypes::MegaBullet) {
			hp--;
			other->Tag = EntityTypes::None;
			return;
		}
		//if (other->Tag == EntityTypes::Wall) {
		//	vx = 0;
		//	if (side == SideCollisions::BottomLeft
		//		|| side == SideCollisions::Left
		//		|| side == SideCollisions::TopLeft) {
		//		//allowMoveLeft = false;
		//	}
		//	if (side == SideCollisions::BottomRight
		//		|| side == SideCollisions::Right
		//		|| side == SideCollisions::TopRight) {
		//		//allowMoveRight = false;
		//	}
		//	if (side == SideCollisions::Bottom) {
		//		vy = 0;
		//		if (mAnimation == mAnimationStand) {
		//			mAnimationStand->Start();
		//			mAnimation = mAnimationStand;
		//		}
		//	}
		//}
	}
}

void Helit::Draw(D3DXVECTOR2 transform)
{
	/*if (mListBullet)
	{
		for (int i = 0; i < sizeof(mListBullet); i++)
			mListBullet[i].Draw(transform);
	}*/
	if (isAlive) {
		mAnimation->SetPosition(this->GetPosition());
		mAnimation->FlipVertical(!isFaceLeft);
		mAnimation->Draw(transform);
	}
	if (explosion)
		explosion->Draw(transform);
}

void Helit::Die()
{
	if (isAlive) {
		mAnimation = mAnimationDie;
		this->Tag = EntityTypes::None;
		explosion = new RedExplosion(posX, posY);
		isAlive = false;
	}
}
