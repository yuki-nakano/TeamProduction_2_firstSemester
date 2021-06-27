#include "NewsPaper.h"

NewsPaper::~NewsPaper()
{
}

bool NewsPaper::Exec(float player_posx_, float player_posy_)
{
	if (!isAlive) { return false; }

	countDown--;

	if (IsFinished())
	{
		isAlive = false;
		return false;
	}

	return true;
}

void NewsPaper::Draw()
{
	if (!isAlive) { return; }

	DrawGraph(0, 0, textureManager->GetTextureDate(TextureDate::kNewsPaper_Texture), TRUE);
}

void NewsPaper::Spown(float player_posx_, float player_posy_)
{
	if (isAlive) { return; }

	isAlive = true;

	countDown = 300;
}

bool NewsPaper::IsFinished()
{
	return countDown <= 0;
}
