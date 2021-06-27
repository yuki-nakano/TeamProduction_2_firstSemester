#include "FloatEnemy.h"

FloatEnemy::FloatEnemy()
{
	textureManager = TextureManager::GetInstance();
	gameManager = GameManager::GetInstance();
	player = Player::GetInstance();


}

FloatEnemy::~FloatEnemy()
{
}

void FloatEnemy::Exec()
{
	timer++;
	if (timer >= 300)
	{
		SpownEnemy();

		timer = 0;
	}

	AddCount();

	Move();

	IsCollidePlayer();
}

void FloatEnemy::Draw()
{
	if (!isAlive) { return; }

	for (int i = 0; i < MaxFloatEnemy; i++)
	{
		if (!canMove[i]) { continue; }

		switch (direction[i])
		{
		case kRight:
			DrawRotaGraph2(pos[i].X, pos[i].Y, gimmickWidht / 2, gimmickHeight / 2, 1.0, rote[i], 
				textureManager->GetTextureDate(TextureDate((int)TextureDate::kFloatEnemyRight_1 + animationCount % 2)), TRUE, FALSE);
			break;
		case kLeft:
			DrawRotaGraph2(pos[i].X, pos[i].Y, gimmickWidht / 2, gimmickHeight / 2, 1.0, rote[i], 
				textureManager->GetTextureDate(TextureDate((int)TextureDate::kFloatEnemyLeft_1 + animationCount % 2)), TRUE, FALSE);
			break;
		}

	}
}

void FloatEnemy::Spown()
{
	if (isAlive) { return; }

	isAlive = true;

	timer = 300;

	count = 0;
	animationCount = 0;

	for (int i = 0; i < MaxFloatEnemy; i++)
	{
		canMove[i] = false;
		rote[i] = 0;
	}

	textureManager = TextureManager::GetInstance();
	gameManager = GameManager::GetInstance();
	player = Player::GetInstance();
}

bool FloatEnemy::IsFinished()
{
	return true;
}

void FloatEnemy::IsCollidePlayer()
{
	for (int i = 0; i < MaxFloatEnemy; i++)
	{
		for (int j = 1; j <= 3; j++)
		{
			const float distance_x = player->GetPos().X - pos[i].X;
			const float distance_y = player->GetPos().Y + PlayerHeight / 4 * j - pos[i].Y;

			if (powf(distance_x, 2.0f) + powf(distance_y, 2.0f) < powf((gimmickWidht + PlayerWidht) / 2, 2.0f))
			{
				gameManager->SetIsCollide(true);
			}
		}
	}
}

void FloatEnemy::Move()
{
	for (int i = 0; i < MaxFloatEnemy; i++)
	{
		if (!canMove[i]) { continue; }

		switch (direction[i])
		{
		case kRight:
			pos[i].X += speed;

			if (pos[i].X > Widht + gimmickHeight)
			{
				canMove[i] = false;
			}

			rote[i] += 0.1;
			break;
		case kLeft:
			pos[i].X -= speed;

			if (pos[i].X < gimmickHeight * -1)
			{
				canMove[i] = false;
			}

			rote[i] -= 0.1;
			break;
		}
	}
}

void FloatEnemy::SpownEnemy()
{
	for (int i = 0; i < MaxFloatEnemy; i++)
	{
		if (!canMove[i])
		{
			canMove[i] = true;
			pos[i].Y = GetRand(Height - (gimmickHeight + MapChipEdge) * 2) + gimmickHeight + MapChipEdge;
			direction[i] = (Direction)GetRand(1);
			
			switch (direction[i])
			{
			case kRight:
				pos[i].X = gimmickWidht * -1;
				break;
			case kLeft:
				pos[i].X = gimmickWidht + Widht;
				break;
			}

			return;
		}
	}
}

void FloatEnemy::AddCount()
{
	count++;
	if (count % 20 == 19)
	{
		animationCount += 1;
	}
}