#include "titleScene.h"
#include "../Library/sceneManager.h"
#include "DebugScreen.h"

#include "../StageUtility.h"
#include "../Library/time.h"

TitleScene::TitleScene()
{
	hBGImage = LoadGraph("image/Title.png");
	hKeyImage = LoadGraph("image/PushSpace.png");

	Stage1Image = LoadGraph("data/image/Stage1.png");
	Stage2Image = LoadGraph("data/image/Stage2.png");
	Stage3Image = LoadGraph("data/image/Stage3.png");
	Stage4Image = LoadGraph("data/image/Stage4.png");
	Stage5Image = LoadGraph("data/image/Stage5.png");





	//	[PUSH SPACE KEY]表示設定の初期化
	DrawKeyTimer = 0.0f;
	isDrawKey = true;
}

TitleScene::~TitleScene()
{
	DeleteGraph(hBGImage);
	DeleteGraph(hKeyImage);
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

	//	前フレームからの経過時間を取得
	DrawKeyTimer += Time::DeltaTime();
	//	一定時間(DRAW_KEY_WAIT)経過したら、[PUSH SPACE KEY]を描画する・しないを切りかえる
	if (DrawKeyTimer >= DRAW_KEY_WAIT)
	{
		isDrawKey = !isDrawKey;
		DrawKeyTimer = 0.0f;
	}
}

void TitleScene::Draw()
{
	//	タイトル画面
	DrawGraph(300, 1800, hBGImage, TRUE);
	DrawGraph(300, 200, hBGImage, TRUE);

	DrawGraph(300, 400, Stage1Image, TRUE);
	DrawGraph(300, 600, Stage2Image, TRUE);
	DrawGraph(300, 100, Stage3Image, TRUE);
	DrawGraph(300, 400, Stage4Image, TRUE);
	DrawGraph(300, 800, Stage5Image, TRUE);


	//	[PUSH SPACE KEY]
	if (isDrawKey)
	{
		DrawGraph(300, 2000, hKeyImage, TRUE);
	}

		SceneBase::Draw();
		DrawString(100, 100, "プレイしたいステージを１～5を押して選択してください。", GetColor(255, 255, 255));
}