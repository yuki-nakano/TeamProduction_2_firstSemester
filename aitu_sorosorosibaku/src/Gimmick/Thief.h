#ifndef THIEF_H
#define THIEF_H

#include "DxLib.h"
#include "GimmickBace.h"

class Thief : public GimmickBace
{
public:
	~Thief();

	bool Exec(float player_posx_, float player_posy_);
	void Draw();

	void Spown(float player_posx_, float player_posy_);

private:
	void IsCollidePlayer(float player_posx_, float player_posy_);

	void Move();

	void AddCount();

	bool IsFinished();

private:
	float gimmickWidht = 90;
	float gimmickHeight = 160;

	bool haveKey = false;

	int speed = MaxSpeed * 2;

	int count = 0;
	int animationCount = 0;
};

#endif // !THIEF_H
