#include "Ridder.h"

Ridder::~Ridder()
{
}

bool Ridder::Exec(float player_posx_, float player_posy_)
{
	if (!isAlive) { return false; }

	AddCount();

	Move();

	IsCollidePlayer(player_posx_, player_posy_);

	if (IsFinished())
	{
		isAlive = false;
		return false;
	}

	return true;
}

void Ridder::Draw()
{
	if (!isAlive) { return; }

	DrawGraph(pos.X, pos.Y - 20, textureManager->GetTextureDate(TextureDate((int)TextureDate::kRider_Texture_1 + animationCount % 3)), TRUE);
//	DrawBox(pos.X, pos.Y, pos.X + gimmickWidht, pos.Y + gimmickHeight, GetColor(0, 0, 0), FALSE);
}

void Ridder::Spown(float player_posx_, float player_posy_)
{
	if (isAlive) { return; }

	isAlive = true;

	pos.Y = player_posy_ - gimmickHeight / 2;
	pos.X = Widht;
}

void Ridder::Move()
{
	pos.X -= speed;
}

void Ridder::IsCollidePlayer(float player_posx_, float player_posy_)
{
	if (powf(player_posx_ - (pos.X + gimmickWidht / 4), 2.0f) <= powf(PlayerWidht / 2 + gimmickWidht / 4, 2.0f) &&
		powf(player_posy_ - PlayerHeight / 2 - (pos.Y + gimmickHeight / 4 * 3), 2.0f) <= powf(PlayerHeight/ 2 + gimmickHeight / 4, 2.0f))
	{
		gameManager->SetIsCollide(true);
		isAlive = false;
	}
}

void Ridder::AddCount()
{
	count++;
	if (count % 20 == 19)
	{
		animationCount += 1;
	}
}

bool Ridder::IsFinished()
{
	return pos.X + gimmickWidht < 0;
}
