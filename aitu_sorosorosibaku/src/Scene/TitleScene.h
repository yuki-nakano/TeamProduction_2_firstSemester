#ifndef TITLT_SCENE_H
#define TITLT_SCENE_H

#include "DxLib.h"
#include "../Definition.h"
#include "../Manager/GameManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/TextureManager.h"

#include "Player.h"
#include "Option.h"

#define _USE_MATH_DEFINES
#include <math.h>

const int NextSceneKey = KEY_INPUT_RETURN;

class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();
public:
	void Exec();
	void Draw();

	virtual bool IsEnd() const; //シーンが終了したかどうかを返す

private:
	GameManager* gameManager = nullptr;
	InputManager* inputManager = nullptr;
	SoundManager* soundManager = nullptr;
	TextureManager* textureManager = nullptr;
	Option* option = nullptr;
	Player* player = nullptr;

	//シーン終了時にtrueにする
	bool finishedScene = false;

	int animationCount = 0;
	int animationCount_Player = 0;

	int isOption = false;
	int tmp;
};

#endif // !TITLT_SCENE_H