#include "DxLib.h"
#include "Definition.h"
#include "Manager/GameManager.h"
#include "Manager/InputManager.h"
#include "Manager/SceneManager.h"
#include "Manager/SoundManager.h"
#include "Manager/TextureManager.h"
#include "Manager/GimmickManager.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	SetOutApplicationLogValidFlag(false);
	ChangeWindowMode(true);
	SetGraphMode(Widht, Height, 16);
	SetBackgroundColor(255, 255, 255);
	SetMainWindowText("あいつ、そろそろ死爆");

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//描画先を裏の画面に設定
	SetDrawScreen(DX_SCREEN_BACK);

	//管理クラスの作成
	InputManager::CreateInstance();
	InputManager* inputManager = InputManager::GetInstance();
	SoundManager::CreateInstance();
	//SoundManager::GetInstance()->LoadSounds();
	TextureManager::CreateInstance();
	GameManager::CreateInstance();
	SceneManager::CreateInstance();
	SceneManager* sceneManager = SceneManager::GetInstance();

	SoundManager::GetInstance()->StartBGM(Sound::kTitle);

	while (true)
	{
		// メッセージループに代わる処理をする
		if (ProcessMessage() == -1 ||
			inputManager->IsKeyPushed(KEY_INPUT_ESCAPE) &&
			inputManager->IsKeyHeld(KEY_INPUT_LSHIFT))
		{
			break;        // エラーが起きたらループを抜ける
		}
		else
		{
			//フレームごとにキーの状態更新
			inputManager->UpdateKeyStatus();

			ClearDrawScreen();
			clsDx();

			//シーン処理
			sceneManager->Exec();

			//シーン描画
			sceneManager->Draw();

			if (GameManager::GetInstance()->GetFinishGame()) { break; }

			ScreenFlip();
		}
	}
	
	sceneManager = nullptr;
	inputManager = nullptr;
	SceneManager::DeleteInstance();
	GameManager::DeleteInstance();
	TextureManager::DeleteInstance();
	SoundManager::DeleteInstance();
	InputManager::DeleteInstance();

	DxLib_End();	// ＤＸライブラリ使用の終了処理
	return 0;		// ソフトの終了 
}
