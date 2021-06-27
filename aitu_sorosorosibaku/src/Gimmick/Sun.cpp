#include "Sun.h"

Sun::Sun()
{
	textureManager = TextureManager::GetInstance();
	gameManager = GameManager::GetInstance();

	pos.X = -1000;
	pos.Y = -1000;
}

Sun::~Sun()
{
}

bool Sun::Exec(float player_posx_, float player_posy_)
{
	if (!isAlive) { return false; }

	Move(player_posx_, player_posy_);

	IsCollidePlayer(player_posx_, player_posy_);

	return true;
}

void Sun::Draw()
{
	if (!isAlive) { return; }

	DrawGraph(pos.X - gimmickWidht / 2, pos.Y - gimmickHeight / 2, textureManager->GetTextureDate(TextureDate::kSun_Texture), TRUE);
}

void Sun::Spown(float player_posx_, float player_posy_)
{
	if (gameManager->GetSunInitPos().X == -1000) { return; }

	pos.X = (gameManager->GetSunInitPos().X + 0.5f) * MapChipEdge;
	pos.Y = (gameManager->GetSunInitPos().Y + 0.5f) * MapChipEdge;
}

void Sun::Calculate(float posx_, float posy_)
{
	distanceX = posx_ - pos.X;
	distanceY = (posy_ - pos.Y) * -1;
	atanTheta = atan2(distanceY, distanceX) * 180 / M_PI;

	if (atanTheta < 0)
	{
		atanTheta += 360.0f;
	}
}

bool Sun::IsFinished()
{
	return false;
}

void Sun::Move(float player_posx_, float player_posy_)
{
	if (theta > 360.0f)
	{
		theta -= 360.0f;
	}

	if (theta < 0.0f)
	{
		theta += 360.0f;
	}

	Calculate(player_posx_, player_posy_);

	if (sqrt(pow(atanTheta - theta, 2.0f)) <= thetaSpeed &&
		sqrt(pow(atanTheta - theta, 2.0f)) >= 0.0f ||
		sqrt(pow(atanTheta - theta, 2.0f)) <= 360.0f &&
		sqrt(pow(atanTheta - theta, 2.0f)) >= 360.0f - thetaSpeed)
	{
		theta = atanTheta;
	}
	else if (atanTheta - theta > thetaSpeed &&
		atanTheta - theta < 180.0f ||
		atanTheta - theta <= -180.0f &&
		atanTheta - theta > -360.0f + thetaSpeed)
	{
		theta += thetaSpeed;
	}
	else if (atanTheta - theta < thetaSpeed &&
		atanTheta - theta > -180.0f ||
		atanTheta - theta >= 180.0f &&
		atanTheta - theta < 360.0f - thetaSpeed)
	{
		theta -= thetaSpeed;
	}

	pos.X += cos(theta / 180.0f * M_PI) * speed;
	pos.Y -= sin(theta / 180.0f * M_PI) * speed;
}

void Sun::IsCollidePlayer(float player_posx_, float player_posy_)
{
	if (powf(player_posx_ - (pos.X), 2.0f) <= powf((PlayerWidht + collisionWidht) / 2, 2.0f) &&
		powf(player_posy_ - PlayerHeight / 2 - (pos.Y), 2.0f) <= powf((PlayerHeight + collisionWidht) / 2, 2.0f))
	{
		gameManager->SetIsCollide(true);
		isAlive = false;
	}
}
