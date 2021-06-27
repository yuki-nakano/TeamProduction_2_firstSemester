#include "Metor.h"

Metor::Metor()
{
	textureManager = TextureManager::GetInstance();
	gameManager = GameManager::GetInstance();
	player = Player::GetInstance();
}

Metor::~Metor()
{
}

void Metor::Exec()
{
	if (!isAlive) { return; }

	StartMoving();

	Move();

	IsCollidePlayer();

	if (IsFinished())
	{
		isAlive = false;
	}
}

void Metor::Draw()
{
	if (!isAlive) { return; }

	if (timer < 240)
	{
		DrawGraph((gameManager->GetBossInitPos().X + 0.5) * MapChipEdge - BossWidht / 2 - 400, (gameManager->GetBossInitPos().Y + 1) * MapChipEdge - BossHeight / 2 - 250,
			textureManager->GetTextureDate(TextureDate::kBossDialogueMetor), TRUE);
	}


	for (int i = 0; i < MaxMetor; i++)
	{
		if (!canMove[i]) { continue; }

		DrawGraph(pos[i].X - gimmickWidht / 2, pos[i].Y - gimmickHeight / 2, textureManager->GetTextureDate(TextureDate::kEnergyBullet_down), TRUE);
	}
}

void Metor::Spown()
{
	if (isAlive) { return; }

	textureManager = TextureManager::GetInstance();
	gameManager = GameManager::GetInstance();
	player = Player::GetInstance();

	timer = 0;

	isAlive = true;

	for (int i = 0; i < MaxMetor; i++)
	{
		canMove[i] = false;
		pos[i].Y = gimmickHeight / 2 * -1;
		pos[i].X = GetRand(Widht - (MapChipEdge + (int)gimmickWidht / 2) * 2) + (MapChipEdge + gimmickWidht / 2);
	}
}

bool Metor::IsFinished()
{
	return pos[MaxMetor - 1].Y - gimmickHeight / 2 > Height;
}

void Metor::IsCollidePlayer()
{
	for (int i = 0; i < MaxMetor; i++)
	{
		if (!canMove[i]) { continue; }

		if (powf(player->GetPos().X - pos[i].X, 2.0f) <= powf((PlayerWidht + gimmickWidht) / 2, 2.0f) &&
			powf(player->GetPos().Y - PlayerHeight / 2 - pos[i].Y , 2.0f) <= powf((PlayerHeight + gimmickHeight) / 2, 2.0f))
		{
			gameManager->SetIsCollide(true);
			isAlive = false;
		}
	}
}

void Metor::Move()
{
	for (int i = 0; i < MaxMetor; i++)
	{
		if (!canMove[i]) { continue; }

		pos[i].Y += speed_y;
	}
}

void Metor::StartMoving()
{
	if (timer >= 600) { return; }

	timer++;
	if (timer % 30 == 0)
	{
		canMove[timer / 30] = true;
	}
}
