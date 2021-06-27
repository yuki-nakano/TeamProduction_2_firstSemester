#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "DxLib.h"
#include "../Definition.h"
#include "../Singleton.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

//シーン間での値の保存
class GameManager : public Singleton<GameManager>
{
public:
	GameManager();
	~GameManager();

	float GetPlayerInitPosX(int stage_num_) const { return playerInitPos[stage_num_].X; }
	float GetPlayerInitPosY(int stage_num_) const { return playerInitPos[stage_num_].Y; }

	Vec2 GetSunInitPos() const { return SunInitPos[stageNum]; }

	Gimmick GetCurrentGimmickMapDate(int x_, int y_) const { return currentGimmickMapDate[y_][x_]; }
	void SetCurrentGimmickMapDate(int x_, int y_, Gimmick stage_date_) { currentGimmickMapDate[y_][x_] = stage_date_; }

	int GetCurrentBlockMapDate(int x_, int y_) const { return currentBlockMapDate[y_][x_]; }
	void SetCurrentBlockMapDate(int x_, int y_, int stage_date_) { currentBlockMapDate[y_][x_] = stage_date_; }

	bool GetIsCollide() const { return isCollide; }
	void SetIsCollide(bool is_collide_) { isCollide = is_collide_; }

	bool GetIsCollideThief() const { return isCollideThief; }
	void SetIsCollideThief(bool is_collide_thief_) { isCollideThief = is_collide_thief_; }

	int GetStageNum() const { return stageNum; }
	void SetStage(int stage_num_);

	void SetIsClear(bool is_clear_) { isClear = is_clear_; }
	bool GetIsClear() const { return isClear; }

	int GetIsChangeStageFront()const { return isChangeStage_front[stageNum]; }
	int GetIsChangeStageBack()const { return isChangeStage_back[stageNum]; }

	void SetPlayerPos(Vec3 player_pos) { playerPos.X = player_pos.X; playerPos.Y, player_pos.Y; }
	Vec3 GetPlayerPos() const { return playerPos; }

	Vec2 GetBossInitPos()const { return BossInitPos; }

	void ReSetStage();

	void SetFinishGame(bool finish_game) { finishGame = finish_game; }
	bool GetFinishGame() const { return finishGame; }

	void SetClearedhGame(bool cleared_game) { clearedGame = cleared_game; }
	bool GetClearedGame() const { return finishGame; }

	int GetSaveStageBackGround(int num_) const { return SaveStageBackGround[num_]; }

	int GetSaveStageNum(int num_) const { return SaveStageNum[num_]; }

	void SetCanUseSaveStage(int num_, bool can_use_save_stage_) { CanUseSaveStage[num_] = can_use_save_stage_; }
	bool GetCanUsedSaveStage(int num_) const { return CanUseSaveStage[num_]; }

private:
	//ファイルの読み込み
	void FileInput(int stage_num_, const char* pass_);
	void DateFileInput();

	//ファイル書き込み
	void DateFileOutput();

private:
	//ギミックのデータ保存
	Gimmick gimmickMapDate[MaxStage][MapHeight][MapWidht];
	//現在のステージのギミックデータ
	Gimmick currentGimmickMapDate[MapHeight][MapWidht];

	//ブロックテータの保存
	int blockMapDate[MaxStage][MapHeight][MapWidht];
	//現在のステージのブロックデータ
	int currentBlockMapDate[MapHeight][MapWidht];

	//プレイヤーとギミックとの接触
	bool isCollide = false;
	bool isCollideThief = false;

	//現在のステージ番号
	int stageNum = 0;

	//ステージごとのプレイヤー初期値
	Vec3 playerInitPos[MaxStage];

	//ステージごとのギミック初期値
	Vec2 SunInitPos[MaxStage];
	Vec2 BossInitPos;

	//ゲームクリア判定
	bool isClear = false;

	//画面端でステージ移動可能かの判定
	bool isChangeStage_front[MaxStage];
	bool isChangeStage_back[MaxStage];

	Vec3 playerPos;

	//ゲーム終了判定フラグ
	bool finishGame = false;;

	//ゲームをクリアしているか判定フラグ
	bool clearedGame = false;

	int SaveStageBackGround[MaxSaveStage] =
	{
		kRoad,kCorridor,kClassroom,kCorridor,kStairs,kCorridor,
		kDesert,kCorridor,kStairs,kRooftop,kSpace,
	};

	//ファストトラベル可能ステージ番号
	int SaveStageNum[MaxSaveStage] = { 0,3,5,7,9,10,12,14,16,17,19 };
	bool CanUseSaveStage[MaxSaveStage];
};

#endif // !GAME_MANAGER_H
