#pragma once
#include "../Library/gameObject.h"
#include "DxLib.h"  // �`��p
class GoalText : public GameObject {
public:
	GoalText();                // �R���X�g���N�^
	~GoalText();               // �f�X�g���N�^
	void Update() override;    // �X�V����
	void Draw() override;      // �`�揈��
	

	int hImage;

private:
	float timer;               // �^�C�}�[�i�e�L�X�g�̕\�����ԁj
	bool fadeStarted;          // �t�F�[�h�J�n�t���O
	int alpha;                 // �����̓����x�i�t�F�[�h�p�j

};