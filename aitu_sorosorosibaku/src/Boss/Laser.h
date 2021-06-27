#ifndef LASER_H
#define LASER_H

#include "BossGimmickBace.h"
#include "DxLib.h"

class Laser : public BossGimmickBace
{
public:
	Laser();
	~Laser();

	void Exec();
	void Draw();

	void Spown();

private:
	bool IsFinished();

	void IsCollidePlayer();

private:
	TextureManager* textureManager = nullptr;
	GameManager* gameManager = nullptr;
	Player* player = nullptr;

	float gimmickWidht = Widht;
	float gimmickHeight = 0;

	Vec3 pos;

	int timer = 0;
	
	enum class Phase
	{
		kCharge,
		kSmallLaser,
		kBigLaser,
	};
	Phase phase = Phase::kCharge;

	int count = 0;
	int animationCount = 0;
};

#endif // !LASER_H
