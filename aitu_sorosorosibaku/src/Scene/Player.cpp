#include "Player.h"

Player::Player()
{
	inputManager = InputManager::GetInstance();
	gameManager = GameManager::GetInstance();
	textureManager = TextureManager::GetInstance();
	soundManager = SoundManager::GetInstance();
	gimmickManager = GimmickManager::GetInstance();

	isDead = false;
}

Player::~Player()
{
}

void Player::Exec()
{
	//if (inputManager->IsKeyPushed(KEY_INPUT_E))
	//{
	//	debug ? debug = false : debug = true;
	//}
	//if (debug)
	//{
	//	if(inputManager->IsKeyHeld(RightMoveKey))
	//	{
	//		pos.X += 30.0f;
	//	}
	//	if (inputManager->IsKeyHeld(LeftMoveKey))
	//	{
	//		pos.X -= 10.0f;
	//	}
	//	if (inputManager->IsKeyHeld(KEY_INPUT_S))
	//	{
	//		pos.Y += 10.0f;
	//	}
	//	if (inputManager->IsKeyHeld(KEY_INPUT_W))
	//	{
	//		pos.Y -= 10.0f;
	//	}
	//	return;
	//}

	animationCount++;
	if (animationCount % 10 == 0)
	{
		animationCount_walk++;
	}

	if (isDead)
	{
		DeadAnimation();

		speedVec.Y += gravity;

		pos.Y += speedVec.Y;

		return;
	}

	if (!DonotOperation)
	{
		Move();

		if (isStandingGround)
		{
			Friction();
		}
		else
		{
			speedVec.Y += gravity;
		}

		Jump();

		Reset();

		Search();
	}

	ChangePos();

	if (gameManager->GetIsCollideThief())
	{
		haveKeyItem = false;
		gameManager->SetIsCollideThief(false);
	}

	if (gameManager->GetIsCollide() ||
		pos.Y > Height + PlayerHeight || 
		pos.Y < 0)
	{
		gravity = Gravity;
		gravityDirection = true;

		gameManager->SetIsCollide(false);
		isDead = true;

		soundManager->StopBGM();

		speedVec.Y = JumpPower * -3;
	}
}

void Player::Draw()
{
	if (isDead)
	{
		DrawRotaGraph2(pos.X, pos.Y - PlayerHeight / 2, 15, 30, 1.0f, rote, textureManager->GetTextureDate(TextureDate::kPlayerWait), TRUE, FALSE);

		return;
	}

	if (coolTime == 0)
	{
		DrawGraph(pos.X - 30, pos.Y - 60, textureManager->GetTextureDate(TextureDate::kMobius), TRUE);
	}
	else if (coolTime > 150)
	{
		DrawGraph(mobiusPos.X - 30, mobiusPos.Y - 60, textureManager->GetTextureDate(TextureDate::kMobius), TRUE);
	}

	if (isStandingGround)
	{
		if (speedVec.X > 0)
		{
			DrawGraph(pos.X - 30 / 2, pos.Y - PlayerHeight,
				textureManager->GetTextureDate(TextureDate((int)TextureDate::kPlayerWalkRight_01 + animationCount_walk % 2)), TRUE);
		}
		else if (speedVec.X < 0)
		{
			DrawGraph(pos.X - 30 / 2, pos.Y - PlayerHeight,
				textureManager->GetTextureDate(TextureDate((int)TextureDate::kPlayerWalkLeft_01 + animationCount_walk % 2)), TRUE);
		}
		else if (speedVec.X == 0)
		{
			DrawGraph(pos.X - 30 / 2, pos.Y - PlayerHeight, textureManager->GetTextureDate(TextureDate::kPlayerWait), TRUE);
		}
	}
	else
	{
		if (speedVec.X >= 0)
		{
			DrawGraph(pos.X - 30 / 2, pos.Y - PlayerHeight, textureManager->GetTextureDate(TextureDate::kPlayerJumpRight), TRUE);
		}
		else if (speedVec.X < 0)
		{
			DrawGraph(pos.X - 30 / 2, pos.Y - PlayerHeight, textureManager->GetTextureDate(TextureDate::kPlayerJumpLeft), TRUE);
		}
	}

	//DrawBox(mapPos.X * MapChipEdge, mapPos.Y * MapChipEdge,
	//	(mapPos.X + 1) * MapChipEdge, (mapPos.Y + 1) * MapChipEdge, GetColor(255, 255, 0), TRUE);

	//DrawGraph(pos.X + 50, pos.Y + 30, textureManager->GetTextureDate(TextureDate::kMobius), TRUE);
}


void Player::Reset()
{
	if (coolTime > 0)
	{
		coolTime--;
		return;
	}

	if (!inputManager->IsKeyPushed(ResetKey)) { return; }

	mobiusPos.X = pos.X;
	mobiusPos.Y = pos.Y;

	pos.X = gameManager->GetPlayerInitPosX(gameManager->GetStageNum());
	pos.Y = gameManager->GetPlayerInitPosY(gameManager->GetStageNum());
	ResetStatus();
}


void Player::ResetStatus()
{
	isStandingGround = false;
	speedVec.X = 0;
	speedVec.Y = 0;
	moveVec.X = 0;
	moveVec.Y = 0;
	coolTime = 300;
	DonotOperation = false;

	const int StageNum = gameManager->GetStageNum();

	switch (StageNum)
	{
	case 19:
		gravity = 0.1f;
		break;
	case 20:
		gravity = 0.1f;
		break;
	default:
		gravity = 0.5f;
		break;
	}
}

void Player::Friction()
{
	if (speedVec.X > 0 && !inputManager->IsKeyHeld(RightMoveKey))
	{
		speedVec.X -= FrictionForce;

		if (speedVec.X < 0)
		{
			speedVec.X = 0;
		}
	}
	else if (speedVec.X < 0 && !inputManager->IsKeyHeld(LeftMoveKey))
	{
		speedVec.X += FrictionForce;

		if (speedVec.X > 0)
		{
			speedVec.X = 0;
		}
	}
}

void Player::Move()
{
	if (inputManager->IsKeyHeld(RightMoveKey))
	{
		speedVec.X += Speed;

		if (speedVec.X > MaxSpeed)
		{
			speedVec.X = MaxSpeed;
		}
	}

	if (inputManager->IsKeyHeld(LeftMoveKey))
	{
		speedVec.X -= Speed;

		if (speedVec.X < MaxSpeed * -1)
		{
			speedVec.X = MaxSpeed * -1;
		}
	}
}

void Player::Jump()
{
	if (!inputManager->IsKeyPushed(JumpKey)) { return; }

	if (isStandingGround)
	{
		if (gravityDirection)
		{
			speedVec.Y = JumpPower * -1;
		}
		else
		{
			speedVec.Y = JumpPower;
		}

		isStandingGround = false;
	}
}

void Player::Search()
{
	if (!inputManager->IsKeyPushed(SearchKey)) { return; }

	switch (gameManager->GetCurrentGimmickMapDate(mapPos.X, mapPos.Y))
	{
	case kChest_close:
		haveKeyItem = true;
		break;
	case kGoalTexturePos:
		GoToNextStage();
		break;
	case kRocketTexturePos:
		GoToNextStage();
		break;
	case kGoal:
		GoToNextStage();
		break;
	case kRocket:
		GoToNextStage();
		break;
	default:
		break;
	}
}

void Player::GoToNextStage()
{
	//if (!haveKeyItem) { return; }

	for (int i = 0; i < MaxSaveStage; i++)
	{
		if (gameManager->GetStageNum() + 1 == gameManager->GetSaveStageNum(i))
		{
			gameManager->SetCanUseSaveStage(i, true);
			break;
		}
	}
	haveKeyItem = false;
	gimmickManager->DeadGimmick();
	gameManager->SetStage(gameManager->GetStageNum() + 1);
	pos.X = gameManager->GetPlayerInitPosX(gameManager->GetStageNum());
	pos.Y = gameManager->GetPlayerInitPosY(gameManager->GetStageNum());
	gimmickManager->SpawnGimmick(kSun, pos.X, pos.Y);
}

void Player::ChangePos()
{
	CheckGravity();

	moveVec.X = speedVec.X;
	moveVec.Y = speedVec.Y;

	CheckCollisionBlock();

	pos.X += moveVec.X;
	pos.Y += moveVec.Y;

	CheckBlock(pos.X, pos.Y - 1, &mapPos.X, &mapPos.Y);
}

void Player::CheckCollisionBlock()
{
	float tmpx = moveVec.X;
	float tmpy = moveVec.Y;

	if (speedVec.X < 0)
	{
		tmpx = CheckCollisionBlock_left();
	}
	else if (speedVec.X > 0)
	{
		tmpx = CheckCollisionBlock_right();
	}
	switch (gravityDirection)
	{
	case true:
		if (speedVec.Y < 0)
		{
			tmpy = CheckCollisionBlock_up();
		}
		else if (speedVec.Y > 0)
		{
			tmpy = CheckCollisionBlock_down();
		}
		break;
	case false:
		if (speedVec.Y > 0)
		{
			tmpy = CheckCollisionBlock_up();
		}
		else if (speedVec.Y < 0)
		{
			tmpy = CheckCollisionBlock_down();
		}
		break;
	}

	moveVec.X = tmpx;
	moveVec.Y = tmpy;
}

float Player::CheckCollisionBlock_up()
{
	Vec2 tmp1;
	Vec2 tmp2;
	float tmp = moveVec.Y;

	CheckBlock(pos.X - PlayerWidht / 2 + 1, pos.Y - PlayerHeight + moveVec.Y, &tmp1.X, &tmp1.Y);
	CheckBlock(pos.X + PlayerWidht / 2 - 1, pos.Y - PlayerHeight + moveVec.Y, &tmp2.X, &tmp2.Y);

	for (int i = tmp1.X; i <= tmp2.X; i++)
	{
		if (i < 0 || tmp1.Y < 0)
		{
			continue;
		}

		if (gameManager->GetCurrentBlockMapDate(i, tmp1.Y) == kBlock)
		{

			tmp = (tmp1.Y + 1) * MapChipEdge - pos.Y + PlayerHeight;
			speedVec.Y = 0;

		}

		if (gameManager->GetCurrentGimmickMapDate(i, tmp1.Y) == kBlindBlock)
		{
			tmp = (tmp1.Y + 1) * MapChipEdge - pos.Y + PlayerHeight;
			speedVec.Y = 0;

			gameManager->SetCurrentBlockMapDate(i, tmp1.Y, kBlock);
		}

		CheckCollisionGimmick(i, tmp1.Y);
	}

	return tmp;
}

float Player::CheckCollisionBlock_down()
{
	Vec2 tmp1;
	Vec2 tmp2;
	float tmp = moveVec.Y;

	CheckBlock(pos.X - PlayerWidht / 2 + 1, pos.Y + moveVec.Y, &tmp1.X, &tmp1.Y);
	CheckBlock(pos.X + PlayerWidht / 2 - 1, pos.Y + moveVec.Y, &tmp2.X, &tmp2.Y);

	for (int i = tmp1.X; i <= tmp2.X; i++)
	{
		if (i < 0 || tmp1.Y < 0)
		{
			continue;
		}

		if (gameManager->GetCurrentBlockMapDate(i, tmp1.Y) == kBlock)
		{
			tmp = tmp1.Y * MapChipEdge - pos.Y;
			isStandingGround = true;
			speedVec.Y = 0;
		}

		if (gameManager->GetCurrentGimmickMapDate(i, tmp1.Y) == kDesk)
		{
			DonotOperation = true;
			if (gimmickManager->GetIsAliveGimmick(kDesk)) { break; }
			gimmickManager->SpawnGimmick(kDesk, pos.X, pos.Y);
			gimmickManager->SetIsAliveGimmick(kDesk, true);
		}

		CheckCollisionGimmick(i, tmp1.Y);
	}

	return tmp;
}

float Player::CheckCollisionBlock_right()
{
	Vec2 tmp1;
	Vec2 tmp2;
	float tmp = moveVec.X;

	CheckBlock(pos.X + PlayerWidht / 2 + 1 + moveVec.X, pos.Y - PlayerHeight, &tmp1.X, &tmp1.Y);
	CheckBlock(pos.X + PlayerWidht / 2 + 1 + moveVec.X, pos.Y - 1, &tmp2.X, &tmp2.Y);

	for (int i = tmp1.Y; i <= tmp2.Y; i++)
	{
		if (i < 0 || tmp1.X < 0)
		{
			continue;
		}

		if (gameManager->GetCurrentBlockMapDate(tmp1.X, i) == kBlock)
		{
			tmp = tmp1.X * MapChipEdge - pos.X - PlayerWidht / 2;
			speedVec.X = 0;
		}

		if (gameManager->GetCurrentGimmickMapDate(tmp1.X, i) == kLeftBlindBlock)
		{
			tmp = tmp1.X * MapChipEdge - pos.X - PlayerWidht / 2;
			speedVec.X = 0;

			gameManager->SetCurrentBlockMapDate(tmp1.X, i, kBlock);
		}
		
		CheckCollisionGimmick(tmp1.X, i);
	}

	return tmp;
}

float Player::CheckCollisionBlock_left()
{
	Vec2 tmp1;
	Vec2 tmp2;
	float tmp = moveVec.X;

	CheckBlock(pos.X - PlayerWidht / 2 - 1 + moveVec.X, pos.Y - PlayerHeight, &tmp1.X, &tmp1.Y);
	CheckBlock(pos.X - PlayerWidht / 2 - 1 + moveVec.X, pos.Y - 1, &tmp2.X, &tmp2.Y);

	for (int i = tmp1.Y; i <= tmp2.Y; i++)
	{
		if (i < 0 || tmp1.X < 0)
		{
			continue;
		}

		if (gameManager->GetCurrentBlockMapDate(tmp1.X, i) == kBlock)
		{
			tmp = (tmp1.X + 1) * MapChipEdge - pos.X + PlayerWidht / 2;
			speedVec.X = 0;
		}

		CheckCollisionGimmick(tmp1.X, i);	
	}

	return tmp;
}

void Player::CheckCollisionGimmick(int x_, int y_)
{
	switch (gameManager->GetCurrentGimmickMapDate(x_, y_))
	{
	case kNewsPaperSwitch:
		if (gimmickManager->GetIsAliveGimmick(kNewsPaperSwitch)) { break; }
		gimmickManager->SpawnGimmick(kNewsPaperSwitch, pos.X, pos.Y);
		gimmickManager->SetIsAliveGimmick(kNewsPaperSwitch, true);
		gameManager->SetCurrentGimmickMapDate(x_, y_, kNone);
		break;
	//case kDog:
	//	break;
	case kRiderSwitch:
		if (gimmickManager->GetIsAliveGimmick(kRiderSwitch)) { break; }
		gimmickManager->SpawnGimmick(kRiderSwitch, pos.X, pos.Y);
		gimmickManager->SetIsAliveGimmick(kRiderSwitch, true);
		gameManager->SetCurrentGimmickMapDate(x_, y_, kNone);
		break;
	case kMineSwitch:
		gameManager->SetIsCollide(true);
		gimmickManager->SpawnGimmick(kMineSwitch, pos.X, pos.Y);
		gimmickManager->SetIsAliveGimmick(kMineSwitch, true);
		break;
	//case kWood:
	//	break;
	case kSun:
		if (gimmickManager->GetIsAliveGimmick(kSun)) { break; }
		gimmickManager->SpawnGimmick(kSun, pos.X, pos.Y);
		gimmickManager->SetIsAliveGimmick(kSun, true);
		gameManager->SetCurrentGimmickMapDate(x_, y_, kNone);
		break;
	case kEnergyBulletSwitch:
		if (gimmickManager->GetIsAliveGimmick(kEnergyBulletSwitch)) { break; }
		gimmickManager->SpawnGimmick(kEnergyBulletSwitch, pos.X, pos.Y);
		gimmickManager->SetIsAliveGimmick(kEnergyBulletSwitch, true);
		gameManager->SetCurrentGimmickMapDate(x_, y_, kNone);
		break;
	case kReser:
		break;
	case kThiefSwitch:
		break;
	case kLightSwitch:
		break;
	case kGum:
		break;
	case kPen:
		break;
	case kLuckyHole:
		isFinishedLuckyHole = true;

		if (GetRand(149) == 8 && !isFinishedLuckyHole)
		{

		}
		break;
	case kNeedle:
		gameManager->SetIsCollide(true);
		break;
	case kPushpin:
		gameManager->SetIsCollide(true);
		break;
	case kFakeChest:
		gameManager->SetIsCollide(true);
		break;
	case kGravity:
		gravityDirection = false;
		if (gravity > 0)
		{
			gravity *= -1;
			speedVec.Y = 0;
		}
		break;
	case kKey:
		haveKeyItem = true;
		gameManager->SetCurrentGimmickMapDate(x_, y_, kNone);
		break;
	case kGtavityRelease:
		gravityDirection = false;
		if (gravity < 0)
		{
			gravity *= -1;
			speedVec.Y = 0;
		}
		break;
	default:
		break;
	}
}

void Player::CheckGravity()
{
	Vec2 tmp1;
	Vec2 tmp2;

	if (gravityDirection)
	{
		CheckBlock(pos.X - PlayerWidht / 2, pos.Y + 1, &tmp1.X, &tmp1.Y);
		CheckBlock(pos.X + PlayerWidht / 2, pos.Y + 1, &tmp2.X, &tmp2.Y);
	}
	else
	{
		CheckBlock(pos.X - PlayerWidht / 2, pos.Y - 1, &tmp1.X, &tmp1.Y);
		CheckBlock(pos.X + PlayerWidht / 2, pos.Y - 1, &tmp2.X, &tmp2.Y);
	}

	for (int i = tmp1.X; i <= tmp2.X; i++)
	{
		if (gameManager->GetCurrentBlockMapDate(i, tmp1.Y) == kBlock)
		{
			return;
		}
	}

	isStandingGround = false;
}

void Player::CheckBlock(float posx_, float posy_, int* x_, int* y_)
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

void Player::CheckFoot()
{

	//switch (gameManager->GetStageDate())
	//{
	//default:
	//	break;
	//}

}

void Player::DeadAnimation()
{
	rote += 0.5f;
}
