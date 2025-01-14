#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"
class Ball : public GameObject {
public:
	Ball();    // �R���X�g���N�^
	~Ball();   // �f�X�g���N�^
	void Update() override;   // �X�V����
	void Draw() override;     // �`�揈��
	// �{�[���̉摜���ԂɊւ���ϐ�
	int hImage;               // �ʏ�̃{�[���摜
	int hImageCollide;        // �Փˌ�̃{�[���摜
	int currentImage;         // ���ݕ\�����Ă���{�[���摜
	VECTOR2 position;         // �{�[���̈ʒu
	VECTOR2 velocity;         // �{�[���̑��x
	int goaled;               // �S�[���B���t���O
	int scroll;               // �X�N���[���ʒu�i���z�j
private:
	// �A�j���[�V�����Ɋւ���ϐ�
	float Gravity = 0.0f;     // �d��
	bool isColliding = false; // �Փˏ�ԃt���O
	int collisionTimer = 0;   // �Փˌ�̃^�C�}�[
	// �A�j���[�V�����̃t���[���Ǘ�
	int currentFrame;     // ���݂̃t���[��
	int frameWidth;     // �e�t���[���̕�
	int frameHeight;     // �e�t���[���̍���
	int totalFrames = 8;      // �A�j���[�V�����t���[���̑���
	int frameCounter = 0;     // �A�j���[�V�����̃J�E���^
	int maxFrames;
	int frameTimer;
	int animationSpeed;
};