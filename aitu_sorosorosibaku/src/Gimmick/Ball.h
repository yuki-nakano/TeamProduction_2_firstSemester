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

	//�u���b�N�ւ̂߂荞�݊m�F
	void CheckCollisionBlock();
	//�㑤�̃u���b�N�ւ̊m�F
	float CheckCollisionBlock_up();
	//�����̃u���b�N�ւ̊m�F
	float CheckCollisionBlock_down();
	//�E���̃u���b�N�ւ̊m�F
	float CheckCollisionBlock_right();
	//�����̃u���b�N�ւ̊m�F
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
