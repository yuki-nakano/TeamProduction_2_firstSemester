#include "TitleScene.h"

TitleScene::TitleScene()
{
	gameManager = GameManager::GetInstance();
	inputManager = InputManager::GetInstance();
	soundManager = SoundManager::GetInstance();
	textureManager = TextureManager::GetInstance();

	SceneManager::GetInstance()->SetNextScene(SceneID_InGame);
}

TitleScene::~TitleScene()
{
}

void TitleScene::Exec()
{
	//if (option->Exec())
	//{
	//	return;
	//}

	if (inputManager->IsKeyPushed(NextSceneKey))
	{	
		soundManager->ChangeBGM(Sound::kStageBGM1);

		finishedScene = true;
	}
}

void TitleScene::Draw()
{
	//DrawString(0, 0, "title", GetColor(0, 0, 0));

	DrawGraph(0, 0, textureManager->GetTextureDate(TextureDate::kTitleBack), FALSE);

	DrawGraph(310, 45, textureManager->GetTextureDate(TextureDate::kTitleLogo), TRUE);

	DrawGraph(740, 595, textureManager->GetTextureDate(TextureDate::kTitleStart), TRUE);

	//option->Draw();
}

bool TitleScene::IsEnd() const
{
	return (finishedScene);
}
