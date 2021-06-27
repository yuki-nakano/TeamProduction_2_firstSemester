#include "Option.h"

Option::Option()
{
	inputManager = InputManager::GetInstance();
	gameManager = GameManager::GetInstance();
	textureManager = TextureManager::GetInstance();
	soundManager = SoundManager::GetInstance();

	player = Player::GetInstance();
	gimmickManager = GimmickManager::GetInstance();
}

Option::~Option()
{
}

bool Option::Exec()
{
	ChangeOption();

	if (!isOption) { return isOption; }

	count++;

	FastTravel();

	return isOption;
}

void Option::Draw()
{
	if (!isOption) { return; }

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	DrawGraph(271, 0, textureManager->GetTextureDate(TextureDate::kPause), TRUE);

	for (int i = 0; i < MaxSaveStage; i++)
	{
		if (i == currentButton &&
			count % 30 < 15)
		{
			continue;
		}

		switch (gameManager->GetCanUsedSaveStage(i))
		{
		case true:
			DrawGraph(60 + 150 * i, 480 + 250 * (i % 2),
				textureManager->GetTextureDate(TextureDate((int)TextureDate::kFastTravelIcon_road + gameManager->GetSaveStageBackGround(i))), TRUE);
			break;
		case false:
			DrawGraph(60 + 150 * i, 480 + 250 * (i % 2),
				textureManager->GetTextureDate(TextureDate::kFastTravelIcon_black), TRUE);
			break;
		}
	}

	if (player->GetHaveKeyItem())
	{
		DrawExtendGraph(Widht - 100, 0, Widht, 100, textureManager->GetTextureDate(TextureDate::kKey_Texture), TRUE);
	}
}

void Option::ChangeOption()
{
	if (inputManager->IsKeyPushed(OptionKey))
	{
		isOption ? isOption = false : isOption = true;
		count = 0;
	}
}

void Option::FastTravel()
{
	if (inputManager->IsKeyPushed(KEY_INPUT_RIGHT) ||
		inputManager->IsKeyPushed(KEY_INPUT_D) &&
		currentButton < MaxSaveStage - 1)
	{
		currentButton++;
	}
	else if (inputManager->IsKeyPushed(KEY_INPUT_LEFT) ||
		inputManager->IsKeyPushed(KEY_INPUT_A) &&
		currentButton > 0)
	{
		currentButton--;
	}
	else if (inputManager->IsKeyPushed(KEY_INPUT_RETURN) &&
		gameManager->GetCanUsedSaveStage(currentButton))
	{
		if (gameManager->GetStageNum() == MaxStage - 1) { return; }

		gameManager->SetStage(gameManager->GetSaveStageNum(currentButton));
		gimmickManager->DeadGimmick();
		player->SetPosX(gameManager->GetPlayerInitPosX(gameManager->GetStageNum()));
		player->SetPosY(gameManager->GetPlayerInitPosY(gameManager->GetStageNum()));
		player->ResetStatus();
		player->SetHaveKeyItem(false);
		soundManager->ChangeBGM(BGM[gameManager->GetStageNum()]);
		gimmickManager->SpawnGimmick(kSun, player->GetPosX(), player->GetPosY());
		isOption = false;
	}
}
