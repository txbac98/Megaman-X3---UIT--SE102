#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "../../GameComponents/Animation.h"
#include "../../GameComponents/GameGlobal.h"
#include "../../GameComponents/Camera.h"
#include "PlayerData.h"
#include "PlayerState.h"
#include "PlayerRunningState.h"
#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerDashingState.h"
#include "PlayerClingState.h"
#include "PlayerClingAndShootState.h"
#include "PlayerStandingAndShootState.h"
#include "PlayerRunningAndShootState.h"
#include "PlayerJumpingAndShootState.h"
#include "PlayerBeingAttackedState.h"
#include "../../KeyGame.h"
#include "Bullet/PlayerBullet.h"
#include "../Effect/PlayerDashingSmoke.h"
#include "HP/PlayerHP.h"
#include "PlayerDeathEffect.h"

class Player : public Entity
{
public:
    Player();
    ~Player();
    enum MoveDirection
    {
        MoveToLeft, //chay tu phai sang trai
        MoveToRight, //chay tu trai sang phai
        None //dung im
    };

    void SetCamera(Camera *camera);

    void Update(float dt);

    void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));


	//void Draw();
    void SetState(PlayerState *newState);
	
	void OnCollision(Entity * other, SideCollisions side);
	
	
	//Va chạm ở frame kế tiếp
	void OnAABBCheck(Entity * other);

    void CheckNoCollisionWithBottom();

    MoveDirection getMoveDirection();

    RECT GetBound();     
	bool EndCurrentAnimation();
    PlayerState::StateName Player::getState();

    //xu ly input
    //gom 256 key tuong ung true = dang dc nhan, false = khong dc nhan
    void HandleKeyboard(float dt);

    //true thi se lat nguoc anh theo truc y
    void SetReverse(bool flag);
	//true: bên trái, false: bên phải
    bool allowMoveLeft,isCollisionBottom;
    bool allowMoveRight;
	bool isDownKeyAttack;
	bool isImmortal;	//vừa mới tấn công xong
	bool beingAttacked;
	float dtImmortal;	//đếm time immortal
	bool turnDraw;		//Chớp khi miễn kháng
	int typeBullet;
	Animation   *mCurrentAnimation;
	Animation	*mCurrentEffectAnimation;

	PlayerBullet *mListBullet ;
	//vector<PlayerBullet*> mListBullet;
	PlayerDashingSmoke *mListSmoke;

	PlayerDeathEffect *mDeathEffect;

	PlayerHP *mHP;
	
//protected:
	Animation   *mAnimationSpawning,
		*mAnimationStanding,
		*mAnimationRunning,
		*mAnimationJumping,
		*mAnimationFalling,
		*mAnimationDashing,
		*mAnimationCling,
		*mAnimationDie,
		*mAnimationEffect1,
		*mAnimationEffect2,
		*mAnimationClingAndShoot,
		*mAnimationBeingAttacked,
		*mAnimationStandingAndShoot,
		*mAnimationRunningAndShoot,
		*mAnimationJumpingAndShoot;


    Camera      *mCamera;

    PlayerData *mPlayerData;

	Entity *objectBottom; //Wall bottom

    void changeAnimation(PlayerState::StateName state);
	void StartCurrentAnimation();

    PlayerState::StateName mCurrentState;

    //chi cho phep jump khi nhan nhim space, muon nhay lai phai tha phim space roi nhan lai
	bool allowJump;
	//true: bên trái, false: bên phải
	bool mCurrentReverse;

	//thời gian nhấn nút bắn
	float timeDownAttackKey;
	
};

