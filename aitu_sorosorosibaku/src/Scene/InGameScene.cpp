#include "InGameScene.h"

GameScene::GameScene()
{
	gameManager = GameManager::GetInstance();
	gameManager->SetStage(0);
	
	inputManager = InputManager::GetInstance();
	soundManager = SoundManager::GetInstance();
	textureManager = TextureManager::GetInstance();

	SceneManager::GetInstance()->SetNextScene(SceneID_InGame);

	GimmickManager::CreateInstance();
	gimmickManager = GimmickManager::GetInstance();

	Player::CreateInstance();
	player = Player::GetInstance();
	player->SetPosX(gameManager->GetPlayerInitPosX(gameManager->GetStageNum()));
	player->SetPosY(gameManager->GetPlayerInitPosY(gameManager->GetStageNum()));
	player->SetIsDead(false);

	Boss::CreateInstance();
	boss = Boss::GetInstance();

	Option::CreateInstance();
	option = Option::GetInstance();

	stayTime = 0;
}

GameScene::~GameScene()
{
	gimmickManager->DeleteInstance();

	boss->DeleteInstance();
	player->DeleteInstance();
}

void GameScene::Exec()
{
	Result();

	if (stayTime != 0 && stayTime < 60) { return; }

	if (option->Exec())
	{
		return;
	}

	animationCount++;

	player->Exec();

	boss->Exec();

	gimmickManager->Exec(player->GetPosX(), player->GetPosY());

	ChangeMap();
}

void GameScene::Draw()
{
	DrawGraph(0, 0, textureManager->GetTextureDate(backGround[gameManager->GetStageNum()]), FALSE);

	DrawMap();

	gimmickManager->Draw();

	boss->Draw();

	ResultDraw();	

	player->Draw();

	option->Draw();

	//DrawBox(90, 60, 1840, 105, GetColor(255, 255, 0), TRUE);

}

bool GameScene::IsEnd() const
{
	return (finishedScene);
}

void GameScene::DrawMap()
{
	for (int y = 0; y < MapHeight; y++)
	{
		for (int x = 0; x < MapWidht; x++)
		{
			if (gameManager->GetCurrentBlockMapDate(x, y))
			{
				DrawGraph(x * MapChipEdge, y * MapChipEdge, textureManager->GetTextureDate(TextureDate::kMapChip_Block_Texture), TRUE);
			}

			DrawGimmickMap(x, y);
		}
	}
}

void GameScene::DrawGimmickMap(int x_, int y_)
{
	switch (gameManager->GetCurrentGimmickMapDate(x_, y_))
	{
	case kTransparentBlock:
		DrawGraph(x_ * MapChipEdge, y_ * MapChipEdge, textureManager->GetTextureDate(TextureDate::kMapChip_Block_Texture), TRUE);
		break;
	case kGoalTexturePos:
		DrawGraph(x_ * MapChipEdge - 10, y_ * MapChipEdge - 40, textureManager->GetTextureDate(TextureDate::kGool_Texture), TRUE);
		break;
	case kKey:
		DrawGraph(x_ * MapChipEdge, y_ * MapChipEdge, textureManager->GetTextureDate(TextureDate::kKey_Texture), TRUE);
		break;
	case kMineSwitch:
		break;
	case kWood:
		break;
	case kDesk:
		DrawGraph(x_ * MapChipEdge, y_ * MapChipEdge, textureManager->GetTextureDate(TextureDate::kDesk), TRUE);
		break;
	case kNeedle:
		DrawExtendGraph(x_ * MapChipEdge, y_ * MapChipEdge, (x_ + 1) * MapChipEdge, (y_ + 1) * MapChipEdge,
			textureManager->GetTextureDate(TextureDate::kNeedle), TRUE);
		break;
	case kPushpin:
		DrawGraph(x_ * MapChipEdge, y_ * MapChipEdge, textureManager->GetTextureDate(TextureDate::kPushPin), TRUE);
		break;
	case kFakeChest:
		DrawGraph(x_ * MapChipEdge + (MapChipEdge - GimmickWidht_Chest) / 2, (y_ + 1) * MapChipEdge - GimmickHeight_Chest, 
			textureManager->GetTextureDate(TextureDate::kChest_close), TRUE);
		break;
	case kChest_close:
		DrawGraph(x_ * MapChipEdge + (MapChipEdge - GimmickWidht_Chest) / 2, (y_ + 1) * MapChipEdge - GimmickHeight_Chest,
			textureManager->GetTextureDate(TextureDate::kChest_close), TRUE);
		break;
	case kBlindBack:
		break;
	case kFakeGool:
		DrawGraph(x_ * MapChipEdge + (MapChipEdge - GimmickWidht_Chest) / 2, (y_ + 1) * MapChipEdge - GimmickHeight_Chest,
			textureManager->GetTextureDate(TextureDate::kChest_close), TRUE);
		break;
	case kChaosOperation:
		break;
	case kGravity:
		break;
	case kRocketTexturePos:
		DrawGraph(x_ * MapChipEdge, y_ * MapChipEdge, textureManager->GetTextureDate(TextureDate::kRocket_wait), TRUE);
		break;
	case kRegent:

		break;
	case kChest_open:
		DrawGraph(x_ * MapChipEdge + (MapChipEdge - GimmickWidht_Chest) / 2, (y_ + 1) * MapChipEdge - GimmickHeight_Chest,
			textureManager->GetTextureDate(TextureDate::kChest_open), TRUE);
		break;
	default:
		break;
	}
}

bool GameScene::Result()
{
	if (!player->GetIsDead() && !gameManager->GetIsClear()) { return false; }

	stayTime++;

	if (gameManager->GetIsClear())
	{
		switch (gameManager->GetClearedGame())
		{
		case true:
			if (inputManager->IsKeyPushed(KEY_INPUT_RETURN) && stayTime > 480)
			{
				gameManager->SetIsClear(false);
				finishedScene = true;
				gimmickManager->DeadGimmick();
				SceneManager::GetInstance()->SetNextScene(SceneID_Title);
				soundManager->StartBGM(Sound::kTitle);
			}
			break;
		case false:
			if (stayTime > 780)
			{
				gameManager->SetFinishGame(true);
			}
			break;
		}
	}
	else if (player->GetIsDead())
	{
		if (stayTime == 30)
		{
			PlaySoundMem(soundManager->GetSoundData(Sound::kLose), DX_PLAYTYPE_BACK);
		}

		if (inputManager->IsKeyPushed(KEY_INPUT_RETURN) && stayTime >= 60)
		{
			StopSoundMem(soundManager->GetSoundData(Sound::kLose));
			finishedScene = true;
			gimmickManager->DeadGimmick();
			SceneManager::GetInstance()->SetNextScene(SceneID_Title);
			soundManager->StartBGM(Sound::kTitle);
		}
	}

	return true;
}

void GameScene::ResultDraw()
{
	if (gameManager->GetIsClear())
	{
		DrawGraph(0, 0, textureManager->GetTextureDate(TextureDate::kResult_clear), TRUE);

		switch (gameManager->GetClearedGame())
		{
		case true:
			DrawGraph(0, 720, textureManager->GetTextureDate(TextureDate::kResult_button), TRUE);
			break;
		case false:
			break;
		}
	}
	else if (player->GetIsDead() && stayTime > 60)
	{
		DrawGraph(0, 0, textureManager->GetTextureDate(TextureDate::kResult_lose), TRUE);
		DrawGraph(0, 720, textureManager->GetTextureDate(TextureDate::kResult_button), TRUE);
	}
}

void GameScene::ChangeMap()
{
	if (player->GetPosX() + PlayerWidht / 2 > 1920 &&
		gameManager->GetIsChangeStageFront())
	{
		gimmickManager->DeadGimmick();
		gameManager->SetStage(gameManager->GetStageNum() + 1);
		player->SetPosX(player->GetPosX() - (1910 - PlayerWidht));
		player->SetPosY(player->GetPosY() - 1);
		soundManager->ChangeBGM(BGM[gameManager->GetStageNum()]);

		gimmickManager->SpawnGimmick(kSun, player->GetPosX(), player->GetPosY());

		const int StageNum = gameManager->GetStageNum();

		if (StageNum == MaxStage - 1)
		{
			boss->Spown();
		}

		switch (StageNum)
		{
		case 19:
			player->SetCurrentGravity(0.1f);
			break;
		case 20:
			player->SetCurrentGravity(0.1f);
			break;
		default:
			player->SetCurrentGravity(0.5f);
			break;
		}
	}
	else if (player->GetPosX() + PlayerWidht / 2 > 1920 &&
		!gameManager->GetIsChangeStageFront())
	{
		player->SetPosX(1920 - PlayerWidht / 2);
	}

	if (player->GetPosX() - PlayerWidht / 2 < 0 &&
		gameManager->GetIsChangeStageBack())
	{
		gimmickManager->DeadGimmick();
		gameManager->SetStage(gameManager->GetStageNum() - 1);
		player->SetPosX(player->GetPosX() + (1910 - PlayerWidht));
		player->SetPosY(player->GetPosY() - 1);
		soundManager->ChangeBGM(BGM[gameManager->GetStageNum()]);

		gimmickManager->SpawnGimmick(kSun, player->GetPosX(), player->GetPosY());

		const int StageNum = gameManager->GetStageNum();

		switch (StageNum)
		{
		case 19:
			player->SetCurrentGravity(0.1f);
			break;
		case 20:
			player->SetCurrentGravity(0.1f);
			break;
		default:
			player->SetCurrentGravity(0.5f);
			break;
		}
	}
	else if (player->GetPosX() - PlayerWidht / 2 < 0 &&
		!gameManager->GetIsChangeStageBack())
	{
		player->SetPosX(PlayerWidht / 2);
	}
}
