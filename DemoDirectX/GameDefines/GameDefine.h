#pragma once
namespace PlayerDefine
{
    const float MAX_JUMP_VELOCITY = 320.0f; //van toc roi lon nhat
    const float MIN_JUMP_VELOCITY = -320.0f; //van toc nhay thap nhat
	const float JUMP_ACCELERATOR_X = 150.0f;
	const float JUMP_ACCELERATOR_Y = 15.0f;
    const float MAX_RUNNING_SPEED = 100.0f; //toc do chay nhanh nhat cua player
	const float RUNNING_ACCELERATOR = 50.0f; //gia tốc chạy
	const float DASHING_SPEED = 150;
	const float DASHING_TIME = 0.5f;
    const float BOTTOM_RANGE_FALLING = 0.4f; // do dai va cham voi bottom neu nhu va cham bottom nho hon thi player se bi roi xuong
	const float TIME_IMMORTAL = 1.0f;	//Thời gian miễn kháng sau khi bị tấn công
	//Effect
	const float TIME_EFFECT2 = 1.0f;
	const float TIME_EFFECT1 = 0.3f;
	
}
namespace NotorDefine {
	const float BULLET_SPEED_X_1 = 70.0f;
	const float BULLET_SPEED_Y_1 = 100.0f;
	const float BULLET_SPEED_X_2 = 10.0f;
	const float BULLET_SPEED_Y_2 = 150.0f;
	const float BULLET_ACCELERATOR_Y = 3.0f;
	const float ACCELERATOR_Y = 10.0f;
	const float JUMP_SPEED_Y = 200;
	const float JUMP_SPEED_X = 50;
}
namespace HelitDefine {
	const float ACCELERATOR_Y = 10.0f;
	const float BULLET_SPEED_X = 100.0f;
}

namespace HeadDefine {
	const float BULLET_SPEED_X = 70.0f;
	const float BULLET_SPEED_Y = 100.0f;
	const float BULLET_ACCELERATOR_Y = 50.0f;
}

namespace BulletDefine {
	const float PLAYER_BULLET_SPEED = 300.0f;
}
namespace SceneDefine {
	const int WIDTH = 256;	//map64 :: 150
	const int HEIGHT = 256;
}
