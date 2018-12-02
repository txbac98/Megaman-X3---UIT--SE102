#include "PlayerSpawningState.h"

PlayerSpawningState::PlayerSpawningState(PlayerData * playerData)
{
}

PlayerSpawningState::~PlayerSpawningState()
{
}

void PlayerSpawningState::Update(float dt)
{
}

void PlayerSpawningState::HandleKeyboard()
{
}

void PlayerSpawningState::OnCollision(Entity * other, Entity::SideCollisions side)
{
}

PlayerState::StateName PlayerSpawningState::GetState()
{
	return PlayerState::Spawning;
}
