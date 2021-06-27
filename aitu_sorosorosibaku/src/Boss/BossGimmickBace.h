#ifndef BOSS_GIMMICK_BASE_H
#define BOSS_GIMMICK_BASE_H

#include "../Manager/TextureManager.h"
#include "../Manager/GameManager.h"
#include "../Definition.h"
#include "../Scene/Player.h"

#define _USE_MATH_DEFINES
#include <math.h>

class BossGimmickBace
{
public:
	BossGimmickBace();
	virtual ~BossGimmickBace();

	virtual void Exec() = 0;
	virtual void Draw() = 0;

	//ギミックの開始
	virtual void Spown() = 0;

	bool GetIsAliveGimmick() const { return isAlive; }

protected:
	//ギミックの終了判定
	virtual bool IsFinished() = 0;

	//プレイヤーとの接触判定
	virtual void IsCollidePlayer() = 0;

protected:
	TextureManager* textureManager = nullptr;
	GameManager* gameManager = nullptr;
	Player* player = nullptr;

	//ギミックのサイズ
	float gimmickWidht;
	float gimmickHeight;

	//ギミックの生存判定
	bool isAlive = false;
};

#endif // !BOSS_GIMMICK_BASE_H
