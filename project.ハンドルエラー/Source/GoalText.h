#pragma once
#include "../Library/gameObject.h"
#include "DxLib.h"  // �`��p
#include "Vector2.h"
class GoalText : public GameObject {
public:
	GoalText();                // �R���X�g���N�^
	~GoalText();               // �f�X�g���N�^
	void Update() override;    // �X�V����
	void Draw() override;      // �`�揈��
	VECTOR2 position;
	int hImage;

	int PushBKey;
	int PushBbutton;
	int GameclearText;

	bool IsGoal;
	int scroll;
	int XInput;             // �W���C�p�b�hX������
	int YInput;             // �W���C�p�b�hY������

private:
	float timer;               // �^�C�}�[�i�e�L�X�g�̕\�����ԁj
	bool fadeStarted;          // �t�F�[�h�J�n�t���O
	int alpha;                 // �����̓����x�i�t�F�[�h�p�j

	int PlaySoundCounter;
};