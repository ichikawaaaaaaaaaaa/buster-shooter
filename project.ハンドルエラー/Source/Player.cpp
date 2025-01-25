#include "Player.h"
#include "GoalText.h"
#include "Stage.h"
#include "Ball.h"
#include "config.h"
#include "Enemy.h"
#include "Vector2.h"
#include "GameOver.h"
#include "Jet.h"
#include "Spring.h"
#include "Walker.h"
#include "../Library/time.h"
#include <iostream>





float Gravity = 2.0f;     //�d�͉����x
float jumpHeight = 40* 2.0;  //�W�����v�̍���
float V0 = -sqrtf(3.0f * Gravity * jumpHeight);//�����v�Z

// �v���C���[�̃��C�t�ƓG�ɐG�ꂽ��
int life = 2;  // �������C�t��3
int enemyCollisionCount = 1; // �G�ɐG�ꂽ��

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
   // IsGoal = 0; //�S�[���t���O������
    goaled = 0;  //�S�[���B���t���O������
    scroll = 0;  //�X�N���[���ʒu������

    //�v���C���[�̃��C�t
    hImagelife = LoadGraph("data/image/heart.png");
    blinkCounter = 0;
    life = 3;
}

// �X�V����

void Player::Update()

{




    //<<<<<<< HEAD


    std::list<GoalText*> gls = FindGameObjects<GoalText>(); // �S�[�������擾
    for (auto g : gls) {
        //�S�[�����Ă�����S�Ă̏������~
        if (g->IsGoal == true)
        {
            return;
        }
    }






    //=======
    //>>>>>> 22785fc63763e0367779acd117806a6a2e23f18e



    GetJoypadInputState(DX_INPUT_KEY_PAD1);
    int PadInput;

    GetJoypadAnalogInput(&XInput, &YInput, DX_INPUT_KEY_PAD1);
    PadInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    // �E�N���b�N��������Ă��邩�����o
    if (GetMouseInput() & MOUSE_INPUT_RIGHT) {
        if (!prevRightClick) {  // �N���b�N���V���Ɏn�܂�����
            //isRightClicked = true;
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
            //isLeftClicked = true;
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

    //std::list<Enemy*> enemys = FindGameObjects<Enemy>();
    if (blinkCounter == 0) {
        std::list<Jet*> Jets = FindGameObjects<Jet>();
        for (Jet* j : Jets) {
            if (CircleHit(position, j->position, 56)) {

                //	�A���t�@�l�̌v�Z
                blinkCounter = 30;
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
                    std::list<GoalText*> gls = FindGameObjects<GoalText>(); // �S�[�������擾
                    for (auto g : gls) {
                        //�S�[�����Ă�����S�Ă̏������~
                        if (g->IsGoal == true)
                        {
                            return;
                        }
                    }
                }
            }
        }
        std::list<Spring*> Springs = FindGameObjects<Spring>();
        for (Spring* s : Springs) {
            if (CircleHit(position, s->position, 56)) {

                //	�A���t�@�l�̌v�Z
                blinkCounter = 30;
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
                    std::list<GoalText*> gls = FindGameObjects<GoalText>(); // �S�[�������擾
                    for (auto g : gls) {
                        //�S�[�����Ă�����S�Ă̏������~
                        if (g->IsGoal == true)
                        {
                            return;
                        }
                    }
                }
            }
        }        std::list<Walker*> Walkers = FindGameObjects<Walker>();
        for (Walker* w : Walkers) {
            if (CircleHit(position, w->position, 56)) {

                //	�A���t�@�l�̌v�Z
                blinkCounter = 30;
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
                    std::list<GoalText*> gls = FindGameObjects<GoalText>(); // �S�[�������擾
                    for (auto g : gls) {
                        //�S�[�����Ă�����S�Ă̏������~
                        if (g->IsGoal == true)
                        {
                            return;
                        }
                    }
                }
            }
        }
    }
    // ��ʊO�ɏo����Q�[���I�[�o�[
    int x = position.x;
    int y = position.y;
    if (y < 0 || y >= SCREEN_HEIGHT) {
        SceneManager::ChangeScene("GameOver");
        return; // �Q�[���I�[�o�[��̏������I��
    }

    {
        Stage* s = FindGameObject<Stage>();
        if (goaled == false) {

            //�E�ړ�
            if (CheckHitKey(KEY_INPUT_A)) {
                position.x -= 7;
                int push = s->IsWallLeft(position + VECTOR2(0, 0));
                position.x += push;
                push = s->IsWallLeft(position + VECTOR2(0, 29));
                position.x += push;
            }

            // �E�̈ړ�����(PAD)

            if (XInput > 100) {
                position.x += 7;
                int push = s->IsWallRight(position + VECTOR2(39, 0));
                position.x -= push;
                push = s->IsWallRight(position + VECTOR2(39, 39));
                position.x -= push;
            }

            //���ړ�
            if (CheckHitKey(KEY_INPUT_D)) {
                position.x += 7;
                // �E�ɕǂ����邩���ׂ�
                int push = s->IsWallRight(position + VECTOR2(39, 0));
                position.x -= push;
                push = s->IsWallRight(position + VECTOR2(39, 39));
                position.x -= push;
            }

            // ���̈ړ�����(PAD)

            if (XInput < -100) {
                position.x -= 7;
                //�L�����N�^�[�̍�����ŏՓ˃`�F�b�N

                int push = s->IsWallLeft(position + VECTOR2(0, 0));
                position.x += push;
                push = s->IsWallLeft(position + VECTOR2(0, 39));
                position.x += push;
            }


        }

        //�W�����v
        if (PadInput & PAD_INPUT_1 || CheckHitKey(KEY_INPUT_SPACE)) {
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

        position.y += velocity; // ���W�ɂ͑��x�𑫂�
        velocity += Gravity; // ���x�ɂ͏d�͂𑫂�
        onGround = false;
        if (velocity >= 0) {
            int push = s->IsWallDown(position + VECTOR2(1, 38));
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
    if (PadInput & PAD_INPUT_2 || GetMouseInput() & MOUSE_INPUT_RIGHT) {

        if (!prevRightMouse) {
            Ball* ba = Instantiate<Ball>();   // �{�[���𐶐�
            ba->position = position;          // �v���C���[�̈ʒu�ɐ���
            ba->position.y += 2;              // �������ɂ��炷
            ba->velocity = VECTOR2(10.0f, 0.0f); // �E�����̑��x
        }
        prevRightMouse = true;
    }

    else {
        prevRightMouse = false;
    }
    // ����Ball�𓊂���(PAD)
      // A�{�^�� PAD_INPUT_1
    if (PadInput & PAD_INPUT_3 || GetMouseInput() & MOUSE_INPUT_LEFT) {

        if (!prevLeftMouse) {
            Ball* ba = Instantiate<Ball>();  // �{�[���𐶐�
            ba->position = position;
            ba->position.y += 2;
            ba->velocity = VECTOR2(-10.0f, 0.0f); // �������̑��x

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
    for (int i = 0; i < life; i++) {
        DrawGraph(i * 40, 34, hImagelife, TRUE);
        // �����Ń��C�t�A�C�R����`�悷��R�[�h��ǉ�
        // ��: DrawGraph(10 + i * 30, 10, lifeIconImage, TRUE);
    }
    if (blinkCounter > 0) {
        blinkCounter--;
    }
    if (blinkCounter % 2 != 0) {
        return;
    }



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
            
            }
           
        }

    }


    //alpha += (int)(ofset * Time::DeltaTime());

    //	�O�t���[������̌o�ߎ��Ԃ��擾
    //DrawStertTimer += Time::DeltaTime();
    //	��莞��(DRAW_STERT_WAIT)�o�߂�����A�A���t�@�l�̉��Z�E���Z��؂肩����
    //if (DrawStertTimer >= DRAW_STERT_WAIT)
    //{
    //    ofset = -ofset;;
    //    DrawStertTimer = 0.5f;
    //}



