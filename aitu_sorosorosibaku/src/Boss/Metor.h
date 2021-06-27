#ifndef METOR_H
#define METOR_H

#include "BossGimmickBace.h"
#include "DxLib.h"

const int MaxMetor = 20;

class Metor : public BossGimmickBace
{
public:
	Metor();
	~Metor();

	void Exec();
	void Draw();

	void Spown();

private:
	bool IsFinished();

	void IsCollidePlayer();

	void Move();

	void StartMoving();
private:
	const float speed_y = 4.0f;

	TextureManager* textureManager = nullptr;
	GameManager* gameManager = nullptr;
	Player* player = nullptr;

	float gimmickWidht;
	float gimmickHeight;

	Vec3 pos[MaxMetor];

	bool canMove[MaxMetor];

	bool isAlive = false;

	int timer;
};

#endif // !METOR_H
