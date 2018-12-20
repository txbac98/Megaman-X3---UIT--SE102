#include "Game.h"
#include "GameGlobal.h"
#include "../GameControllers/SceneManager.h"
#include "../Scenes/DemoScene.h"
#include "../Scenes/MenuScene.h"
#include "Sound.h"

Game::Game(int fps)
{
	mFPS = fps;

	//Load âm thanh
	Sound::getInstance()->loadSound("Resources/Sounds/Background.wav", "Background");
	Sound::getInstance()->loadSound("Resources/Sounds/Explosion.wav", "Explosion");
	Sound::getInstance()->loadSound("Resources/Sounds/Jump.wav", "PlayerShoot");
	Sound::getInstance()->loadSound("Resources/Sounds/PlayerShoot.wav", "PlayerShoot12");
	Sound::getInstance()->loadSound("Resources/Sounds/Jump.wav", "Jump");
	Sound::getInstance()->loadSound("Resources/Sounds/Die.wav", "Die");

	SceneManager::GetInstance()->ReplaceScene(new MenuScene());
	
	InitLoop();
}

Game::~Game()
{

}

void Game::Update(float dt)
{
	SceneManager::GetInstance()->GetCurrentScene()->Update(dt);
	Render();
}

void Game::Render()
{
	auto device = GameGlobal::GetCurrentDevice();
	auto scene = SceneManager::GetInstance()->GetCurrentScene();
	device->Clear(0, NULL, D3DCLEAR_TARGET, scene->GetBackcolor(), 0.0f, 0);

	{
		device->BeginScene();

		//bat dau ve
		GameGlobal::GetCurrentSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);

		//draw here
		scene->Draw();

		//ket thuc ve
		GameGlobal::GetCurrentSpriteHandler()->End();

		device->EndScene();
	}

	device->Present(0, 0, 0, 0);
}

void Game::InitLoop()
{
	MSG msg;

	float tickPerFrame = 1.0f / mFPS, delta = 0;

	while (GameGlobal::isGameRunning)
	{
		GameTime::GetInstance()->StartCounter();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		

		delta += GameTime::GetInstance()->GetCouter();

		if (delta >= tickPerFrame)
		{
			Update((delta));
			KEYBOARD->PollKeyboard();
			KEYBOARD->UpdateKeyboard();
			KEY->update();
			delta = 0;
		}
		else
		{
			Sleep(tickPerFrame - delta);
			delta = tickPerFrame;
		}
	}
}