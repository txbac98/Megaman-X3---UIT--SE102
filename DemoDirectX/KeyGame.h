#pragma once
#include "Keyboard.h"
#include "Constant.h"

class KeyGame
{
private:
	Keyboard* key;

	static KeyGame* instance;
public:
	static KeyGame* getInstance();

	//Giữ phím, hoặc nhấn
	bool keyUp;
	bool keyDown;
	bool keyLeft;
	bool keyLeftUp;
	bool keyRight;
	bool keyRightUp;
	bool keyMove;
	bool keyStair;
	bool keyBeginStair;
	bool keyRangeAttack;
	bool keySitDownAttack;

	bool keyChangeScene;
	bool keyChangeScenePress, isKeyChangeSceneDownPrevious;

	bool keyAttack;
	bool keyAttackUp;
	bool keyAttackPress, isKeyAttackDownPrevious;

	bool keyJump;
	bool keyJumpPress, isKeyJumpDownPrevious;

	bool keyDash;
	bool keyDassPress, isKeyDashDownPrevious;


	void update();

	KeyGame();
	~KeyGame();
};

