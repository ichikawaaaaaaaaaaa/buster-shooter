#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"

//GameObject �N���X�̌p��
class Player : public GameObject {
public:
	Player();//�R���X�g���N�^
	~Player();//�f�X�g���N�^
	void Update() override;//�v���C���[�̍X�V����
	void Draw() override;//�v���C���[�̕`�揈��

	int hImage;//�v���C���[�̉摜�n���h��
	VECTOR2 position;// �v���C���[�̍��W�iVector2�j
	float velocity;  // ���������̑��x�i�W�����v�E�����p�j
	bool prevJumpKey;      // �O�t���[���̃W�����v�L�[�̏��
	bool onGround; // �v���C���[���n�ʂɐڂ��Ă��邩
	int IsGoal;  // �S�[���t���O
	int goaled;    // �S�[���B���t���O

	int scroll;  // �X�N���[���ʒu�i���z�j

	int patternX;  
	int patternY;
	int frameCounter;

	bool crying;

	bool prevRightMouse;

};



