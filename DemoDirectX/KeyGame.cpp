#include "KeyGame.h"

KeyGame* KeyGame::instance = 0;
KeyGame*  KeyGame::getInstance()
{
	if (instance == 0)
		instance = new KeyGame();

	return instance;
}

void KeyGame::update()
{
	keyAttack = key->IsKeyDown(DIK_Z);
	keyAttackUp = key->IsKeyUp(DIK_Z);
	keyAttackPress = keyAttack && !isKeyAttackDownPrevious;
	isKeyAttackDownPrevious = keyAttack;

	keyJump = key->IsKeyDown(DIK_X);
	keyJumpPress = keyJump && !isKeyJumpDownPrevious;
	isKeyJumpDownPrevious = keyJump;

	keyDash = key->IsKeyDown(DIK_C);
	keyDassPress = keyDash && !isKeyDashDownPrevious;
	isKeyDashDownPrevious = keyDash;

	/*keyChangeScene = key->IsKeyDown(DIK_RETURN);
	keyChangeScenePress = keyChangeScene && !isKeyChangeSceneDownPrevious;
	isKeyChangeSceneDownPrevious = keyChangeScene;*/

	keyUp = key->IsKeyDown(DIK_UP) ;
	keyDown = key->IsKeyDown(DIK_DOWN) ;
	keyLeft = key->IsKeyDown(DIK_LEFT) ;
	keyLeftUp = key->IsKeyUp(DIK_LEFT);
	keyRightUp = key->IsKeyUp(DIK_RIGHT);
	keyRight = key->IsKeyDown(DIK_RIGHT);
	keyMove = keyLeft || keyRight;
	keyStair = keyUp || keyDown || keyLeft || keyRight;
	keyBeginStair = keyUp;
	keyRangeAttack = keyUp && keyAttackPress;
	keySitDownAttack = keyDown && keyAttackPress;
}

KeyGame::KeyGame()
{
	key = Keyboard::getInstance();
	isKeyJumpDownPrevious = false;
	isKeyAttackDownPrevious = false;
	isKeyChangeSceneDownPrevious = false;
	isKeyDashDownPrevious = false;
}

KeyGame::~KeyGame()
{
}
