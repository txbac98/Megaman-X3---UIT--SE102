#include "Hornet.h"
#include "../../GameComponents/ViewPort.h"

Hornet::~Hornet()
{
}

Hornet::Hornet(float posX, float posY)
{
	mAnimationFly = new Animation("Resources/Boss/Hornet.png", "Resources/Boss/HornetFly.txt", 0.02f, true);
	mAnimationStand = new Animation("Resources/Boss/Hornet.png", "Resources/Boss/HornetStand.txt", 0.05f, false);
	mAnimationPrepare= new Animation("Resources/Boss/Hornet.png", "Resources/Boss/HornetPrepare.txt", 0.05f, false);
	mAnimationAttack = new Animation("Resources/Boss/Hornet.png", "Resources/Boss/HornetAttack.txt", 0.05f, false);
	mAnimationSpawnChild = new Animation("Resources/Boss/Hornet.png", "Resources/Boss/HornetSpawnChild.txt", 0.05f, false);
	mAnimationDie = new Animation("Resources/Boss/Hornet.png", "Resources/Boss/HornetDie.txt", 0.1f, false);
	
	mAnimation = mAnimationStand;
	this->SetPosition(posX, posY);
	mAnimation->SetPosition(posX, posY);
	this->SetWidth(30);	//người ở giữa
	this->SetHeight(60);	//người ở giữa
	isFaceRight = false;
	isAlive = true;
	isSpawn = true;
	mPlayer = ViewPort::getInstance()->mPlayer;
	mCamera = ViewPort::getInstance()->mCamera;

	rectMove = mCamera->GetBound();
	rectMove.left += 50;
	rectMove.right -= 50;
	rectMove.top += 50;
	rectMove.bottom -= 120;
	dame = 1;
	toAttack = true;
	midRectY = rectMove.top + (rectMove.bottom - rectMove.top) / 2;

	mPlayer->hornetHP = new HornetHP(225, 60);
	mListChild.push_back(new ChildHornet());
	mListChild.push_back(new ChildHornet());
	mListChild.push_back(new ChildHornet());
	mListChild.push_back(new ChildHornet());
	mListChild.push_back(new ChildHornet());

	this->Tag = EntityTypes::HornetBoss;
}

void Hornet::Update(float dt)
{
	
	mAnimation->Update(dt);
	Entity::Update(dt);	

	if (mPlayer->hornetHP->HP <= 0) {
		if (mAnimation != mAnimationDie) {
			mAnimationDie->Start();
			mAnimation = mAnimationDie;
			vy=200;
		}			
	}
	else if (mPlayer->hornetHP->HP > 30) {
		typeAttack = 1;
	}
	else if (mPlayer->hornetHP->HP > 15) {
		typeAttack = 2;
	}
	else {
		typeAttack = 3;
	}
	if (mAnimation == mAnimationAttack) {	//Lao tới nv
		/*float dtx, dty;
		dtx = abs((posMegaX -posX) / (posMegaY - posY));
		dty = abs((posMegaY - posY) / (posMegaX-posX));*/
		if (int(posX) > posMegaX) {
			this->AddPositionX(-1);
		}
		else if (int(posX) < posMegaX) {
			this->AddPositionX(1);
		}
		if (int(posY) > posMegaY) {
			this->AddPositionY(-1);
		}
		else if (int(posY) < posMegaY) {
			this->AddPositionY(1);
		}
		if (int(posY) == posMegaY && int(posX)==posMegaX) {
			mAnimationFly->Start();
			mAnimation = mAnimationFly;
			vy = -HornetDefine::SPEED_Y;
		}
	}
	if (mAnimation->mEndAnimate) {	//Fly->stand->attack->fly
		if (mAnimation == mAnimationStand) {
			if (typeAttack == 1) {
				//Spawn child
				SpawnChild1();
				
			}
			else if (typeAttack == 2) {
				
				//Chuẩn bị xuống
				if (toAttack) {
					toAttack = false;
					mAnimationPrepare->Start();
					mAnimation = mAnimationPrepare;
				}
				else {
					toAttack = true;
					SpawnChild1();
				}
				
			}
			else if (typeAttack == 3) {
				//Spawn child and follow
					SpawnFollow();		
			}
		}
		else if (mAnimation == mAnimationSpawnChild) {

			vy = HornetDefine::SPEED_Y;
			if (posX > (mCamera->GetPosition().x)) {
				vx = -HornetDefine::SPEED_X;
			}
			else vx = HornetDefine::SPEED_X;
			mAnimationFly->Start();
			mAnimation = mAnimationFly;
		}
		else if (mAnimation == mAnimationPrepare) {	//Kết thúc chuẩn bị: Prepare->Attack
				posMegaX = mPlayer->posX;
				posMegaY = mPlayer->posX;
				mAnimationAttack->Start();
				mAnimation = mAnimationAttack;			
		}
		else if (mAnimation == mAnimationDie) {
			isAlive = false;
		}
	}

	//Đi hình số 8
	if (mAnimation == mAnimationFly) {
		if (posY > rectMove.bottom) {
			this->SetPosition(posX, rectMove.bottom);
			vy = -HornetDefine::SPEED_Y;
		}
		if (posY < rectMove.top) {
			//Stand
			this->SetPosition(posX, rectMove.top);	
			mAnimationStand->Start();
			mAnimation = mAnimationStand;
			vy = 0;
			vx = 0;
		}
		if (posX<rectMove.left || posX>rectMove.right) {
			if (posX < rectMove.left) this->SetPosition(rectMove.left,posY);
			if (posX > rectMove.right) this->SetPosition(rectMove.right, posY);
			vy = -HornetDefine::SPEED_Y;
			vx = 0;			
		}
	}
	
	

	//Kiểm tra va chạm với nhân vật
	if (mPlayer) {
		//kiểm tra va chạm viên đạn player
		for (int i = 0; i < sizeof(mPlayer->mListBullet); i++) {
			CollisionManager::getInstance()->checkCollision(&mPlayer->mListBullet[i], this, dt);
		}
		CollisionManager::getInstance()->checkCollision(mPlayer, this, dt);

		//Xoay mặt hướng nhân vật
		if (mPlayer->posX >= posX) {
			isFaceRight = true;			
			direction = 1;
		}
		else {
			isFaceRight = false;
			direction = -1;
		}
	}

	//kiểm tra va chạm  object với map
	std::vector<Entity*> mListMapObject;
	ViewPort::getInstance()->GetMapObject(mListMapObject, this);
	for (size_t j = 0; j < mListMapObject.size(); j++) {
		CollisionManager::getInstance()->checkCollision(this, mListMapObject[j], dt);
	}
	//Update child
	for (int i = 0; i < mListChild.size(); i++) {
		mListChild[i]->Update(dt);
	}

	//Follow
	if (mAnimationFollow) {
		int xFollow, yFollow, xPlayer, yPlayer;
		xFollow = int(mAnimationFollow->GetPosition().x);
		yFollow = int(mAnimationFollow->GetPosition().y);
		xPlayer = int(mPlayer->posX);
		yPlayer = int(mPlayer->posY);
		if (xFollow < xPlayer) xFollow++;
		else if (xFollow > xPlayer) xFollow--;
		if (yFollow < yPlayer) yFollow++;
		else if (yFollow > yPlayer) yFollow--;
			
		mAnimationFollow->SetPosition(xFollow, yFollow);
		mAnimationFollow->Update(dt);
		if (xFollow == xPlayer && yFollow == yPlayer) {
			mPlayer->onFollow=true;
			mAnimationFollow = NULL;
		}
	}
	if (mChildFollow) {
		if (!mChildFollow->isAlive)	mPlayer->onFollow = false;
		if (mPlayer->onFollow) {
			if (int(mChildFollow->posX) < int(mPlayer->posX)) {
				mChildFollow->isFaceRight = false;
				mChildFollow->AddPositionX(1);
			}
			else if (int(mChildFollow->posX) > int(mPlayer->posX)) { 
				mChildFollow->isFaceRight = true;
				mChildFollow->AddPositionX(-1); 
			}

			//Chạy tới player
			if (int(mChildFollow->posY) < int(mPlayer->posY)) {
				mChildFollow->AddPositionY(1);
			}
			else if (int(mChildFollow->posY) > int(mPlayer->posY)) mChildFollow->AddPositionY(-1);
		}
		mChildFollow->Update(dt);
	}
}

void Hornet::OnCollision(Entity * other, SideCollisions side)
{
	 
	if (other->Tag == EntityTypes::MegaBullet) {
		mPlayer->hornetHP->AddDame(other->dame);
		other->Tag = EntityTypes::None;
	}
	if (other->Tag == Wall) {
		//if (side == SideCollisions::Bottom) {
		
		if (mAnimation == mAnimationAttack) {
				mAnimationFly->Start();
				mAnimation = mAnimationFly;
				vy = -HornetDefine::SPEED_Y;
		}
		if (mAnimation == mAnimationDie && side == SideCollisions::Bottom)
		 {
				vy = 0;
				vx = 0;
		}

	}
	
	
}

void Hornet::Draw(D3DXVECTOR2 transform)
{
	
	
	mAnimation->SetPosition(posX, posY);
	mAnimation->FlipVertical(isFaceRight);
	mAnimation->Draw(transform);

	for (int i = 0; i < mListChild.size(); i++) {
		mListChild[i]->Draw(transform);
	}

	if (mAnimationFollow) {
		mAnimationFollow->Draw(transform);
	}
	
	if (mChildFollow) {
		mChildFollow->Draw(transform);
	}
}

void Hornet::SpawnChild1()
{
	for (int i = 0; i < mListChild.size(); i++) {
		if (mListChild[i]->isAlive) {
			mAnimationStand->Start();
			mAnimation = mAnimationStand;
			return;
		}
	}
	for (int i = 0; i < mListChild.size(); i++) {
		if (!mListChild[i]->isAlive) {
			mListChild[i] = new ChildHornet(1, posX, posY, direction*30, -10 +i*7);
		}
	}
	mAnimationSpawnChild->Start();
	mAnimation = mAnimationSpawnChild;
}

void Hornet::SpawnFollow()
{
	if (toAttack) {
		if (!mChildFollow)
			mChildFollow = new ChildHornet(2, posX, posY, direction * 30, -20);
		if (!mPlayer->onFollow) {
			if (!mChildFollow->isAlive)	mChildFollow = new ChildHornet(2, posX, posY, direction * 30, -20);
			mAnimationFollow = new Animation("Resources/Enemies/Follow.png", "Resources/Enemies/Follow.txt", 0.1f, true);
			mAnimationFollow->SetPosition(posX, posY);
		}
		mAnimationSpawnChild->Start();
		mAnimation = mAnimationSpawnChild;
	}
	else
	{
		if (!mChildFollow)
			mChildFollow = new ChildHornet(2, posX, posY, direction * 30, -20);
		SpawnChild1();
	}
	toAttack = !toAttack;
	
	//SpawnChild1();
}
