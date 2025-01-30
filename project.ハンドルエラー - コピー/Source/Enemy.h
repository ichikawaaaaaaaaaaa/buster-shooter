#pragma once

#include "../Library/gameObject.h"

#include "Vector2.h"

class Enemy : public GameObject {

public:

    Enemy();            // �R���X�g���N�^
    ~Enemy();           // �f�X�g���N�^

    void Update() override;  // �X�V����
    void Draw() override;    // �`�揈��
    VECTOR2 position;        // �G�̈ʒu
    VECTOR2 speed;           // �G�̑��x

    int hImage;              // �G�̉摜�n���h��
    int patternX;            // �\���p�^�[���̉��ԍ�
    int patternY;            // �\���p�^�[���̏c�ԍ�
    int velocity;
    VECTOR2 GetPosition() const;  // �G�̈ʒu���擾����
    void OnCollide();             // �Փˎ��̏���

    int timer;               // �^�C�}�[
    bool attacking;          // �U�����t���O
    bool dead;               // ���S�t���O
    int deadCounter;         // ���S��Ԃ̃J�E���^
    bool onGround;           // �n�ʂɂ��邩�ǂ����̃t���O

    // �A�j���[�V�����֘A

    int imageWidth;          // �摜�̕�
    int imageHeight;         // �摜�̍���
    int frameWidth;          // 1�t���[���̕�
    int frameHeight;         // 1�t���[���̍���
    int framesPerRow;        // 1�s������̃t���[����
    int maxFrames;           // �ő�t���[����
    int currentImage;        // ���ݎg�p���̉摜
    int currentFrame;        // ���݂̃t���[���ԍ�
    int frameTimer;          // �t���[���؂�ւ��p�^�C�}�[
    int animationSpeed;      // �A�j���[�V�����̑��x
};