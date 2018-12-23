#include "MenuScene.h"
#include "DemoScene.h"
#include "../GameControllers/SceneManager.h"
#include "../GameComponents/Sound.h"

MenuScene::MenuScene()
{
	mBackColor = 0x000000;
	mAnimationPlayerStanding = new Animation("Resources/Megaman/Megaman.png", "Resources/Megaman/Standing.txt", 0.2f, true);	//0.3
	mAnimationPlayerStanding->SetPosition(40, 130);
	mSprite = new Sprite("Resources/Scene/MenuScene.png");
	mSprite->SetPosition(128, 100);
	Sound::getInstance()->play("MenuBackground", true, 0);
}

void MenuScene::Update(float dt)
{
	mAnimationPlayerStanding->Update(dt);
	if (KEY->isKeyChangeSceneDownPrevious) {
		Sound::getInstance()->stop("MenuBackground");
		SceneManager::GetInstance()->ReplaceScene(new DemoScene());
	}
}



void MenuScene::Draw()
{
	mSprite->Draw();
	mAnimationPlayerStanding->Draw();
}
