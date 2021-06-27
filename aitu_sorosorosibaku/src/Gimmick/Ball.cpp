#include "Ball.h"

Ball::~Ball()
{
}

bool Ball::Exec(float player_posx_, float player_posy_)
{
	if (!isAlive) { return false; }

//	AddCount();

	Move();

	IsCollidePlayer(player_posx_, player_posy_);
}

void Ball::Draw()
{
	if (!isAlive) { return; }

	DrawBox(pos.X, pos.Y, pos.X + gimmickWidht, pos.Y + gimmickHeight, GetColor(0, 0, 0), FALSE);
}

void Ball::Spown(float player_posx_, float player_posy_)
{
	if (isAlive) { return; }

	isAlive = true;

	pos.Y = player_posy_ - gimmickHeight / 2;
	pos.X = Widht;

//	gameManager->SetIsAliveGimmick(kRugbyBall, false);
}

void Ball::Move()
{
	pos.X += cos(Theta * M_PI / 180) * speed;
	pos.Y += sin(Theta * M_PI / 180) * speed * -1;

	if (pos.X < 0)
	{
		pos.X = 0.1f;

		if (Theta == 180)
		{
			Theta = 0;
		}
		else if (Theta < 180)
		{
			Theta = 180 - Theta;
		}
		else if (Theta > 180)
		{
			Theta = 540 - Theta;
		}
	}
	else if (pos.X + gimmickWidht > Widht)
	{
		pos.X = Widht - (gimmickWidht + 0.1f);

		if (Theta == 0 || Theta == 360)
		{
			Theta = 180;
		}
		else if (Theta < 180)
		{
			Theta = 180 - Theta;
		}
		else if (Theta > 180)
		{
			Theta = 540 - Theta;
		}
	}
	else if (pos.Y < 0)
	{
		pos.Y = 0.1f;

		if (Theta == 90)
		{
			Theta = 270;
		}
		else if (Theta < 90)
		{
			Theta = 360 - Theta;
		}
		else if (Theta > 90)
		{
			Theta = 360 - Theta;
		}
	}
	else if (pos.Y + gimmickWidht > Height)
	{
		pos.Y = Height - (gimmickHeight + 0.1f);

		if (Theta == 270)
		{
			Theta = 90;
		}
		else if (Theta < 270)
		{
			Theta = 360 - Theta;
		}
		else if (Theta > 270)
		{
			Theta = 360 - Theta;
		}
	}
}

void Ball::IsCollidePlayer(float player_posx_, float player_posy_)
{
	if (powf(player_posx_ - (pos.X + gimmickWidht / 2), 2.0f) <= powf((PlayerWidht + gimmickWidht) / 2, 2.0f) &&
		powf(player_posy_ - PlayerHeight / 2 - (pos.Y + gimmickHeight / 2), 2.0f) <= powf((PlayerHeight + gimmickHeight) / 2, 2.0f))
	{
//		gameManager->SetIsColliedGimmick(true);
		isAlive = false;
	}
}


void Ball::CheckCollisionBlock()
{
	float tmpx = moveVec.X;
	float tmpy = moveVec.Y;

	if (moveVec.X < 0)
	{
		tmpx = CheckCollisionBlock_left();
	}
	else if (moveVec.X > 0)
	{
		tmpx = CheckCollisionBlock_right();
	}

	if (moveVec.Y < 0)
	{
		tmpy = CheckCollisionBlock_up();
	}
	else if (moveVec.Y > 0)
	{
		tmpy = CheckCollisionBlock_down();
	}

	moveVec.X = tmpx;
	moveVec.Y = tmpy;
}

float Ball::CheckCollisionBlock_up()
{
	Vec2 tmp1;
	Vec2 tmp2;
	float tmp = moveVec.Y;

	CheckBlock(pos.X, pos.Y + moveVec.Y, &tmp1.X, &tmp1.Y);
	CheckBlock(pos.X + gimmickWidht, pos.Y + moveVec.Y, &tmp2.X, &tmp2.Y);

	for (int i = tmp1.X; i <= tmp2.X; i++)
	{
		switch (gameManager->GetCurrentGimmickMapDate(i, tmp1.Y))
		{
		case kBlock:

			tmp = (moveVec.Y - ((tmp1.Y + 1) * MapChipEdge - pos.Y)) * -1;

			if (Theta == 90)
			{
				Theta = 270;
			}
			else if (Theta < 90)
			{
				Theta = 360 - Theta;
			}
			else if (Theta > 90)
			{
				Theta = 360 - Theta;
			}

			break;
		default:
			break;
		}
	}

	return tmp;
}

float Ball::CheckCollisionBlock_down()
{
	Vec2 tmp1;
	Vec2 tmp2;
	float tmp = moveVec.Y;

	CheckBlock(pos.X, pos.Y + moveVec.Y, &tmp1.X, &tmp1.Y);
	CheckBlock(pos.X + gimmickWidht, pos.Y + moveVec.Y, &tmp2.X, &tmp2.Y);

	for (int i = tmp1.X; i <= tmp2.X; i++)
	{
		switch (gameManager->GetCurrentGimmickMapDate(i, tmp1.Y))
		{
		case kBlock:

			tmp =(moveVec.Y - (tmp1.Y * MapChipEdge - (pos.Y + gimmickHeight))) * -1;

			if (Theta == 270)
			{
				Theta = 90;
			}
			else if (Theta < 270)
			{
				Theta = 360 - Theta;
			}
			else if (Theta > 270)
			{
				Theta = 360 - Theta;
			}

			break;
		default:
			break;
		}
	}

	return tmp;
}

float Ball::CheckCollisionBlock_right()
{
	Vec2 tmp1;
	Vec2 tmp2;
	float tmp = moveVec.X;

	CheckBlock(pos.X + gimmickWidht + moveVec.X, pos.Y, &tmp1.X, &tmp1.Y);
	CheckBlock(pos.X + gimmickWidht + moveVec.X, pos.Y + gimmickHeight, &tmp2.X, &tmp2.Y);

	for (int i = tmp1.Y; i <= tmp2.Y; i++)
	{
		switch (gameManager->GetCurrentGimmickMapDate(tmp1.X, i))
		{
		case kBlock:

			tmp = (moveVec.X - (tmp1.X * MapChipEdge - (pos.X + gimmickWidht))) * -1;

			if (Theta == 0 || Theta == 360)
			{
				Theta = 180;
			}
			else if (Theta < 180)
			{
				Theta = 180 - Theta;
			}
			else if (Theta > 180)
			{
				Theta = 540 - Theta;
			}

			break;
		default:
			break;
		}
	}

	return tmp;
}

float Ball::CheckCollisionBlock_left()
{
	Vec2 tmp1;
	Vec2 tmp2;
	float tmp = moveVec.X;

	CheckBlock(pos.X + moveVec.X, pos.Y - PlayerHeight, &tmp1.X, &tmp1.Y);
	CheckBlock(pos.X + moveVec.X, pos.Y - 1, &tmp2.X, &tmp2.Y);

	for (int i = tmp1.Y; i <= tmp2.Y; i++)
	{
		switch (gameManager->GetCurrentGimmickMapDate(tmp1.X, i))
		{
		case kBlock:

			tmp = (moveVec.X - ((tmp1.X + 1) * MapChipEdge - pos.X)) * -1;

			if (Theta == 180)
			{
				Theta = 0;
			}
			else if (Theta < 180)
			{
				Theta = 180 - Theta;
			}
			else if (Theta > 180)
			{
				Theta = 540 - Theta;
			}

			break;
		default:
			break;
		}

		//if (tmp1.X == -1)
		//{
		//	tmp = (tmp1.X + 1) * MapChipEdge - pos.X + PlayerWidht / 2;
		//	speedVec.X = 0;
		//}
	}

	return tmp;
}

void Ball::CheckBlock(float posx_, float posy_, int* x_, int* y_)
{
	if (posx_ < 0 || posy_ < 0)
	{
		*x_ = -1;
		*y_ = -1;
	}

	for (int y = 0; y < MapHeight; y++)
	{
		for (int x = 0; x < MapWidht; x++)
		{
			if (posx_ >= MapChipEdge * x &&
				posx_ < MapChipEdge * (x + 1) &&
				posy_ >= MapChipEdge * y &&
				posy_ < MapChipEdge * (y + 1))
			{
				*x_ = x;
				*y_ = y;
			}
		}
	}
}

