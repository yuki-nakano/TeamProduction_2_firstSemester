#include "Desk.h"

Desk::~Desk()
{
}

bool Desk::Exec(float player_posx_, float player_posy_)
{
	if (!isAlive) { return false; }

	AddCount();

	if (IsFinished())
	{
		gameManager->SetIsCollide(true);
		isAlive = false;
	}

	return true;
}

void Desk::Draw()
{
	if (!isAlive) { return; }

	DrawGraph(pos.X, pos.Y, textureManager->GetTextureDate(TextureDate::kTeacher), TRUE);
}

void Desk::Spown(float player_posx_, float player_posy_)
{
	if (isAlive) { return; }

	isAlive = true;

	pos.Y = player_posy_ - gimmickHeight;
	pos.X = player_posx_ + MapChipEdge;
}

void Desk::IsCollidePlayer(float player_posx_, float player_posy_)
{

}

void Desk::AddCount()
{
	count++;
	if (count % 20 == 19)
	{
		animationCount += 1;
	}
}

bool Desk::IsFinished()
{
	return false;
}
