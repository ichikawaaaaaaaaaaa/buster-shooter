#include "titleScene.h"
#include "../Library/sceneManager.h"
#include "DebugScreen.h"
#include "StageUtility.h"
#include <iostream>

TitleScene::TitleScene()
{
	StageUtility::Init();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_1)) {
		StageUtility::SetStageNo(1);
		SceneManager::ChangeScene("PlayScene");
	}
	if (CheckHitKey(KEY_INPUT_2)) {
		StageUtility::SetStageNo(2);
		SceneManager::ChangeScene("PlayScene");
	}
	if (CheckHitKey(KEY_INPUT_3)) {
		StageUtility::SetStageNo(3);
		SceneManager::ChangeScene("PlayScene");
	}
	if (CheckHitKey(KEY_INPUT_4)) {
		StageUtility::SetStageNo(4);
		SceneManager::ChangeScene("PlayScene");
	}
	if (CheckHitKey(KEY_INPUT_5)) {
		StageUtility::SetStageNo(5);
		SceneManager::ChangeScene("PlayScene");
	}

	SceneBase::Update();
}

void TitleScene::Draw()
{
	SceneBase::Draw();
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawString(100, 100, "プレイしたいステージを１～2を押して選択してください。", GetColor(255, 255, 255));
}
