#ifndef ENERGY_BULLET_H
#define ENERGY_BULLET_H

#include "DxLib.h"
#include "GimmickBace.h"

class EnergyBullet : public GimmickBace
{
public:
	~EnergyBullet();

	bool Exec(float player_posx_, float player_posy_);
	void Draw();

	void Spown(float player_posx_, float player_posy_);

private:
	void IsCollidePlayer(float player_posx_, float player_posy_);

	void Move();

	void AddCount();

	bool IsFinished();

private:
	float gimmickWidht = 100;
	float gimmickHeight = 100;

	int count = 0;
	int animationCount = 0;

	int speed = MaxSpeed * 3;
};

#endif // !ENERGY_BULLET_H
