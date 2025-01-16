#include "Player.h"
#include "GoalText.h"
#include "Stage.h"
#include "Ball.h"
#include "config.h"
#include "Enemy.h"
#include "Vector2.h"
#include "GameOver.h"


float Gravity = 0.5f;     //�d�͉����x
float jumpHeight = 40 * 1.5;  //�W�����v�̍���
float V0 = -sqrtf(3.0f * Gravity * jumpHeight);//�����v�Z

// �v���C���[�̃��C�t�ƓG�ɐG�ꂽ��
int life = 2;  // �������C�t��3
int enemyCollisionCount = 0; // �G�ɐG�ꂽ��

// �R���X�g���N�^

Player::Player()

{
    hImage = LoadGraph("data/image/Player.png");//�L�����摜�̓ǂݍ���
    hImageRightClick = LoadGraph("data/image/kenright.png");
    hImageLeftClick = LoadGraph("data/image/kenleft.png");
    position.x = 10;  //����X���W
    position.y = 100; //�������W
    velocity = 0; //�������x
    prevJumpKey = false;   //�����W�����v�L�[���
    onGround = false;  //�n�㔻�菉����
    IsGoal = 0; //�S�[���t���O������
    goaled = 0;  //�S�[���B���t���O������
    scroll = 0;  //�X�N���[���ʒu������

    //�v���C���[�̃��C�t
    life = LoadGraph("data/image/heart.png");
}

// �X�V����

void Player::Update()

{
    GetJoypadInputState(DX_INPUT_KEY_PAD1);
    int PadInput;

    GetJoypadAnalogInput(&XInput, &YInput, DX_INPUT_KEY_PAD1);
    PadInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    // �E�N���b�N��������Ă��邩�����o
    if (GetMouseInput() & MOUSE_INPUT_RIGHT) {
        if (!prevRightClick) {  // �N���b�N���V���Ɏn�܂�����
            isRightClicked = true;
        }
        prevRightClick = true;
    }
    else {
        prevRightClick = false;
        isRightClicked = false;  // �E�N���b�N�����ꂽ��
    }

    // ���N���b�N��������Ă��邩�����o
    if (GetMouseInput() & MOUSE_INPUT_LEFT) {
        if (!prevLeftClick) {  // �N���b�N���V���Ɏn�܂�����
            isLeftClicked = true;
        }
        prevLeftClick = true;
    }
    else {
        prevLeftClick = false;
        isLeftClicked = false;  // ���N���b�N�����ꂽ��
    }

    Stage* s = FindGameObject<Stage>(); // �X�e�[�W�I�u�W�F�N�g�擾
    if (goaled) return; // �S�[���ς݂̏ꍇ�A�������I��

    // �v���C���[�ƓG�̏Փ˔���

    std::list<Enemy*> enemys = FindGameObjects<Enemy>();

    for (Enemy* e : enemys) {
        if (CircleHit(position, e->position, 56)) { // �Փ˂����ꍇ
            enemyCollisionCount++; // �Փˉ񐔂𑝉�

            // �Փˉ񐔂�2��ɂȂ����烉�C�t�����炷
            if (enemyCollisionCount >= 2) {

                life--; // ���C�t��1���炷

                enemyCollisionCount = 0; // �Փˉ񐔃��Z�b�g

                // ���C�t��0�ɂȂ�����Q�[���I�[�o�[
                if (life <= 0) {
                    // �Q�[���I�[�o�[�����i�����Ŏ��ۂɃQ�[���I�[�o�[�����������j
                    // �Ⴆ�΁A�Q�[���I�[�o�[��ʂ�\��������A�Q�[�����I�������肷��
                    // GameOver(); // �Q�[���I�[�o�[�������Ăяo��
                    SceneManager::ChangeScene("GameOver");
                    return; // �Q�[���I�[�o�[��̏������I��
                }
            }
        }
    }


    {
        Stage* s = FindGameObject<Stage>();
        if (goaled == false) {
            if (CheckHitKey(KEY_INPUT_A)) {
                position.x -= 2;
                int push = s->IsWallLeft(position + VECTOR2(0, 0));
                position.x += push;
                push = s->IsWallLeft(position + VECTOR2(0, 39));
                position.x += push;
            }
            if (CheckHitKey(KEY_INPUT_D)) {
                position.x += 2;
                // �E�ɕǂ����邩���ׂ�
                int push = s->IsWallRight(position + VECTOR2(39, 0));
                position.x -= push;
                push = s->IsWallRight(position + VECTOR2(39, 39));
                position.x -= push;
            }
            if (CheckHitKey(KEY_INPUT_SPACE)) {
                if (prevJumpKey == false) {
                    if (onGround) {
                        // �W�����v�J�n
                        velocity = V0; // ���������߂�
                    }
                }
                prevJumpKey = true;
            }
            else {
                prevJumpKey = false;
            }
        }
        position.y += velocity; // ���W�ɂ͑��x�𑫂�
        velocity += Gravity; // ���x�ɂ͏d�͂𑫂�
        onGround = false;
        if (velocity >= 0) {
            int push = s->IsWallDown(position + VECTOR2(0, 40));
            // �W�����v�̑����`�F�b�N�́A�P�h�b�g�������āA
            // �����Ԃ��ʂ́A-1����
            if (push > 0) { // �n�ʂɐG�ꂽ�̂�
                velocity = 0.0f; // �n�ʂɐG�����瑬�x��0�ɂ���
                position.y -= push - 1; // �n�ʂ̏�ɉ����Ԃ�
                onGround = true;
            }

            push = s->IsWallDown(position + VECTOR2(39, 40));
            if (push > 0) {
                velocity = 0.0f;
                position.y -= push - 1;
                onGround = true;
            }
        }
        else {
            int push = s->IsWallUP(position + VECTOR2(0, 0));
            if (push > 0) {
                velocity = 0.0f;
                position.y += push;
            }
            push = s->IsWallUP(position + VECTOR2(39, 0));
            if (push > 0) {
                velocity = 0.0f;
                position.y += push;
            }
        }
        if (position.x - s->scroll > 400) {
            s->scroll = position.x - 400;
        }
        if (position.x - s->scroll < 0) {
            s->scroll = position.x;
        }

        if (s->IsGoal(position + VECTOR2(20, 20))) {
            goaled = true;
            Instantiate<GoalText>();
        }
    }
    // �E��Ball�𓊂���(PAD)
  // X�{�^�� PAD_INPUT_3
    if (PadInput & PAD_INPUT_3 || GetMouseInput() & MOUSE_INPUT_RIGHT) {

        if (!prevRightMouse) {
            Ball* ba = Instantiate<Ball>();   // �{�[���𐶐�
            ba->position = position;          // �v���C���[�̈ʒu�ɐ���
            ba->position.y += 5;              // �������ɂ��炷
            ba->velocity = VECTOR2(5.0f, 0.0f); // �E�����̑��x
        }
        prevRightMouse = true;
    }

    else {
        prevRightMouse = false;
    }
    // ����Ball�𓊂���(PAD)
      // A�{�^�� PAD_INPUT_1
    if (PadInput & PAD_INPUT_1 || GetMouseInput() & MOUSE_INPUT_LEFT) {

        if (!prevLeftMouse) {
            Ball* ba = Instantiate<Ball>();  // �{�[���𐶐�
            ba->position = position;
            ba->position.y += 5;
            ba->velocity = VECTOR2(-5.0f, 0.0f); // �������̑��x

        }
        prevLeftMouse = true;
    }

    else {
        prevLeftMouse = false;
    }

    // �X�N���[������

    if (position.x - s->scroll > 400) {
        s->scroll = position.x - 400;
    }

    if (position.x - s->scroll < 200) {
        s->scroll = position.x - 200;
    }
}


void Player::Draw()

{
    Stage* s = FindGameObject<Stage>();
    if (isRightClicked) {
        // �E�N���b�N����Ă���ꍇ�A�E�N���b�N�p�̉摜��`��
        DrawRectGraph(position.x - s->scroll, position.y, 0, 0, 32, 40, hImageRightClick, TRUE);
    }
    else {
        // �ʏ펞�̉摜��`��
        DrawRectGraph(position.x - s->scroll, position.y, 0, 0, 32, 40, hImage, TRUE);
        // ���C�t��\���i�Ⴆ�΁A��ʂ̏㕔�Ƀ��C�t�̃A�C�R����\������j

        if (isLeftClicked) {
            DrawRectGraph(position.x - s->scroll, position.y, 0, 0, 32, 40, hImageLeftClick, TRUE);
        }
        else {
            // �ʏ펞�̉摜��`��
            DrawRectGraph(position.x - s->scroll, position.y, 0, 0, 32, 40, hImage, TRUE);
            // ���C�t��\���i�Ⴆ�΁A��ʂ̏㕔�Ƀ��C�t�̃A�C�R����\������j

            for (int i = 0; i < life; i++) {
                //   DrawGraph(10 + i * 40, 34, life, TRUE);

                   // �����Ń��C�t�A�C�R����`�悷��R�[�h��ǉ�
                   // ��: DrawGraph(10 + i * 30, 10, lifeIconImage, TRUE);
            }
        }
    }
}
