//#include "GameClear.h"
//#include <DxLib.h>
//#include <cassert>
//
//#include "Player.h"
//GameClear::GameClear()
//{
//
//	bgHandle = LoadGraph("image/GameClear.png");
//	assert(bgHandle > 0);
//
//}
//
//GameClear::~GameClear()
//{
//	DeleteGraph(bgHandle);
//	DeleteGraph(hBGImageII);
//}
//
//void GameClear::Update()
//
//{
//
//	if ((CheckHitKey(KEY_INPUT_T)) || CheckHitKey(KEY_INPUT_RSHIFT))
//	{
//		SceneManager::ChangeScene("TitleScene");
//	}
//}
//
//
//void GameClear::Draw()
//{
//	DrawGraph(0, 0, hBGImageII, TRUE);
//	//	É^ÉCÉgÉãâÊñ 
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//	í èÌï`âÊ
//	DrawGraph(0, 0, bgHandle, TRUE);
//	//	[GameOver]
//
//
//}