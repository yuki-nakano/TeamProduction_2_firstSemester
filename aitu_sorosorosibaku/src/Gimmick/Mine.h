#ifndef MINE_H
#define MINE_H

#include "DxLib.h"
#include "GimmickBace.h"

class Mine : public GimmickBace
{
public:
	~Mine();

	bool Exec(float player_posx_, float player_posy_);
	void Draw();

	void Spown(float player_posx_, float player_posy_);

private:
	void AddCount();
	
	bool IsFinished();

private:

	float gimmickWidht = 150;
	float gimmickHeight = 90;

	int count = 0;
	int animationCount = 0;

};



#endif // !MINE_H
