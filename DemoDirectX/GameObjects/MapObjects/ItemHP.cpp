#include "ItemHP.h"
#include "../../GameComponents/ViewPort.h"
ItemHP::~ItemHP()
{
}


ItemHP::ItemHP(float posX, float posY)
{
	//mSprite = new Sprite("Resources/MapObject/item.png");
	mItemHP = new Animation("Resources/MapObject/item.png", "Resources/MapObject/ItemHP.txt", 0.05f, false);
	this->SetPosition(posX, posY);
	this->SetWidth(mItemHP->GetWidth());
	this->SetHeight(mItemHP->GetHeight());
	mItemHP->SetPosition(posX, posY);
	isSpawn = true;
	isAlive = true;
	mPlayer = ViewPort::getInstance()->mPlayer;
	this->Tag = EntityTypes::ItemHP;
}

void ItemHP::Update(float dt)
{
	if (isAlive) {
		this->SetWidth(mItemHP->GetWidth());
		this->SetHeight(mItemHP->GetHeight());
		CollisionManager::getInstance()->checkCollision(mPlayer, this, dt);
		mItemHP->Update(dt);
		Entity::Update(dt);
	}

}

void ItemHP::OnCollision(Entity * other, SideCollisions side)
{
	if (other->Tag == EntityTypes::Megaman) {
		isAlive = false;
		this->Tag = EntityTypes::None;
		mPlayer->mHP->HP = 18;
	}
}

void ItemHP::Draw(D3DXVECTOR2 transform)
{
	if (isAlive)
	{
		mItemHP->SetPosition(posX, posY);
		mItemHP->Draw(D3DXVECTOR2(transform));
	}

}
