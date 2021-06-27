#ifndef SUN_H
#define SUN_H

#include "DxLib.h"
#include "GimmickBace.h"

class Sun : public GimmickBace
{
public:
	Sun();
	~Sun();

	bool Exec(float player_posx_, float player_posy_);
	void Draw();

	void Spown(float player_posx_, float player_posy_);

private:
	bool IsFinished();

	void Move(float player_posx_, float player_posy_);

	void IsCollidePlayer(float player_posx_, float player_posy_);

	void Calculate(float posx_, float posy_);

private:
	int speed = MaxSpeed / 2;

	float gimmickWidht = 640;
	float gimmickHeight = 640;

	float collisionWidht = 387;
	float collisionHwight = 387;

	float distanceX = 0;
	float distanceY = 0;
	double atanTheta = 0;

	double theta = 0;
	//1フレームで回転できる角度の最大値
	double thetaSpeed = 10;
};



#endif // !SUN_H
