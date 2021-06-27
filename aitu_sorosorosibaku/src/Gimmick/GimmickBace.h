#ifndef GIMMICK_BASE_H
#define GIMMICK_BASE_H

#include "../Manager/TextureManager.h"
#include "../Manager/GameManager.h"
#include "../Definition.h"

#define _USE_MATH_DEFINES
#include <math.h>

class GimmickBace
{
public:
	GimmickBace();
	virtual ~GimmickBace();

	virtual bool Exec(float player_posx_, float player_posy_) = 0;
	virtual void Draw() = 0;

	virtual void SetIsAlive(bool is_alive_) { isAlive = is_alive_; }
	
	virtual void Spown(float player_posx_, float player_posy_) = 0;

protected:
	virtual bool IsFinished() = 0;

protected:
	TextureManager* textureManager = nullptr;
	GameManager* gameManager = nullptr;

	float gimmickWidht;
	float gimmickHeight;

	Vec3 pos;

	bool isAlive = false;
};

#endif // !GIMMICK_BASE_H
