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
	PushBbutton = LoadGraph("data/image/PushBbutton.png");

	Stage1Image = LoadGraph("data/image/Stage1.png");
	Stage2Image = LoadGraph("data/image/Stage2.png");
	Stage3Image = LoadGraph("data/image/Stage3.png");
	Stage4Image = LoadGraph("data/image/Stage4.png");
	Stage5Image = LoadGraph("data/image/Stage5.png");

	StageFlame = LoadGraph("data/image/StageFlame.png");

	Stageflame = 1;
	prevInputPad = false;   

	int KeyPush = false;	//�L�[���͌��m
	int StickInput = false; //�R���g���[���[���m
	

	int PlaySoundFile(char* FileName, int PlayType);


	//	[PUSH SPACE KEY]�\���ݒ�̏�����
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

	GetJoypadInputState(DX_INPUT_KEY_PAD1);
	int PadInput;

	GetJoypadAnalogInput(&XInput, &YInput, DX_INPUT_KEY_PAD1);
	PadInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);

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
		StickInput = false;
		KeyPush = true;
		PlaySoundFile("data/sound/StageSelect.mp3", DX_PLAYTYPE_BACK);
			}
			if (CheckHitKey(KEY_INPUT_2)) {
				Stageflame = 2;
				StickInput = false;
				KeyPush = true;
				PlaySoundFile("data/sound/StageSelect.mp3", DX_PLAYTYPE_BACK);
			}
			if (CheckHitKey(KEY_INPUT_3)) {
				Stageflame = 3;
				StickInput = false;
				KeyPush = true;
				PlaySoundFile("data/sound/StageSelect.mp3", DX_PLAYTYPE_BACK);
			}
			if (CheckHitKey(KEY_INPUT_4)) {
				Stageflame = 4;
				StickInput = false;
				KeyPush = true;
				PlaySoundFile("data/sound/StageSelect.mp3", DX_PLAYTYPE_BACK);
			}
			if (CheckHitKey(KEY_INPUT_5)) {
				Stageflame = 5;
				StickInput = false;
				KeyPush = true;
				PlaySoundFile("data/sound/StageSelect.mp3", DX_PLAYTYPE_BACK);
			}

			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				PlaySoundFile("data/sound/StageJoin.mp3", DX_PLAYTYPE_BACK);
				StageUtility::SetStageNo(Stageflame);
				SceneManager::ChangeScene("PlayScene");
			}


			timer += 0.1f;
			if (timer >= 1.0f) {
				prevInputPad = false;
			}



			if (prevInputPad == false) {
				if (CheckHitKey(KEY_INPUT_D)) {
					StickInput = false;
					KeyPush = true;
					PlaySoundFile("data/sound/StageSelect.mp3", DX_PLAYTYPE_BACK);
					//if (CheckHitKey(KEY_INPUT_RIGHT)) {
					Stageflame = ((Stageflame + 1) % 5);
				}
				if (Stageflame == 0)
				{
					Stageflame = 5;
				}
				if ( CheckHitKey(KEY_INPUT_A)) {
					StickInput = false;
					KeyPush = true;
					PlaySoundFile("data/sound/StageSelect.mp3", DX_PLAYTYPE_BACK);
					//if (CheckHitKey(KEY_INPUT_LEFT)) {
					Stageflame -= 1;
					if (Stageflame == 0)
					{
						Stageflame = 5;
					}
				}
				prevInputPad = true;
				timer = 0.0f;

			}

				if (prevInputPad == false) {
					if (XInput > 100 || CheckHitKey(KEY_INPUT_D)) {
						KeyPush = false;
						StickInput = true;
						PlaySoundFile("data/sound/StageSelect.mp3", DX_PLAYTYPE_BACK);
					//if (CheckHitKey(KEY_INPUT_RIGHT)) {
						Stageflame = ((Stageflame + 1) % 5) ;
					}
					if (Stageflame == 0)
					{
						Stageflame = 5;
					}
				if (XInput < -100 || CheckHitKey(KEY_INPUT_A)) {
					KeyPush = false;
					StickInput = true;
					PlaySoundFile("data/sound/StageSelect.mp3", DX_PLAYTYPE_BACK);
				//if (CheckHitKey(KEY_INPUT_LEFT)) {
						Stageflame -= 1;
						if (Stageflame == 0)
						{
							Stageflame = 5;
						}
					}
				prevInputPad = true;
				timer = 0.0f;

				}
				
				if (PadInput & (PAD_INPUT_3))
				{
					PlaySoundFile("data/sound/StageJoin.mp3", DX_PLAYTYPE_NORMAL);
					StageUtility::SetStageNo(Stageflame);
					SceneManager::ChangeScene("PlayScene");
				}
			
			
		



	//	�O�t���[������̌o�ߎ��Ԃ��擾
	DrawKeyTimer += Time::DeltaTime();
	//	��莞��(DRAW_KEY_WAIT)�o�߂�����A[PUSH SPACE KEY]��`�悷��E���Ȃ���؂肩����
	if (DrawKeyTimer >= DRAW_KEY_WAIT)
	{
		isDrawKey = !isDrawKey;
		DrawKeyTimer = 0.5f;
	}
}

void TitleScene::Draw()
{
	//	�^�C�g�����
	DrawGraph(0, 0, BackScreen, TRUE);
	DrawGraph(140, 200, hBGImage, TRUE);


	if (KeyPush == true) {
		DrawGraph(340, 600, hKeyImage, TRUE);
	}
	if (StickInput == true) {
		DrawGraph(300, 600, PushBbutton, TRUE);
	}

	


	//	[PUSH SPACE KEY]
	

	if (isDrawKey)
	{
		DrawGraph(300, 2000, hKeyImage, TRUE);
	}

	if (Stageflame ==1) {
		if (isDrawKey)
	{
		DrawGraph(33, 462, StageFlame, TRUE);
	}
	}

	if (Stageflame == 2) {
		if (isDrawKey)
		{
			DrawGraph(283, 462, StageFlame, TRUE);
		}				   
	}					   
						  
						   
	if (Stageflame == 3) { 
		if (isDrawKey)	   
		{				   
			DrawGraph(533, 462, StageFlame, TRUE);
	}				   
	}					   
						   
	if (Stageflame == 4) { 
		if (isDrawKey)	   
		{				   
			DrawGraph(783, 462, StageFlame, TRUE);
		}				   
	}					   
						   
	if (Stageflame == 5) { 
		if (isDrawKey)	   
		{				   
			DrawGraph(1033, 462, StageFlame, TRUE);
		}
	}


	DrawGraph(40, 470, Stage1Image, TRUE);
	DrawGraph(290, 470, Stage2Image, TRUE);
	DrawGraph(540, 470, Stage3Image, TRUE);
	DrawGraph(790, 470, Stage4Image, TRUE);
	DrawGraph(1040, 470, Stage5Image, TRUE);


		SceneBase::Draw();
	//	DrawString(100, 100, "�v���C�������X�e�[�W���P�`5�������đI�����Ă��������BSpace�Ŋm�肵�܂�", GetColor(255, 255, 255));
}