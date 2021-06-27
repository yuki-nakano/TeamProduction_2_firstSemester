#ifndef RIDER_H
#define RIDER_H

#include "DxLib.h"
#include "GimmickBace.h"

class Ridder : public GimmickBace
{
public:
	~Ridder();

	bool Exec(float player_posx_, float player_posy_);
	void Draw();

	void Spown(float player_posx_, float player_posy_);

private:
	void Move();

	void IsCollidePlayer(float player_posx_, float player_posy_);

	void AddCount();

	bool IsFinished();

private:
	int speed = MaxSpeed * 2;

	float gimmickWidht = 180;
	float gimmickHeight = 140;

	int count = 0;
	int animationCount = 0;
};

#endif // !RIDER_H
