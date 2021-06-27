#ifndef BALL_H
#define BALL_H

#include "DxLib.h"
#include "GimmickBace.h"

class Ball : public GimmickBace
{
public:
	~Ball();

	bool Exec(float player_posx_, float player_posy_);
	void Draw();

	void Spown(float player_posx_, float player_posy_);

private:
	void Move();

	void IsCollidePlayer(float player_posx_, float player_posy_);

	//ブロックへのめり込み確認
	void CheckCollisionBlock();
	//上側のブロックへの確認
	float CheckCollisionBlock_up();
	//下側のブロックへの確認
	float CheckCollisionBlock_down();
	//右側のブロックへの確認
	float CheckCollisionBlock_right();
	//左側のブロックへの確認
	float CheckCollisionBlock_left();

	void CheckBlock(float posx_, float posy_, int* x_, int* y_);

private:
	Vec3 moveVec;

	int speed = MaxSpeed * 2;

	float gimmickWidht = 180;
	float gimmickHeight = 140;

	float Theta;
};



#endif // !BALL_H
