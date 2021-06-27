#include "Thief.h"

Thief::~Thief()
{
}

bool Thief::Exec(float player_posx_, float player_posy_)
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

void Thief::Draw()
{
	if (!isAlive) { return; }

	DrawGraph(pos.X - gimmickWidht / 2, pos.Y - gimmickHeight / 2, 
		textureManager->GetTextureDate(TextureDate((int)TextureDate::kThief_1 + animationCount % 2)), TRUE);
}

void Thief::Spown(float player_posx_, float player_posy_)
{
	if (isAlive) { return; }

	isAlive = true;

	haveKey = false;

	pos.Y = player_posy_ - gimmickHeight / 2;
	pos.X = Widht;
}

void Thief::Move()
{
	pos.X -= speed;
}

void Thief::IsCollidePlayer(float player_posx_, float player_posy_)
{
	if (powf(player_posx_ - (pos.X + gimmickWidht / 4), 2.0f) <= powf(PlayerWidht / 2 + gimmickWidht / 4, 2.0f) &&
		powf(player_posy_ - PlayerHeight / 2 - (pos.Y + gimmickHeight / 4 * 3), 2.0f) <= powf(PlayerHeight / 2 + gimmickHeight / 4, 2.0f))
	{
		gameManager->SetIsCollideThief(true);
		haveKey = true;
	}
}

void Thief::AddCount()
{
	count++;
	if (count % 20 == 19)
	{
		animationCount += 1;
	}
}

bool Thief::IsFinished()
{
	return pos.X + gimmickWidht < 0;
}
