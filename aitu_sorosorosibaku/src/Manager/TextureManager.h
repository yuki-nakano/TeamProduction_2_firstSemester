#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "DxLib.h"
#include "../Definition.h"
#include "../Singleton.h"

enum class TextureDate
{
	//SceneID_Title
	kTitleLogo,
	kTitleBack,
	kTitleStart,

	//SceneID_InGame
	kPlayerWalkRight_01,
	kPlayerWalkRight_02,
	kPlayerWalkLeft_01,
	kPlayerWalkLeft_02,
	kPlayerJumpRight,
	kPlayerJumpLeft,
	kPlayerWait,

	kMobius,

	kBackGround_01,	//背景
	kBackGround_02,
	kBackGround_03,
	kBackGround_04,
	kBackGround_05,
	kBackGround_06,
	kBackGround_07,
	kBackGround_08,
	kBackGround_09,
	kBackGround_10,
	kBackGround_11,
	kBackGround_12,

	kMapChip_Block_Texture,

	kPause,
	kPauseBackGround,
	kFastTravelTitle,
	kFastTravelIcon_road,
	kFastTravelIcon_corridor,
	kFastTravelIcon_classroom,
	kFastTravelIcon_stairs,
	kFastTravelIcon_desert,
	kFastTravelIcon_rooftop,
	kFastTravelIcon_space,
	kFastTravelIcon_black,

	kKey_Texture,
	kGool_Texture,

	kNewsPaper_Texture,

	kWood_Animation_1,	//ギミック　木
	kWood_Animation_2,
	kWood_Animation_3,
	kWood_Animation_4,
	kWood_Animation_5,
	kWood_Animation_6,

	kEnergyBullet_up,		//ギミック　エネルギー弾
	kEnergyBullet_down,
	kEnergyBullet_right,
	kEnergyBullet_left,

	kRider_Texture_1,	//ギミック　暴走族
	kRider_Texture_2,
	kRider_Texture_3,

	kDog_Texture_1,		//ギミック　犬
	kDog_Texture_2,
	kDog_Texture_3,
	kDog_Texture_4,

	kSun_Texture,	//ギミック　太陽

	kMine_Texture_1,	//ギミック　地雷
	kMine_Texture_2,
	kMine_Texture_3,
	kMine_Texture_4,
	kMine_Texture_5,
	kMine_Texture_6,
	kMine_Texture_7,
	kMine_Texture_8,

	kChest_open,	//ギミック　宝箱
	kChest_close,

	kDesk,		//ギミック　机
	kTeacher,

	kBlackHoke1,	//ギミック　ブラックホール
	kBlackHoke2,
	kBlackHoke3,

	kRocket_wait,	//ギミック　ロケット
	kRocket_firing,
	kRocket_fly,

	kNeedle,	//ギミック　針

	kPushPin,	//ギミック　画鋲

	kThief_1,
	kThief_2,

	kFloatEnemyRight_1,
	kFloatEnemyRight_2,
	kFloatEnemyLeft_1,
	kFloatEnemyLeft_2,

	kBossWalkRight_01,	//ボスキャラ
	kBossWalkRight_02,
	kBossWalkLeft_01,
	kBossWalkLeft_02,
	kBossWait,
	kBossHpGauge,
	kBossHp,

	kLeser,

	kBossDialogueAppearance,	//ボスセリフ
	kBossDialogueLaser,
	kBossDialogueMetor,
	kBossDialogueDog,
	kBossDialogueBlackHole,
	kBossDialogueFinish,

	kResult_clear,		//リザルト
	kResult_lose,
	kResult_button,

	kTextureMax
};

class TextureManager : public Singleton<TextureManager>
{
public:
	//テクスチャデータの初期化
	void LoadTextures();

	//テクスチャデータの削除
	void DeleteTextures();

	//テクスチャデータの取得
	int GetTextureDate(TextureDate num);

private:
	int textureDate[(int)TextureDate::kTextureMax];

	//ファイルパス
	char pass[(int)TextureDate::kTextureMax][100] =
	{
		"res/Title/title_logo.png",
		"res/Title/title_back.png",
		"res/Title/title_start.png",

		"res/InGame/Player/hero_walk_right1.png",
		"res/InGame/Player/hero_walk_right2.png",
		"res/InGame/Player/hero_walk_left1.png",
		"res/InGame/Player/hero_walk_left2.png",
		"res/InGame/Player/hero_jump_right.png",
		"res/InGame/Player/hero_jump_left.png",
		"res/InGame/Player/hero_wait.png",

		"res/InGame/Player/mobius.png",

		"res/InGame/BackGround/stage_back1.png",
		"res/InGame/BackGround/stage_back2.png",
		"res/InGame/BackGround/stage_back3.png",
		"res/InGame/BackGround/stage_back4.png",
		"res/InGame/BackGround/stage_back5.png",
		"res/InGame/BackGround/stage_back6.png",
		"res/InGame/BackGround/stage_back7.png",
		"res/InGame/BackGround/stage_back8.png",
		"res/InGame/BackGround/stage_back9.png",
		"res/InGame/BackGround/stage_back10.png",
		"res/InGame/BackGround/stage_back11.png",
		"res/InGame/BackGround/stage_back12.png",

		"res/InGame/mapcip.png",

		"res/Pause/pause.png",
		"res/Pause/back_ground.png",
		"res/Pause/fast_travel.png",
		"res/Pause/travel_通学路.png",
		"res/Pause/travel_廊下.png",
		"res/Pause/travel_教室.png",
		"res/Pause/travel_踊り場.png",
		"res/Pause/travel_砂漠.png",
		"res/Pause/travel_屋上.png",
		"res/Pause/travel_宇宙.png",
		"res/Pause/travel_black.png",

		"res/InGame/key.png",

		"res/InGame/door.png",

		"res/InGame/p_01.png",

		"res/InGame/Gimmick/Wood/tree_down1.png",
		"res/InGame/Gimmick/Wood/tree_down2.png",
		"res/InGame/Gimmick/Wood/tree_down3.png",
		"res/InGame/Gimmick/Wood/tree_down4.png",
		"res/InGame/Gimmick/Wood/tree_down5.png",
		"res/InGame/Gimmick/Wood/tree_down6.png",

		"res/InGame/Gimmick/EnergyBullet/energybullet_up.png",
		"res/InGame/Gimmick/EnergyBullet/energybullet_down.png",
		"res/InGame/Gimmick/EnergyBullet/energybullet_right.png",
		"res/InGame/Gimmick/EnergyBullet/energybullet_left.png",

		"res/InGame/Gimmick/Rider/gang1.png",
		"res/InGame/Gimmick/Rider/gang2.png",
		"res/InGame/Gimmick/Rider/gang3.png",

		"res/InGame/Gimmick/Dog/dog_run1.png",
		"res/InGame/Gimmick/Dog/dog_run2.png",
		"res/InGame/Gimmick/Dog/dog_run3.png",
		"res/InGame/Gimmick/Dog/dog_run4.png",

		"res/InGame/Gimmick/Sun/sun.png",

		"res/InGame/Gimmick/Mine/explosion1.png",
		"res/InGame/Gimmick/Mine/explosion2.png",
		"res/InGame/Gimmick/Mine/explosion3.png",
		"res/InGame/Gimmick/Mine/explosion4.png",
		"res/InGame/Gimmick/Mine/explosion5.png",
		"res/InGame/Gimmick/Mine/explosion6.png",
		"res/InGame/Gimmick/Mine/explosion7.png",
		"res/InGame/Gimmick/Mine/explosion8.png",

		"res/InGame/Gimmick/Chest/chest_close.png",
		"res/InGame/Gimmick/Chest/chest_open.png",

		"res/InGame/Gimmick/Desk/desk.png",
		"res/InGame/Gimmick/Desk/teacher.png",

		"res/InGame/Gimmick/BlackHole/black1.png",
		"res/InGame/Gimmick/BlackHole/black2.png",
		"res/InGame/Gimmick/BlackHole/black3.png",

		"res/InGame/Gimmick/Rocket/rocket1.png",
		"res/InGame/Gimmick/Rocket/rocket2.png",
		"res/InGame/Gimmick/Rocket/rocket3.png",

		"res/InGame/Gimmick/Needle/needle.png",

		"res/InGame/Gimmick/PushPin/push_pin.png",

		"res/InGame/Gimmick/Thief/thief_run_left1.png",
		"res/InGame/Gimmick/Thief/thief_run_left2.png",

		"res/InGame/Gimmick/FloatEnemy/zako_walk_right1.png",
		"res/InGame/Gimmick/FloatEnemy/zako_walk_right2.png",
		"res/InGame/Gimmick/FloatEnemy/zako_walk_Left1.png",
		"res/InGame/Gimmick/FloatEnemy/zako_walk_Left2.png",

		"res/InGame/Boss/boss_walk_right1.png",
		"res/InGame/Boss/boss_walk_right2.png",
		"res/InGame/Boss/boss_walk_left1.png",
		"res/InGame/Boss/boss_walk_left2.png",
		"res/InGame/Boss/boss_wait.png",
		"res/InGame/Boss/boss_HP01.png",
		"res/InGame/Boss/boss_HP02.png",

		"res/InGame/Gimmick/Laser/laser_beam.png",

		"res/Ingame/Gimmick/UI/serihu_01.png",
		"res/Ingame/Gimmick/UI/serihu_02.png",
		"res/Ingame/Gimmick/UI/serihu_03.png",
		"res/Ingame/Gimmick/UI/serihu_04.png",
		"res/Ingame/Gimmick/UI/serihu_05.png",
		"res/Ingame/Gimmick/UI/serihu_06.png",

		"res/InGame/Result/result_clear.png",
		"res/InGame/Result/result_lose.png",
		"res/InGame/Result/results_title.png",
	};
};

#endif // !TEXTURE_MANAGER_H
