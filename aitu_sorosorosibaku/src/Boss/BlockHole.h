#ifndef BLACK_HOLE_H
#define BLACK_HOLE_H

#include "BossGimmickBace.h"
#include "DxLib.h"

class BlackHole : public BossGimmickBace
{
public:
	BlackHole();
	~BlackHole();

	void Exec();
	void Draw();

	void Spown();

private:
	bool IsFinished();

	void IsCollidePlayer();

	void Move();

	void AddCount();

private:
	const float speed_x = 3.0f;
	const float speed_y = 4.0f;

	TextureManager* textureManager = nullptr;
	GameManager* gameManager = nullptr;
	Player* player = nullptr;

	float gimmickWidht = 300;
	float gimmickHeight = 300;

	Vec3 pos;

	bool isAlive = false;

	int count = 0;
	int animationCount = 0;

	int rote = 0;
};

#endif // !BLACK_HOLE_H
