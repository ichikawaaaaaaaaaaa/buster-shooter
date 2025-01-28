#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"
#include <DxLib.h>

//GameObject �N���X�̌p��
class Player : public GameObject {
public:
    Player(); // �R���X�g���N�^
    //~Player(); // �f�X�g���N�^�i�K�v�ɉ����ăR�����g�A�E�g���O���Ă��������j
    void Update() override; // �v���C���[�̍X�V����
    void Draw() override;   // �v���C���[�̕`�揈��
    void Animation();       // �v���C���[�̃A�j���[�V��������
    int hImage;             // �v���C���[�̉摜�n���h��
    int hImageKEY_D_Click;
    int hImageKEY_A_Click;
    int hImageRightClick;
    int hImageLeftClick;
    int hImagelife;
    VECTOR2 position;       // �v���C���[�̍��W�iVector2�j
    float velocity;         // ���������̑��x
    bool prevJumpKey;       // �O�t���[���̃W�����v�L�[�̏��
    bool onGround;          // �v���C���[���n�ʂɐڂ��Ă��邩
    int IsGdoal;             // �S�[���t���O
    int goaled;             // �S�[���B���t���O
    int scroll;             // �X�N���[���ʒu�i���z�j
    int patternX;           // �A�j���[�V�����pX�p�^�[��
    int patternY;           // �A�j���[�V�����pY�p�^�[��
    int frameCounter;       // �t���[���J�E���g
    bool crying;            // �����Ă�����
    bool prevRightMouse;    // �E�N���b�N�̑O��̏��
    bool prevLeftMouse;     // ���N���b�N�̑O��̏��
    int XInput;             // �W���C�p�b�hX������
    int YInput;             // �W���C�p�b�hY������

    // ���C�t�Ǘ�

    int life;               // �v���C���[�̃��C�t
    int enemyCollisionCount; // �G�ɐG�ꂽ��
    // �Q�[���I�[�o�[����
    void GameOver();        // �Q�[���I�[�o�[�����i��Ŏ����j

    //D�N���b�N�����o���ĉ摜��ύX���鏈��
    bool prevKEY_D_Click = false;
    bool isKEY_D_Click = false;

    //A�N���b�N�����o���ĉ摜��ύX���鏈��
    bool prevKEY_A_Click = false;
    bool isKEY_A_Click = false;

    // �E�N���b�N�����o���ĉ摜��ύX���鏈��
    bool prevRightClick = false;  // �E�N���b�N�̑O����
    bool isRightClicked = false;  // ���݉E�N���b�N����Ă��邩�̏��

    // ���N���b�N�����o���ĉ摜��ύX���鏈��
    bool prevLeftClick = false;  // �E�N���b�N�̑O����
    bool isLeftClicked = false;  // ���݉E�N���b�N����Ă��邩�̏��

    bool Changeflame;
    float timer;
    int blinkCounter;

};
