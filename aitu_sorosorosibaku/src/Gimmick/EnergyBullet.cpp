#include "EnergyBullet.h"

EnergyBullet::~EnergyBullet()
{
}

bool EnergyBullet::Exec(float player_posx_, float player_posy_)
{
	if (!isAlive) { return false; }

	AddCount();

	Move();

	IsCollidePlayer(player_posx_, player_posy_);

	if (IsFinished())
	{
		isAlive = false;
	}

	return true;
}

void EnergyBullet::Draw()
{
	if (!isAlive) { return; }

	DrawGraph(pos.X - gimmickWidht / 2, pos.Y - gimmickWidht / 2, textureManager->GetTextureDate(TextureDate::kEnergyBullet_left), TRUE);
	//	DrawBox(pos.X, pos.Y, pos.X + gimmickWidht, pos.Y + gimmickHeight, GetColor(0, 0, 0), FALSE);
}

void EnergyBullet::Spown(float player_posx_, float player_posy_)
{
	if (isAlive) { return; }

	isAlive = true;

	pos.Y = player_posy_;
	pos.X = Widht + gimmickWidht;
}

void EnergyBullet::IsCollidePlayer(float player_posx_, float player_posy_)
{
	if (powf(player_posx_ - pos.X, 2.0f) <= powf((PlayerWidht + gimmickWidht) / 2, 2.0f) &&
		powf(player_posy_ - PlayerHeight / 2 - pos.Y, 2.0f) <= powf((PlayerHeight + gimmickHeight) / 2, 2.0f))
	{
		gameManager->SetIsCollide(true);
		isAlive = false;
	}
}

void EnergyBullet::Move()
{
	pos.X -= speed;
}

void EnergyBullet::AddCount()
{
	count++;
	if (count % 20 == 19)
	{
		animationCount += 1;
	}
}

bool EnergyBullet::IsFinished()
{
	return pos.X + gimmickWidht < 0;
}
