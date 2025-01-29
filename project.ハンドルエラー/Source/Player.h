#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"
#include <DxLib.h>

class Player : public GameObject {

public:
    Player(); // �R���X�g���N�^
    void Update() override; // �v���C���[�̍X�V����
    void Draw() override;   // �v���C���[�̕`�揈��
    void DrawLife();
    void Animation();       // �v���C���[�̃A�j���[�V��������
    void UpdateAnimation(); // �V�K�ǉ��F�A�j���[�V�����X�V����

    // �v���C���[�̉摜�n���h��
    int hImage;             // �v���C���[�̃f�t�H���g�̉摜
    int hImageRightClick;
    int hImageLeftClick;
    int hImagelife;

    // �E�ړ��A���ړ��p�̉摜
    int hImageMoveRight;    // �E�ړ����̉摜
    int hImageMoveLeft;     // ���ړ����̉摜

    // �v���C���[�̈ʒu�Ə��
    VECTOR2 position;       // �v���C���[�̍��W�iVector2�j
    float velocity;         // ���������̑��x
    bool prevJumpKey;       // �O�t���[���̃W�����v�L�[�̏��
    bool onGround;          // �v���C���[���n�ʂɐڂ��Ă��邩
    int IsGoal;             // �S�[���t���O
    int goaled;             // �S�[���B���t���O
    int scroll;             // �X�N���[���ʒu�i���z�j

    // �A�j���[�V�����֘A�̕ϐ�
    int patternX;           // �A�j���[�V�����pX�p�^�[��
    int patternY;           // �A�j���[�V�����pY�p�^�[��
    int frameCounter;       // �t���[���J�E���g
    bool crying;            // �����Ă�����
    bool prevRightMouse;    // �E�N���b�N�̑O��̏��
    bool prevLeftMouse;     // ���N���b�N�̑O��̏��

    // �N���b�N���
    bool isRightClicked = false;  // �E�N���b�N����Ă��邩�̏��
    bool isLeftClicked = false;   // ���N���b�N����Ă��邩�̏��

    // �W���C�p�b�h�̓���
    int XInput;                // �W���C�p�b�hX������
    int YInput;                // �W���C�p�b�hY������

    // ���C�t�ƓG�Ƃ̏Փˏ���
    int life;                  // �v���C���[�̃��C�t
    int enemyCollisionCount;   // �G�ɐG�ꂽ��

    // �Q�[���I�[�o�[����
    void GameOver();           // �Q�[���I�[�o�[�����i��Ŏ����j

    // ���ړ��A�j���[�V�����̊Ǘ�
    int moveAnimationFrame;    // ���ړ��̃A�j���[�V�����t���[��
    int moveAnimationCounter;  // ���ړ��A�j���[�V�����̃J�E���^�[

    int animationCounter;
    int animationFrame;
    int animationSpeed = 10;
    int blinkCounter;
    int isMoving;

    int prevRightClick;
    int prevLeftClick;
};