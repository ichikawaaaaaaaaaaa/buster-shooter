#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"

<<<<<<< HEAD
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

};



=======
class Player : public GameObject {
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;
	int hImage;
	VECTOR2 position;
	float velocity;
	bool prevJumpKey;	//�O�̃W�����v�L�[
	bool onGround;	//�n�ʂɂ���
};
>>>>>>> e687b6cbac460819700e00a87906bba6386f6570
