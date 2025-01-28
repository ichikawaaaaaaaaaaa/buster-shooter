#include "GameOver.h"
#include <DxLib.h>
#include <cassert>

#include "Player.h"
#include "Fader.h"
GameOver::GameOver()
{

	bgHandle = LoadGraph("data/image/GameOver.png");
	assert(bgHandle > 0);

	PushBKey = LoadGraph("data/image/PushBkey.png");
	PushAbutton = LoadGraph("data/image/PushAbutton.png");

	int PlaySoundFile(char* FileName, int PlayType);
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

	if (PadInput & PAD_INPUT_3 || CheckHitKey(KEY_INPUT_B)) 
	{
		PlaySoundFile("data/sound/GameOver_TitleBack.mp3", DX_PLAYTYPE_NORMAL);
		SceneManager::ChangeScene("TitleScene");
	}
}

	void GameOver::Draw()
	{
		DrawGraph(400, 200, hBGImageII, TRUE);
		//	É^ÉCÉgÉãâÊñ 
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//	í èÌï`âÊ
		DrawGraph(171, 200, bgHandle, TRUE);
		//	[GameOver]

		DrawGraph(397, 500, PushBKey, TRUE);
		DrawGraph(324, 600, PushAbutton, TRUE);
	}
