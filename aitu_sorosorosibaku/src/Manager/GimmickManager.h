#ifndef GIMMICK_MANAGER_H
#define GIMMICK_MANAGER_H

#include "DxLib.h"
#include "../Definition.h"
#include "../Singleton.h"
#include "GameManager.h"

#include "../Gimmick/NewsPaper.h"
//#include "../Gimmick/Dog.h"
#include "../Gimmick/Ridder.h"
#include "../Gimmick/Mine.h"
#include "../Gimmick/Wood.h"
#include "../Gimmick/Sun.h"
#include "../Gimmick/EnergyBullet.h"
#include "../Gimmick/Desk.h"
#include "../Gimmick/Thief.h"

class GimmickManager : public Singleton<GimmickManager>
{
public:
	GimmickManager();
	~GimmickManager();

	void Exec(float player_pos_x_, float player_pos_y_);
	void Draw();

	void SpawnGimmick(Gimmick gimmick_, float player_pos_x_, float player_pos_y_);

	void DeadGimmick();

	bool GetIsAliveGimmick(Gimmick gimmick_) const { return isAliveGimmick[gimmick_]; }
	void SetIsAliveGimmick(Gimmick gimmick_, bool is_alive_) { isAliveGimmick[gimmick_] = is_alive_; }

private:
	GameManager* gameManager = nullptr;

	bool isAliveGimmick[kGimmickMax];

	GimmickBace* gimmick[kGimmickMax] =
	{
		nullptr,
		nullptr,//プレイヤー初期値
		nullptr,//透ける足場
		nullptr,//孔明
		new NewsPaper,//新聞紙
		nullptr,//new Dog,//犬
		nullptr,//犬初期値
		new Ridder,//暴走族
		new Mine,//地雷
		nullptr,//new Wood,//木
		new Sun,//太陽
		nullptr,//太陽初期値
		new EnergyBullet,//エネルギー弾
		nullptr,//new Laser,//レーザービーム
		new Desk,//机
		nullptr,//蛍光灯
		new Thief,
		nullptr,//new Light,
		nullptr,//new Gum,
		nullptr,//new Pen,
		nullptr,
		nullptr,
		nullptr,
		nullptr,//new ChangeWind,
		nullptr,//new Book,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		nullptr,//new ChosOperation,
		nullptr,//new Gravity,
		nullptr,//new BlackHole,

		
	};
};

#endif // !GIMMICK_MANAGER_H
