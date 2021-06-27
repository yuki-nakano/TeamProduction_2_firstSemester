#include "Wood.h"

Wood::~Wood()
{
}

bool Wood::Exec(float player_posx_, float player_posy_)
{
	if (!isAlive) { return false; }

	AddCount();

	IsCollidePlayer(player_posx_, player_posy_);

	if (IsFinished())
	{
		isAlive = false;
		return false;
	}

	return true;
}

void Wood::Draw()
{
	if (!isAlive) { return; }

}

void Wood::Spown(float player_posx_, float player_posy_)
{
	if (isAlive) { return; }

	isAlive = true;

	pos.Y = player_posy_ - gimmickHeight / 2;
	pos.X = Widht;
}

void Wood::IsCollidePlayer(float player_posx_, float player_posy_)
{
	if (powf(player_posx_ - (pos.X + gimmickWidht / 4), 2.0f) <= powf(PlayerWidht / 2 + gimmickWidht / 4, 2.0f) &&
		powf(player_posy_ - PlayerHeight / 2 - (pos.Y + gimmickHeight / 4 * 3), 2.0f) <= powf(PlayerHeight / 2 + gimmickHeight / 4, 2.0f))
	{
		gameManager->SetIsCollide(true);
		isAlive = false;
	}
}

void Wood::AddCount()
{
	count++;
	if (count % 20 == 19)
	{
		animationCount += 1;
	}
}

bool Wood::IsFinished()
{
	return pos.X + gimmickWidht < 0;
}
