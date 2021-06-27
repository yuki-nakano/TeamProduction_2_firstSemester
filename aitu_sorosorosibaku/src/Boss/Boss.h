#ifndef BOSS_H
#define BOSS_H

#include "DxLib.h"
#include "../Manager/GameManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/TextureManager.h"
#include "../Manager/InputManager.h"
#include "../Definition.h"
#include "../Singleton.h"
#include "../Scene/Player.h"

#include "Dog.h"
#include "Laser.h"
#include "Metor.h"
#include "BlockHole.h"
#include "FloatEnemy.h"


class Boss : public Singleton<Boss>
{
public:
	Boss();
	~Boss();

	void Exec();
	void Draw();

	void Spown();

private:
	void GimmickSpown();

	void CalculateDamage();
private:
	const int ResetKey = KEY_INPUT_RETURN;

	const int spownGimmickCoolTime = 480;
	const int hpSize = 1750;
	const float MaxHp = 188;

	InputManager* inputManager = nullptr;
	GameManager* gameManager = nullptr;
	TextureManager* textureManager = nullptr;
	SoundManager* soundManager = nullptr;
	Player* player = nullptr;

	Vec3 pos;

	int widht = 90;
	int height = 160;

	int damageTimer = 0;
	int gimmickTimer = 0;
	int resultTimer = 0;

	bool isAlived = false;

	float currentHp;

	enum class Phase
	{
		kAppearance,
		kConversation,
		kFight,
		kFinish,
	};
	Phase phase = Phase::kAppearance;

	enum BossGimmick
	{
		kBossDog,
		kBossLaser,
		kBossMetor,
		kBossBlackHole,
		kBossFloatEnemy,
		kBossGimmickMax
	};

	//‹Z
	BossGimmickBace* bossGimmickBace[kBossGimmickMax];
};

#endif // !BOSS_H
