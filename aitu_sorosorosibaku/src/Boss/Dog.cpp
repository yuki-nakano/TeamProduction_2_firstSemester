#include "Dog.h"

Dog::~Dog()
{
}

void Dog::Exec()
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

void Dog::Draw()
{
	if (!isAlive) { return; }

	if (count < 240)
	{
		DrawGraph((gameManager->GetBossInitPos().X + 0.5) * MapChipEdge - BossWidht / 2 - 400, (gameManager->GetBossInitPos().Y + 1) * MapChipEdge - BossHeight / 2 - 250,
			textureManager->GetTextureDate(TextureDate::kBossDialogueDog), TRUE);
	}

	switch (direction)
	{
	case kRight:
		DrawTurnGraph(pos.X - gimmickWidht / 2, pos.Y - gimmickHeight / 2,
			textureManager->GetTextureDate(TextureDate((int)TextureDate::kDog_Texture_1 + animationCount % 4)), TRUE);
		break;
	case kLeft:
		DrawGraph(pos.X - gimmickWidht / 2, pos.Y - gimmickHeight / 2, 
			textureManager->GetTextureDate(TextureDate((int)TextureDate::kDog_Texture_1 + animationCount % 4)), TRUE);
	
		break;
	}

}

void Dog::Spown()
{
	if (isAlive) { return; }

	isAlive = true;

	textureManager = TextureManager::GetInstance();
	gameManager = GameManager::GetInstance();
	player = Player::GetInstance();

	pos.X = Widht + gimmickWidht / 2;
	pos.Y = Height - MapChipEdge - gimmickHeight / 2;

	count = 0;

	rotation = 0;
	direction = kLeft;
}

bool Dog::IsFinished()
{
	return pos.X > Widht + gimmickWidht;
}

void Dog::IsCollidePlayer()
{
	if (!isAlive) { return; }

	if (powf(player->GetPos().X - pos.X, 2.0f) <= powf((PlayerWidht + gimmickWidht) / 2, 2.0f) &&
		powf(player->GetPos().Y - PlayerHeight / 2 - pos.Y, 2.0f) <= powf((PlayerHeight + gimmickHeight) / 2, 2.0f))
	{
		gameManager->SetIsCollide(true);
		isAlive = false;
	}
}

void Dog::Move()
{
	if (!isAlive) { return; }

	switch (direction)
	{
	case kRight:
		pos.X += speed;

		if (pos.X > Widht + gimmickHeight && rotation < 6)
		{
			rotation++;
			if (rotation == 6)
			{
				break;
			}

			direction = kLeft;
		}
		break;
	case kLeft:
		pos.X -= speed;

		if (pos.X < gimmickHeight * -1)
		{
			rotation++;
			direction = kRight;
		}
		break;
	}
}

void Dog::AddCount()
{
	count++;
	if (count % 10 == 9)
	{
		animationCount += 1;
	}
}
