#ifndef WOOD_H
#define WOOD_H

#include "DxLib.h"
#include "GimmickBace.h"

class Wood : public GimmickBace
{
public:
	~Wood();

	bool Exec(float player_posx_, float player_posy_);
	void Draw();

	void Spown(float player_posx_, float player_posy_);

private:
	void IsCollidePlayer(float player_posx_, float player_posy_);

	void AddCount();

	bool IsFinished();

private:
	float gimmickWidht = 180;
	float gimmickHeight = 140;

	int count = 0;
	int animationCount = 0;
};

#endif // !WOOD_H
