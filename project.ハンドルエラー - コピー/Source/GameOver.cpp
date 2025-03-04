#include "GameOver.h"
#include <DxLib.h>
#include <cassert>

#include "Player.h"
GameOver::GameOver()
{

	bgHandle = LoadGraph("image/GameOver.png");
	assert(bgHandle > 0);

}

GameOver::~GameOver()
{
	DeleteGraph(bgHandle);
	DeleteGraph(hBGImageII);
}

void GameOver::Update()
{

	if ((CheckHitKey(KEY_INPUT_T)) || CheckHitKey(KEY_INPUT_RSHIFT))
	{
		SceneManager::ChangeScene("TitleScene");
	}
}


void GameOver::Draw()
{
	DrawGraph(0, 0, hBGImageII, TRUE);
	//	タイトル画面
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//	通常描画
	DrawGraph(0, 0, bgHandle, TRUE);
	//	[GameOver]

}