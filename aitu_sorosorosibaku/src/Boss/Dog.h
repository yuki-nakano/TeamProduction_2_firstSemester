#ifndef DOG_H
#define DOG_H

#include "BossGimmickBace.h"
#include "DxLib.h"

class Dog : public BossGimmickBace
{
public:
	~Dog();

	void Exec();
	void Draw();

	void Spown();

private:
	bool IsFinished();

	void IsCollidePlayer();

	void Move();

	void AddCount();

private:
	TextureManager* textureManager = nullptr;
	GameManager* gameManager = nullptr;
	Player* player = nullptr;

	float gimmickWidht = 120;
	float gimmickHeight = 60;

	Vec3 pos;
	Direction direction;
	int rotation;
	float speed = MaxSpeed * 2;

	bool isAlive = false;

	int count = 0;
	int animationCount = 0;
};

#endif // !DOG_H
