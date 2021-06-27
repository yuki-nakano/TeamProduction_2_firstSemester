#include "BlockHole.h"

BlackHole::BlackHole()
{
	textureManager = TextureManager::GetInstance();
	gameManager = GameManager::GetInstance();
	player = Player::GetInstance();
}

BlackHole::~BlackHole()
{
}

void BlackHole::Exec()
{
	if (!isAlive) { return; }

	AddCount();

	Move();

	IsCollidePlayer();

	if (IsFinished())
	{
		isAlive = false;
	}
}

void BlackHole::Draw()
{
	if (!isAlive) { return; }

	if (count < 240)
	{
		DrawGraph((gameManager->GetBossInitPos().X + 0.5) * MapChipEdge - BossWidht / 2 - 400, (gameManager->GetBossInitPos().Y + 1) * MapChipEdge - BossHeight / 2 - 250,
			textureManager->GetTextureDate(TextureDate::kBossDialogueBlackHole), TRUE);
	}


	DrawRotaGraph2(pos.X, pos.Y, gimmickWidht / 2, gimmickHeight / 2, 1.0, rote,
		textureManager->GetTextureDate(TextureDate((int)TextureDate::kBlackHoke1 + animationCount % 3)), TRUE, FALSE);
}

void BlackHole::Spown()
{
	if (isAlive) { return; }

	isAlive = true;

	textureManager = TextureManager::GetInstance();
	gameManager = GameManager::GetInstance();
	player = Player::GetInstance();

	count = 0;
	animationCount = 0;

	rote = 0;

	pos.X = GetRand(Widht - (MapChipEdge + (int)gimmickWidht / 2) * 2) + (MapChipEdge + gimmickWidht / 2);
	pos.Y = gimmickHeight * -1;

}

bool BlackHole::IsFinished()
{
	return pos.Y - gimmickHeight / 2 > Height;
}

void BlackHole::IsCollidePlayer()
{
	for (int i = 1; i <= 3; i++)
	{
		const float distance_x = player->GetPos().X - pos.X;
		const float distance_y = player->GetPos().Y + PlayerHeight / 4 * i - pos.Y;

		if (powf(distance_x, 2.0f) + powf(distance_y, 2.0f) < powf((gimmickWidht + PlayerWidht) / 2, 2.0f))
		{
			gameManager->SetIsCollide(true);
		}
	}
}

void BlackHole::Move()
{
	rote += 0.5;

	pos.Y += speed_y;

	const float distance = player->GetPos().X - pos.X;
	if (distance <= speed_x &&
		distance >= speed_x * -1)
	{
		pos.X += distance;
	}
	else if (distance > speed_x)
	{
		pos.X += speed_x;
	}
	else if (distance < speed_x * -1)
	{
		pos.X += speed_x * -1;
	}
}

void BlackHole::AddCount()
{
	count++;
	if (count % 10 == 9)
	{
		animationCount += 1;
	}
}
