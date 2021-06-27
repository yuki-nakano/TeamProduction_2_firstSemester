#ifndef IN_GAME_SCENE_H
#define IN_GAME_SCENE_H

#include "DxLib.h"
#include "../Definition.h"
#include "../Manager/GameManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/TextureManager.h"
#include "../Manager/GimmickManager.h"
#include "Option.h"
#include "Player.h"
#include "../Boss/Boss.h"

#define _USE_MATH_DEFINES
#include <math.h>

const int BuckKey = KEY_INPUT_ESCAPE;

class GameScene : public SceneBase
{
public:
	GameScene();
	~GameScene();
public:
	void Exec();
	void Draw();

	virtual bool IsEnd() const; //シーンが終了したかどうかを返す
private:
	//マップの描画
	void DrawMap();
	void DrawGimmickMap(int x_, int y_);
	
	//void Reset();

	bool Result();
	void ResultDraw();

	void ChangeMap();

private:
	GameManager* gameManager = nullptr;
	InputManager* inputManager = nullptr;
	SoundManager* soundManager = nullptr;
	TextureManager* textureManager = nullptr;
	GimmickManager* gimmickManager = nullptr;

	Player* player = nullptr;
	Boss* boss = nullptr;
	Option* option = nullptr;

	//シーン終了時にtrueにする
	bool finishedScene = false;

	int animationCount = 0;

	int isOption = false;

	int stayTime;

	TextureDate backGround[MaxStage] =
	{
		TextureDate::kBackGround_01,TextureDate::kBackGround_02,TextureDate::kBackGround_03,
		TextureDate::kBackGround_04,TextureDate::kBackGround_05,
		TextureDate::kBackGround_12,TextureDate::kBackGround_12,
		TextureDate::kBackGround_04,TextureDate::kBackGround_05,
		TextureDate::kBackGround_08,
		TextureDate::kBackGround_04,TextureDate::kBackGround_05,
		TextureDate::kBackGround_06,TextureDate::kBackGround_07,
		TextureDate::kBackGround_04,
		TextureDate::kBackGround_04,TextureDate::kBackGround_05,
		TextureDate::kBackGround_09,TextureDate::kBackGround_09,
		TextureDate::kBackGround_10,TextureDate::kBackGround_11,
	};

	Sound BGM[MaxStage] =
	{
		Sound::kStageBGM1,Sound::kStageBGM1,Sound::kStageBGM1,
		Sound::kStageBGM2,Sound::kStageBGM2,
		Sound::kStageBGM3,Sound::kStageBGM3,
		Sound::kStageBGM2,Sound::kStageBGM2,
		Sound::kStageBGM4,
		Sound::kStageBGM2,Sound::kStageBGM2,
		Sound::kStageBGM5,Sound::kStageBGM5,
		Sound::kStageBGM4,
		Sound::kStageBGM4,Sound::kStageBGM4,
		Sound::kStageBGM6,Sound::kStageBGM6,
		Sound::kStageBGM7,Sound::kBossBGM,
	};

};

#endif // !IN_GAME_SCENE_H