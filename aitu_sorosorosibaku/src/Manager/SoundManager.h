#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "DxLib.h"
#include "../Definition.h"
#include "../Singleton.h"

enum class Sound
{
	//BGM
	kTitle,

	kStageBGM1,
	kStageBGM2,
	kStageBGM3,
	kStageBGM4,
	kStageBGM5,
	kStageBGM6,
	kStageBGM7,

	kBossBGM,

	kClear,
	kLose,

	//ギッミク
	kBoss,
	kMine,
	kRider,
	kDog,
	kPen,
	kFakeChest,
	kWood,
	kEraser,
	kChangeWind,
	kGum,

	//プレイヤー


	kSoundMax,
	kInvalid,
};

class SoundManager : public Singleton<SoundManager>
{
public:
	//サウンドデータの初期化
	void LoadSounds();

	//サウンドデータの削除
	void DeleteSounds();

	//サウンドデータの取得
	int GetSoundData(Sound num);

	//BGMの変更
	void ChangeBGM(Sound sound_date_);

	//BGMの再生
	void StartBGM(Sound sound_date_);

	//BGMの停止
	void StopBGM();

	//BGMの途中から再生
	void ReStartBGM();

private:
	int soundDate[(int)Sound::kSoundMax];
	int VolumePer = 10;

	//現在のBGMの保存
	Sound currentBGM = Sound::kInvalid;

	//ファイルパス
	char pass[(int)Sound::kSoundMax][100] =
	{
		"res/sound/BGM/title_bgm.mp3",
		"res/sound/BGM/stage_bgm1.mp3",
		"res/sound/BGM/stage_bgm2.mp3",
		"res/sound/BGM/stage_bgm3.mp3",
		"res/sound/BGM/stage_bgm4.mp3",
		"res/sound/BGM/stage_bgm5.mp3",
		"res/sound/BGM/stage_bgm6.mp3",
		"res/sound/BGM/stage_bgm7.mp3",
		"res/sound/BGM/boss_bgm.mp3",
		"res/sound/BGM/clear_bgm.mp3",
		"res/sound/BGM/lose_bgm.mp3",
		"res/sound/Gimmick/guaaa.mp3",
		"res/sound/bakuhatu01.mp3",
		"res/sound/bousou01.mp3",
		"res/sound/dog01.mp3",
		"res/sound/flash-of-light-3.mp3",
		"res/sound/Hit09-1.mp3",
		"res/sound/ki01.mp3",
		"res/sound/sliding-door02.mp3",
		"res/sound/wind02.mp3",
		"res/sound/泥・ぬかるみ.mp3",
	};

};

#endif // !SOUNDMANAGER_H
