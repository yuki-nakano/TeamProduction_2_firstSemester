#include "GameManager.h"

GameManager::GameManager()
{
	for (int i = 0; i < MaxStage; i++)
	{
		isChangeStage_front[i] = true;
		isChangeStage_back[i] = true;

		SunInitPos[i].X = -1000;
		SunInitPos[i].Y = -1000;
	}

	for (int i = 0; i < MaxStage; i++)
	{
		std::stringstream ss;
		ss << "res/MapDate/MapDate" << std::setfill('0') << std::setw(2) << std::right << std::to_string(i + 1) << ".txt";
		FileInput(i, ss.str().c_str());
	}

	isChangeStage_back[0] = false;
	isChangeStage_back[MaxStage - 1] = false;

	DateFileInput();
}

GameManager::~GameManager()
{
	DateFileOutput();
}

void GameManager::SetStage(int stage_num_)
{
	stageNum = stage_num_;

	for (int y = 0; y < MapHeight; y++)
	{
		for (int x = 0; x < MapWidht; x++)
		{
			currentGimmickMapDate[y][x] = gimmickMapDate[stage_num_][y][x];
			currentBlockMapDate[y][x] = blockMapDate[stage_num_][y][x];
		}
	}
}

void GameManager::ReSetStage()
{
	for (int y = 0; y < MapHeight; y++)
	{
		for (int x = 0; x < MapWidht; x++)
		{
			currentGimmickMapDate[y][x] = gimmickMapDate[stageNum][y][x];
			currentBlockMapDate[y][x] = blockMapDate[stageNum][y][x];
		}
	}
}

void GameManager::FileInput(int stage_num_, const char* pass_)
{
	FILE* fp;
	fopen_s(&fp, pass_, "rb");
	if (fp == NULL)
	{
		return;
	}

	const int row = MapWidht * 6;
	char tmpLines[row];
	int count_x = 0;
	int count_y = 0;
	while (fgets(tmpLines, row, fp) != NULL)
	{
		for (int i = 0; i < row; i++)
		{
			if (tmpLines[i] == '\0')
			{
				count_y++;
				count_x = 0;
				break;
			}
			else if (tmpLines[i] == ',')
			{
				count_x++;
			}
			else if (tmpLines[i] >= '0' && tmpLines[i] <= '9')
			{
				blockMapDate[stage_num_][count_y][count_x] = (tmpLines[i] - '0');

				i++;

				int gimmmickDate = 0;

				gimmmickDate = (tmpLines[i] - '0') * 100;

				i++;

				gimmmickDate += (tmpLines[i] - '0') * 10;

				i++;

				gimmmickDate += tmpLines[i] - '0';

				gimmickMapDate[stage_num_][count_y][count_x] = (Gimmick)gimmmickDate;

				switch (gimmickMapDate[stage_num_][count_y][count_x])
				{
				case kPlayerInitPos:
					playerInitPos[stage_num_].X = (count_x * MapChipEdge) + PlayerWidht / 2;
					playerInitPos[stage_num_].Y = (count_y * MapChipEdge) + 1;

					gimmickMapDate[stage_num_][count_y][count_y] = kNone;
					break;
				case kGoalTexturePos:
					isChangeStage_front[stage_num_] = false;
					isChangeStage_back[stage_num_ + 1] = false;

					break;
				case kSunInitPos:
					SunInitPos[stage_num_].X = count_x;
					SunInitPos[stage_num_].Y = count_y;
					break;
				case kBossInitPos:
					BossInitPos.X = count_x;
					BossInitPos.Y = count_y;

					break;
				default:
					break;
				}
			}
		}
	}

	fclose(fp);

}

void GameManager::DateFileInput()
{
	FILE* fp;
	fopen_s(&fp, "res/date.txt", "rb");
	if (fp == NULL)
	{
		return;
	}

	const int row = MaxSaveStage * 3;
	char tmpLines[row];
	int count_x = 0;
	int count_y = 0;
	while (fgets(tmpLines, row, fp) != NULL)
	{
		switch (count_y)
		{
		case 0:
			for (int i = 0; i < MaxSaveStage; i++)
			{

				if (tmpLines[count_x] >= '0' && tmpLines[count_x] <= '9')
				{
					switch (tmpLines[count_x])
					{
					case '0':
						CanUseSaveStage[i] = false;
						break;
					case '1':
						CanUseSaveStage[i] = true;
						break;
					default:
						break;
					}

					count_x++;
				}

				if (tmpLines[count_x] == ',')
				{
					count_x++;
				}
			}

			count_y++;
			break;
		case 1:
			switch (tmpLines[0])
			{
			case '0':
				clearedGame = false;
				break;
			case '1':
				clearedGame = true;
				break;
			default:
				break;
			}

			count_y++;
			break;
		}
	}
	
	fclose(fp);
}

void GameManager::DateFileOutput()
{
	std::ofstream ofs("res/date.txt");

	for (int i = 0; i < MaxSaveStage; i++)
	{
		switch (CanUseSaveStage[i])
		{
		case true:
			ofs << "1";
			break;
		case false:
			ofs << "0";
			break;
		}
		
		ofs << ",";
	}

	ofs << std::endl;

	switch (clearedGame)
	{
	case true:
		ofs << 1;
		break;
	case false:
		ofs << 0;
		break;
	}

	ofs << ",";
}
