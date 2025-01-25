#pragma once
#include "../Library/gameObject.h"

class GameOver : public SceneBase
{
private://	�Q�[���I�[�o�[

	const char* KEY_GRAPH_PATH = "data/image/GameOver.png";

	int PushSpaceKey;

	const int OVER_GRAPH_X = 370;			//	[GAMEOVER]�\���ʒu(X)
	const int OVER_GRAPH_Y = 450;		//	[GAMEOVER]�\���ʒu(Y)

private:
	int bgHandle;			//	�摜�n���h��(�^�C�g�����)
	float timer;               // �^�C�}�[�i�e�L�X�g�̕\�����ԁj


public:
	GameOver();
	~GameOver();
	void Update() override;
	void Draw() override;
	int hBGImageII;

	int XInput;             // �W���C�p�b�hX������
	int YInput;             // �W���C�p�b�hY������
	bool fadeStarted;          // �t�F�[�h�J�n�t���O
	int alpha;                 // �����̓����x�i�t�F�[�h�p�j
};
