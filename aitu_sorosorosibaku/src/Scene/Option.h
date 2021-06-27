#ifndef OPTION_H
#define OPTION_H

#include "DxLib.h"
#include "../Definition.h"
#include "../Singleton.h"
#include "../Manager/InputManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/GameManager.h"
#include "../Manager/TextureManager.h"
#include "Player.h"
#include "../Manager/GimmickManager.h"

class Option : public Singleton<Option>
{
public:
	Option();
	~Option();

	bool Exec();
	void Draw();

private:
	void ChangeOption();

	void FastTravel();

private:
	InputManager* inputManager = nullptr;
	GameManager* gameManager = nullptr;
	TextureManager* textureManager = nullptr;
	SoundManager* soundManager = nullptr;
	GimmickManager* gimmickManager = nullptr;
	Player* player = nullptr;

	int OptionKey = KEY_INPUT_ESCAPE;

	bool isOption = false;

	int currentButton = 0;

	int count = 0;

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

#endif // !OPTION_H