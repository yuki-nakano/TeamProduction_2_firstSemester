#include "Boss.h"

Boss::Boss()
{
	inputManager = InputManager::GetInstance();
	gameManager = GameManager::GetInstance();
	textureManager = TextureManager::GetInstance();
	soundManager = SoundManager::GetInstance();
	player = Player::GetInstance();
}

Boss::~Boss()
{

}

void Boss::Exec()
{
	if (!isAlived) { return; }

	//if (inputManager->IsKeyPushed(KEY_INPUT_1))
	//{
	//	bossGimmickBace[0]->Spown();
	//}
	//
	//if (inputManager->IsKeyPushed(KEY_INPUT_2))
	//{
	//	bossGimmickBace[1]->Spown();
	//}
	//
	//if (inputManager->IsKeyPushed(KEY_INPUT_3))
	//{
	//	bossGimmickBace[2]->Spown();
	//}
	//
	//if (inputManager->IsKeyPushed(KEY_INPUT_4))
	//{
	//	bossGimmickBace[3]->Spown();
	//}
	//
	//if (inputManager->IsKeyPushed(KEY_INPUT_5))
	//{
	//	bossGimmickBace[4]->Spown();
	//}

	switch (phase)
	{
	case Phase::kAppearance:
		pos.Y += MaxSpeed * 0.8f;

		if ((gameManager->GetBossInitPos().Y + 1) * MapChipEdge - height / 2 < pos.Y)
		{
			phase = Phase::kConversation;
		}
		break;
	case Phase::kConversation:
		gimmickTimer++;

		if (gimmickTimer > 240)
		{
			gimmickTimer = 0;

			phase = Phase::kFight;
			bossGimmickBace[kBossFloatEnemy]->Spown();
		}
		break;
	case Phase::kFight:
		damageTimer++;

		GimmickSpown();

		for (int i = 0; i < kBossGimmickMax; i++)
		{
			if (bossGimmickBace[i] == nullptr) { continue; }

			bossGimmickBace[i]->Exec();
		}

		if (inputManager->IsKeyPushed(KEY_INPUT_R))
		{
			currentHp = 0;
		}

		CalculateDamage();
		if (currentHp == 0)
		{
			phase = Phase::kFinish;
			resultTimer = 0;
			PlaySoundMem(soundManager->GetSoundData(Sound::kBoss), DX_PLAYTYPE_BACK);
			soundManager->StopBGM();
		}
		break;
	case Phase::kFinish:
		resultTimer++;

		if (resultTimer == 240)
		{
			gameManager->SetIsClear(true);
			PlaySoundMem(soundManager->GetSoundData(Sound::kClear), DX_PLAYTYPE_BACK);
		}
		break;
	default:
		break;
	}
}

void Boss::Draw()
{
	if (!isAlived) { return; }

	switch (phase)
	{
	case Phase::kAppearance:
		DrawGraph(pos.X - widht / 2, pos.Y - height / 2, textureManager->GetTextureDate(TextureDate::kBossWait), TRUE);
		break;
	case Phase::kConversation:
		DrawGraph(pos.X - widht / 2, pos.Y - height / 2, textureManager->GetTextureDate(TextureDate::kBossWait), TRUE);
		DrawGraph(pos.X - widht / 2 - 400, pos.Y - height / 2 - 250, textureManager->GetTextureDate(TextureDate::kBossDialogueAppearance), TRUE);

		break;
	case Phase::kFight:
		if (!bossGimmickBace[kBossLaser]->GetIsAliveGimmick())
		{
			DrawGraph(pos.X - widht / 2, pos.Y - height / 2, textureManager->GetTextureDate(TextureDate::kBossWait), TRUE);
		}

		for (int i = 0; i < kBossGimmickMax; i++)
		{
			if (bossGimmickBace[i] == nullptr) { continue; }

			bossGimmickBace[i]->Draw();
		}
		DrawGraph((Widht - hpSize) / 2, 90, textureManager->GetTextureDate(TextureDate::kBossHp), TRUE);
		DrawRectGraph((Widht - hpSize) / 2, 90, 0, 0, hpSize * (currentHp / MaxHp), 135, 
			textureManager->GetTextureDate(TextureDate::kBossHpGauge),TRUE, FALSE);
		break;
	case Phase::kFinish:
		if (resultTimer < 480) { break; }
		DrawGraph(pos.X - widht / 2, 920, textureManager->GetTextureDate(TextureDate::kBossWait), TRUE);
		DrawGraph(pos.X - widht / 2 - 400, 720, textureManager->GetTextureDate(TextureDate::kBossDialogueFinish), TRUE);


		break;
	default:
		break;
	}
}

void Boss::Spown()
{
	pos.X = Widht / 2;
	pos.Y = height * -1;
	phase = Phase::kAppearance;
	isAlived = true;
	currentHp = MaxHp;

	bossGimmickBace[kBossDog] = new Dog;
	bossGimmickBace[kBossLaser] = new Laser;
	bossGimmickBace[kBossMetor] = new Metor;
	bossGimmickBace[kBossBlackHole] = new BlackHole;
	bossGimmickBace[kBossFloatEnemy] = new FloatEnemy;
}

void Boss::GimmickSpown()
{
	gimmickTimer++;

	if (gimmickTimer % spownGimmickCoolTime == 0)
	{
		int spownGimmickNum = GetRand(kBossGimmickMax - 1);

		for (int i = 0; i < kBossGimmickMax - 1; i++)
		{
			if (!bossGimmickBace[spownGimmickNum % (kBossGimmickMax - 1)]->GetIsAliveGimmick())
			{
				bossGimmickBace[spownGimmickNum % (kBossGimmickMax - 1)]->Spown();
			}
		}
	}
}

void Boss::CalculateDamage()
{
	if (!inputManager->IsKeyPushed(ResetKey)) { return; }

	if (player->GetCoolTime() != 300) { return; }

	float damage = (int)damageTimer / 60;

	for (int i = 0; i < damageTimer / 600; i++)
	{
		damage *= 1.1;
	}

	currentHp -= (int)damage;
	if (currentHp < 0)
	{
		currentHp = 0;
	}

	damageTimer = 0;
}
