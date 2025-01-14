#include "titleScene.h"
#include "../Library/sceneManager.h"
#include "DebugScreen.h"

#include "../StageUtility.h"
#include "../Library/time.h"

TitleScene::TitleScene()
{
	hBGImage = LoadGraph("data/image/Title.png");
	hKeyImage = LoadGraph("data/image/PushSpace.png");
	BackScreen = LoadGraph("data/image/Titiebackscreen.png");

	Stage1Image = LoadGraph("data/image/Stage1.png");
	Stage2Image = LoadGraph("data/image/Stage2.png");
	Stage3Image = LoadGraph("data/image/Stage3.png");
	Stage4Image = LoadGraph("data/image/Stage4.png");
	Stage5Image = LoadGraph("data/image/Stage5.png");

	StageFlame = LoadGraph("data/image/StageFlame.png");

	Stageflame = 0;



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
//	if (CheckHitKey(KEY_INPUT_1)) {
//		StageUtility::SetStageNo(1);
//		SceneManager::ChangeScene("PlayScene");
//	}
//	if (CheckHitKey(KEY_INPUT_2)) {
//		StageUtility::SetStageNo(2);
//		SceneManager::ChangeScene("PlayScene");
//	}
//	if (CheckHitKey(KEY_INPUT_3)) {
//		StageUtility::SetStageNo(3);
//		SceneManager::ChangeScene("PlayScene");
//	}
//	if (CheckHitKey(KEY_INPUT_4)) {
//		StageUtility::SetStageNo(4);
//		SceneManager::ChangeScene("PlayScene");
//	}
//	if (CheckHitKey(KEY_INPUT_5)) {
//		StageUtility::SetStageNo(5);
//		SceneManager::ChangeScene("PlayScene");
//	}


	if (CheckHitKey(KEY_INPUT_1)) {
		Stageflame = 1;
			}
			if (CheckHitKey(KEY_INPUT_2)) {
				Stageflame = 2;
			}
			if (CheckHitKey(KEY_INPUT_3)) {
				Stageflame = 3;
			}
			if (CheckHitKey(KEY_INPUT_4)) {
				Stageflame = 4;
			}
			if (CheckHitKey(KEY_INPUT_5)) {
				Stageflame = 5;
			}

			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				StageUtility::SetStageNo(Stageflame);
				SceneManager::ChangeScene("PlayScene");
			}

	//	前フレームからの経過時間を取得
	DrawKeyTimer += Time::DeltaTime();
	//	一定時間(DRAW_KEY_WAIT)経過したら、[PUSH SPACE KEY]を描画する・しないを切りかえる
	if (DrawKeyTimer >= DRAW_KEY_WAIT)
	{
		isDrawKey = !isDrawKey;
		DrawKeyTimer = 0.5f;
	}
}

void TitleScene::Draw()
{
	//	タイトル画面
	DrawGraph(0, 0, BackScreen, TRUE);
	DrawGraph(160, 200, hBGImage, TRUE);
	DrawGraph(340, 600, hKeyImage, TRUE);
	

	


	//	[PUSH SPACE KEY]
	if (isDrawKey)
	{
		DrawGraph(300, 2000, hKeyImage, TRUE);
	}

	if (Stageflame ==1) {
		if (isDrawKey)
		{
		DrawGraph(100, 500, StageFlame, TRUE);
		}
	}

	if (Stageflame == 2) {
		if (isDrawKey)
		{
			DrawGraph(300, 500, StageFlame, TRUE);
		}				   
	}					   
						  
						   
	if (Stageflame == 3) { 
		if (isDrawKey)	   
		{				   
			DrawGraph(500, 500, StageFlame, TRUE);
		}				   
	}					   
						   
	if (Stageflame == 4) { 
		if (isDrawKey)	   
		{				   
			DrawGraph(700, 500, StageFlame, TRUE);
		}				   
	}					   
						   
	if (Stageflame == 5) { 
		if (isDrawKey)	   
		{				   
			DrawGraph(900, 500, StageFlame, TRUE);
		}
	}


	DrawGraph(100, 500, Stage1Image, TRUE);
	DrawGraph(300, 500, Stage2Image, TRUE);
	DrawGraph(500, 500, Stage3Image, TRUE);
	DrawGraph(700, 500, Stage4Image, TRUE);
	DrawGraph(900, 500, Stage5Image, TRUE);


		SceneBase::Draw();
		DrawString(100, 100, "プレイしたいステージを１～5を押して選択してください。Spaceで確定します", GetColor(255, 255, 255));
}