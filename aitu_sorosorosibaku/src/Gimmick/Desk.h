#ifndef DESK_H
#define DESK_H

#include "DxLib.h"
#include "GimmickBace.h"

class Desk : public GimmickBace
{
public:
	~Desk();

	bool Exec(float player_posx_, float player_posy_);
	void Draw();

	void Spown(float player_posx_, float player_posy_);

private:
	void IsCollidePlayer(float player_posx_, float player_posy_);

	void AddCount();

	bool IsFinished();

private:
	float gimmickWidht = 34;
	float gimmickHeight = 60;

	int count = 0;
	int animationCount = 0;
};

#endif // !DESK_H
