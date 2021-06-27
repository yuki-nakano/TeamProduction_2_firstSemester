#include "Mine.h"

Mine::~Mine()
{
}

bool Mine::Exec(float player_posx_, float player_posy_)
{
	if (!isAlive) { return false; }

	AddCount();

	if (IsFinished())
	{
		isAlive = false;
		return false;
	}

	return true;
}

void Mine::Draw()
{
	if (!isAlive) { return; }

	DrawGraph(pos.X, pos.Y - 20, textureManager->GetTextureDate(TextureDate((int)TextureDate::kMine_Texture_1 + animationCount % 8)), TRUE);
}

void Mine::Spown(float player_posx_, float player_posy_)
{
	if (isAlive) { return; }

	isAlive = true;

	count = 0;
	animationCount = 0;

	pos.X = player_posx_ - gimmickWidht / 2;
	pos.Y = player_posy_ - gimmickHeight;
}

void Mine::AddCount()
{
	count++;
	if (count % 10 == 9)
	{
		animationCount += 1;
	}
}

bool Mine::IsFinished()
{
	return count > 80;
}
