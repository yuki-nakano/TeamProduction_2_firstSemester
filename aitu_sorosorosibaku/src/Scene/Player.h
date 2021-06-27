#ifndef PLAYER_H
#define PLAYER_H

#include "DxLib.h"
#include "../Definition.h"
#include "../Singleton.h"
#include "../Manager/GameManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/TextureManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/GimmickManager.h"

const int RightMoveKey = KEY_INPUT_D;
const int LeftMoveKey = KEY_INPUT_A;
const int JumpKey = KEY_INPUT_SPACE;
const int SearchKey = KEY_INPUT_W;
const int ResetKey = KEY_INPUT_RETURN;

class Player : public Singleton<Player>
{
public:
	Player();
	~Player();

	void Exec();
	void Draw();

	Vec3 GetPos() const { return pos; }

	float GetPosX() const { return pos.X; }
	void SetPosX(float posx_) { pos.X = posx_; }

	float GetPosY() const { return pos.Y; }
	void SetPosY(float posy_) { pos.Y = posy_; }

	int GetMapPosX() const { return mapPos.X; }
	void SetMapPosX(int posx_) { mapPos.X = posx_; }

	int GetMapPosY() const { return mapPos.Y; }
	void SetMapPosY(int posy_) { mapPos.Y = posy_; }

	bool GetIsDead() const { return isDead; }
	void SetIsDead(bool is_dead_) { isDead = is_dead_; }

	bool GetHaveKeyItem() const { return haveKeyItem; }
	void SetHaveKeyItem(bool have_key_item_) { haveKeyItem = have_key_item_; }

	void ResetStatus();

	void SetCurrentGravity(float gravity_) { gravity = gravity_; }

	int GetCoolTime() const { return coolTime; }

private:
	//摩擦
	void Friction();

	//キャラ移動
	void Move();

	//キャラのジャンプ
	void Jump();

	void Reset();

	void Search();

	void GoToNextStage();

	//キャラの座標の更新
	void ChangePos();

	//ブロックへのめり込み確認
	void CheckCollisionBlock();
	//上側のブロックへの確認
	float CheckCollisionBlock_up();
	//下側のブロックへの確認
	float CheckCollisionBlock_down();
	//右側のブロックへの確認
	float CheckCollisionBlock_right();
	//左側のブロックへの確認
	float CheckCollisionBlock_left();

	void CheckCollisionGimmick(int x_, int y_);

	//重力の確認
	void CheckGravity();

	//プレイヤー座標からマップチップへの変更
	void CheckBlock(float posx_, float posy_, int* x_, int* y_);

	void CheckFoot();

	void DeadAnimation();

private:
	InputManager* inputManager = nullptr;
	GameManager* gameManager = nullptr;
	TextureManager* textureManager = nullptr;
	SoundManager* soundManager = nullptr;
	GimmickManager* gimmickManager = nullptr;

	//プレイヤーの座標
	Vec3 pos;

	//プレイヤーのマップチップ上の座標
	Vec2 mapPos;

	//プレイヤー自身の速度
	Vec3 speedVec;

	//プレイヤーの移動量
	Vec3 moveVec;

	Vec3 mobiusPos;

	float gravity = Gravity;

	//立っているか
	bool isStandingGround = false;

	//キーアイテムの所持
	bool haveKeyItem = false;

	int animationCount = 0;
	int animationCount_walk = 0;

	//ギッミク用
	bool isFinishedLuckyHole = false;

	bool gravityDirection = true;

	Vec3 gimmickMove;

	//死んでいるか
	bool isDead = false;

	bool DonotOperation = false;

	float rote;

	int coolTime = 0;

	//debug
	bool debug = false;

};

#endif // !PLAYER_H
