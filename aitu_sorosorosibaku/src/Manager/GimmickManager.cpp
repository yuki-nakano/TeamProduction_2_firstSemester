#include "GimmickManager.h"

GimmickManager::GimmickManager()
{
	gameManager = GameManager::GetInstance();

	for (int i = 0; i < kGimmickMax; i++)
	{
		isAliveGimmick[i] = false;
	}
}

GimmickManager::~GimmickManager()
{
	for (int i = 0; i < kGimmickMax; i++)
	{
		delete gimmick[i];
	}
}

void GimmickManager::Exec(float player_pos_x_, float player_pos_y_)
{
	for (int i = 0; i < kGimmickMax; i++)
	{
		if (gimmick[i] == nullptr) { continue; }
		if (!gimmick[i]->Exec(player_pos_x_, player_pos_y_))
		{
			isAliveGimmick[i] = false;
		}
	}
}

void GimmickManager::Draw()
{
	for (int i = 0; i < kGimmickMax; i++)
	{
		if (gimmick[i] == nullptr) { continue; }
		gimmick[i]->Draw();
	}
}

void GimmickManager::SpawnGimmick(Gimmick gimmick_, float player_pos_x_, float player_pos_y_)
{
	if (gimmick[gimmick_] == nullptr) { return; }
	gimmick[gimmick_]->Spown(player_pos_x_, player_pos_y_);
}

void GimmickManager::DeadGimmick()
{
	for (int i = 0; i < kGimmickMax; i++)
	{
		if (gimmick[i] == nullptr) { continue; }
		gimmick[i]->SetIsAlive(false);
	}
}
