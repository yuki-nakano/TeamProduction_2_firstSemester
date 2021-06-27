#include "Laser.h"

Laser::Laser()
{
	textureManager = TextureManager::GetInstance();
	gameManager = GameManager::GetInstance();
	player = Player::GetInstance();
}

Laser::~Laser()
{
}

void Laser::Exec()
{
	if (!isAlive) { return; }

	timer++;

	switch (phase)
	{
	case Phase::kCharge:

		pos.Y < player->GetPos().Y - PlayerHeight / 2 ? pos.Y += 1 : pos.Y -= 1;
		
		if (timer > 120)
		{
			phase = Phase::kSmallLaser;
		}

		break;
	case Phase::kSmallLaser:

		if (timer > 180)
		{
			phase = Phase::kBigLaser;
		}

		break;
	case Phase::kBigLaser:

		pos.X += 1;

		gimmickHeight += 1;

		break;
	default:
		break;
	}

	IsCollidePlayer();

	if (IsFinished())
	{
		isAlive = false;
	}
}

void Laser::Draw()
{
	if (!isAlive) { return; }

	if (count < 240)
	{
		DrawGraph(pos.X - BossWidht / 2 - 400, pos.Y  - BossHeight / 2 - 250,
			textureManager->GetTextureDate(TextureDate::kBossDialogueLaser), TRUE);
	}

	switch (phase)
	{
	case Phase::kCharge:

		break;
	case Phase::kSmallLaser:

		DrawExtendGraph(0, pos.Y - gimmickHeight / 2, pos.X, pos.Y + gimmickHeight / 2, textureManager->GetTextureDate(TextureDate::kLeser), TRUE);

		break;
	case Phase::kBigLaser:

		DrawExtendGraph(0, pos.Y - gimmickHeight / 2, pos.X, pos.Y + gimmickHeight / 2, textureManager->GetTextureDate(TextureDate::kLeser), TRUE);

		break;
	default:
		break;
	}

	DrawGraph(pos.X - 120, pos.Y - 80, textureManager->GetTextureDate(TextureDate::kBossWalkLeft_01), TRUE);
}

void Laser::Spown()
{
	if (isAlive) { return; }

	textureManager = TextureManager::GetInstance();
	gameManager = GameManager::GetInstance();
	player = Player::GetInstance();
	isAlive = true;

	count = 0;
	animationCount = 0;

	phase = Phase::kCharge;

	timer = 0;

	gimmickHeight = 2;

	pos.X = Widht;
	pos.Y = player->GetPos().Y - PlayerHeight / 2;
}

bool Laser::IsFinished()
{
	return timer > 360;
}

void Laser::IsCollidePlayer()
{
	if (phase != Phase::kBigLaser) { return; }
	
	if (powf(player->GetPos().Y - PlayerHeight / 2 - pos.Y, 2.0f) <= powf((PlayerHeight + gimmickHeight) / 2, 2.0f))
	{
		gameManager->SetIsCollide(true);
	}

}
