#ifndef FLOAT_ENEMY_H
#define FLOAT_ENEMY_H

#include "BossGimmickBace.h"
#include "DxLib.h"

const int MaxFloatEnemy = 3;

class FloatEnemy : public BossGimmickBace
{
public:
	FloatEnemy();
	~FloatEnemy();

	void Exec();
	void Draw();

	void Spown();

private:
	bool IsFinished();

	void IsCollidePlayer();

	void Move();

	void SpownEnemy();

	void AddCount();
private:
	const float speed = MaxSpeed / 2;

	TextureManager* textureManager = nullptr;
	GameManager* gameManager = nullptr;
	Player* player = nullptr;

	float gimmickWidht = 90;
	float gimmickHeight = 160;

	Vec3 pos[MaxFloatEnemy];
	bool canMove[MaxFloatEnemy];
	Direction direction[MaxFloatEnemy];
	float rote[MaxFloatEnemy];

	int timer = 0;

	int count = 0;
	int animationCount = 0;
};

#endif // !FLOAT_ENEMY_H
