#pragma once
namespace PlayerDefine
{
    const float MAX_JUMP_VELOCITY = 300.0f; //van toc roi lon nhat
    const float MIN_JUMP_VELOCITY = -300.0f; //van toc nhay thap nhat
	const float JUMP_ACCELERATOR_X = 14.0f;
	const float JUMP_ACCELERATOR_Y = 15.0f;
    const float MAX_RUNNING_SPEED = 50.0f; //toc do chay nhanh nhat cua player
	const float RUNNING_ACCELERATOR = 18.0f; //gia tốc chạy
	const float DASHING_SPEED = 150;
	const float DASHING_TIME = 0.5f;
    const float BOTTOM_RANGE_FALLING = 0.4f; // do dai va cham voi bottom neu nhu va cham bottom nho hon thi player se bi roi xuong

	//Effect
	const float TIME_EFFECT2 = 1.0f;
	const float TIME_EFFECT1 = 0.3f;
	
}
namespace BulletDefine {
	const float PLAYER_BULLET_SPEED = 200.0f;
}
namespace SceneDefine {
	const int WIDTH = 200;	//map64 :: 150
	const int HEIGHT = 200;
}
