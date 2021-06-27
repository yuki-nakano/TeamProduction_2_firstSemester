#ifndef NEWS_PAPER_H
#define NEWS_PAPER_H

#include "DxLib.h"
#include "GimmickBace.h"

class NewsPaper : public GimmickBace
{
public:
	~NewsPaper();

	bool Exec(float player_posx_, float player_posy_);
	void Draw();

	void Spown(float player_posx_, float player_posy_);

private:
	bool IsFinished();

private:
	int countDown = 0;
};

#endif // !NEWS_PAPER_H
