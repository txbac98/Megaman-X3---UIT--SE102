﻿#include "PlayerState.h"


PlayerState::PlayerState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
}

PlayerState::PlayerState()
{

}

PlayerState::~PlayerState()
{
}

void PlayerState::Update(float dt)
{

}


void PlayerState::OnCollision(Entity *object, Entity::SideCollisions side) {
	
}
//void PlayerState::SetPositionWhenCollision(Entity *other, Entity::SideCollisions side) {
//	
//}