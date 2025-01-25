#include "GameOver.h"
#include <DxLib.h>
#include <cassert>

#include "Player.h"
#include "Fader.h"
GameOver::GameOver()
{

	bgHandle = LoadGraph("data/image/GameOver.png");
	assert(bgHandle > 0);

	PushSpaceKey = LoadGraph("data/image/PushSpace.png");
}

GameOver::~GameOver()
{
	DeleteGraph(bgHandle);
	DeleteGraph(hBGImageII);
}

void GameOver::Update()
{
	GetJoypadInputState(DX_INPUT_KEY_PAD1);
	int PadInput;

	GetJoypadAnalogInput(&XInput, &YInput, DX_INPUT_KEY_PAD1);
	PadInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (PadInput & PAD_INPUT_1 || CheckHitKey(KEY_INPUT_B)) 
	{
		SceneManager::ChangeScene("TitleScene");
	}
}

	void GameOver::Draw()
	{
		DrawGraph(400, 200, hBGImageII, TRUE);
		//	ƒ^ƒCƒgƒ‹‰æ–Ê
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//	’Êí•`‰æ
		DrawGraph(200, 200, bgHandle, TRUE);
		//	[GameOver]

		DrawGraph(400, 500, PushSpaceKey, TRUE);
		if (timer >= 1.0f) {
		}
	}
