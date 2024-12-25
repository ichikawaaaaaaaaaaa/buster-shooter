#include "titleScene.h"
#include "../Library/sceneManager.h"
#include "DebugScreen.h"

#include "../StageUtility.h"
#include "../Library/time.h"

TitleScene::TitleScene()
{
	hBGImage = LoadGraph("image/Title.png");
	hKeyImage = LoadGraph("image/PushSpace.png");

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

	//	�O�t���[������̌o�ߎ��Ԃ��擾
	DrawKeyTimer += Time::DeltaTime();
	//	��莞��(DRAW_KEY_WAIT)�o�߂�����A[PUSH SPACE KEY]��`�悷��E���Ȃ���؂肩����
	if (DrawKeyTimer >= DRAW_KEY_WAIT)
	{
		isDrawKey = !isDrawKey;
		DrawKeyTimer = 0.0f;
	}
}

void TitleScene::Draw()
{
	//	�^�C�g�����
	DrawGraph(0, 0, hBGImage, TRUE);

	//	[PUSH SPACE KEY]
	if (isDrawKey)
	{
		DrawGraph(300, 500, hKeyImage, TRUE);
	}

		SceneBase::Draw();
		DrawString(0, 0, "TITLE SCENE", GetColor(255, 255, 255));
		DrawString(100, 100, "�v���C�������X�e�[�W���P�`5�������đI�����Ă��������B", GetColor(255, 255, 255));
}