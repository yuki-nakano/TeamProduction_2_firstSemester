#include "SoundManager.h"

void SoundManager::LoadSounds()
{
	for (int i = 0; i < (int)Sound::kSoundMax; i++)
	{
		soundDate[i] = LoadSoundMem(pass[i]);
		ChangeVolumeSoundMem(255 * VolumePer / 100, soundDate[i]);
	}
}

void SoundManager::DeleteSounds()
{

	for (int i = 0; i < (int)Sound::kSoundMax; i++)
	{
		DeleteSoundMem(soundDate[i]);
	}
}

int SoundManager::GetSoundData(Sound num)
{
	return soundDate[(int)num];
}

void SoundManager::ChangeBGM(Sound sound_date_)
{
	if (currentBGM == Sound::kInvalid || currentBGM == sound_date_) { return; }

	StopSoundMem(soundDate[(int)currentBGM]);
	PlaySoundMem(soundDate[(int)sound_date_], DX_PLAYTYPE_LOOP);
	currentBGM = sound_date_;
}

void SoundManager::StartBGM(Sound sound_date_)
{
	currentBGM = sound_date_;

	PlaySoundMem(soundDate[(int)sound_date_], DX_PLAYTYPE_LOOP);
}

void SoundManager::StopBGM()
{
	StopSoundMem(soundDate[(int)currentBGM]);

	//currentBGM = Sound::kInvalid;
}

void SoundManager::ReStartBGM()
{
	if (currentBGM == Sound::kInvalid) { return; }

	PlaySoundMem(soundDate[(int)currentBGM], DX_PLAYTYPE_LOOP, FALSE);
}
