#pragma once

#include "../Library/gameObject.h"

#include "Vector2.h"

class Jet : public GameObject
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	Jet();
	~Jet();
	// �X�V����
	void Update() override;
	// �`�揈��
	void Draw() override;
	// �ʒu�擾
	VECTOR2 GetPosition() const;
	// �Փˎ��̏���
	void OnCollide() override;
private:
	// �����o�ϐ�
	int hImage;          // �摜�̃n���h��
	int imageWidth;      // �摜�̕�
	int imageHeight;     // �摜�̍���
	VECTOR2 position;    // ���݈ʒu
	VECTOR2 speed;       // �ړ����x
	int patternX;        // �p�^�[��X (�A�j���[�V�����p)
	int patternY;        // �p�^�[��Y (�A�j���[�V�����p)
	int currentImage;    // ���݂̉摜
	int frameWidth;      // 1�t���[���̕�
	int frameHeight;     // 1�t���[���̍���
	int maxFrames;       // ���t���[����
	int currentFrame;    // ���݂̃t���[��
	int frameTimer;      // �t���[���؂�ւ��^�C�}�[
	int animationSpeed;  // �A�j���[�V�������x
	int timer;           // �U���^�C�}�[
	bool attacking;      // �U�������ǂ���
	bool dead;           // ���S���
	int deadCounter;     // ���S�J�E���^
	// �Փ˔���p
	float velocity;      // ���x
	bool onGround;       // �n�ʂɐڐG���Ă��邩
};
