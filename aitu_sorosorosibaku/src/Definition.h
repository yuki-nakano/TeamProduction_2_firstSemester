#ifndef DEFINITION_H
#define DEFINITION_H

#include "DxLib.h"

//画面サイズ
const int Widht = 1920;
const int Height = 1080;

//プレイヤーのサイズ
const int PlayerWidht = 30;
const int PlayerHeight = 60;

//ボスのサイズ
const int BossWidht = 160;
const int BossHeight = 90;

const float JumpPower = 10.0f;	//ジャンプ力
const float Gravity = 0.5f;		//重力
const float MaxSpeed = 6.0f;	//最大速度
const float Speed = 0.5f;		//加速力
const float FrictionForce = 0.2f;//地面との摩擦力

//マップチップの数
const int MapWidht = 64;
const int MapHeight = 36;

//マップチップのサイズ
const int MapChipEdge = 30;

//ステージ数
const int MaxStage = 21;

const int MaxSaveStage = 11;

enum Stage
{
	kRoad,
	kCorridor,
	kClassroom,
	kStairs,
	kDesert,
	kRooftop,
	kSpace,
	kBlack,
};

//ギミックのサイズ
//宝箱
const int GimmickWidht_Chest = 85;
const int GimmickHeight_Chest = 85;
//ドア
const int GimmickWidht_Door = 80;
const int GimmickHeight_Door = 100;

struct Vec3
{
	Vec3() :
		X(0.0f),
		Y(0.0f),
		Z(0.0f)
	{
	}

	Vec3(float x, float y, float z) :
		X(x),
		Y(y),
		Z(z)
	{
	}

	float X;
	float Y;
	float Z;
};

struct Vec2
{
	Vec2() :
		X(0),
		Y(0)
	{
	}

	Vec2(int x, int y) :
		X(x),
		Y(y)
	{
	}

	int X;
	int Y;
};

enum
{
	kNoneBlock,
	kBlock
};

enum Gimmick
{
	kNone,
	kPlayerInitPos,
	kTransparentBlock,
	kBlindBlock,
	kNewsPaperSwitch,
	kDogSwitch,
	kDogInitPos,	
	kRiderSwitch,
	kMineSwitch,
	kWood,
	kSun,
	kSunInitPos,
	kEnergyBulletSwitch,
	kReser,
	kDesk,
	kLightSwitch,
	kThiefSwitch,
	kLight,
	kGum,
	kPen,
	kLuckyHole,
	kNeedle,
	kPushpin,
	kChangeWind,
	kBook,
	kFakeChest,
	kChest_close,
	kKantyou,
	kBlindBack,
	kFakeGool,
	kChaosOperation,
	kGravity,
	kBossBlackHole,
	kDanjiri,
	kReserEndless,
	kUI,
	kMoveBlock,
	kBasketBall,
	kTennisBall,
	kEnemy,
	kDropkick,
	kEraser,
	kGoalTexturePos,
	kKey,
	kRocketTexturePos,
	kRegent,
	kRegentInit,
	kChaosOperationRelease,
	kGtavityRelease,
	kLeftBlindBlock,
	kSunHighSpeed,
	kBossInitPos,
	kEnemyJump,
	kReserInit,
	kKantyouInit,
	kMoveBlockSwitch,
	kFakeLight,
	kBlackHoleSwitch,

	kChest_open,
	kRegentWidth,
	kSpeedBoots,
	kGoal,
	kRocket,

	kGimmickMax
};

enum Direction
{
	kRight, //右向き
	kLeft,	//左向き
};

enum SceneID
{
	//タイトルシーン
	SceneID_Title,
	//ゲームシーン
	SceneID_InGame,
	
	SceneID_Max,
	SceneID_Invalid,	//無効値
};

#endif // !DEFINITION_H
