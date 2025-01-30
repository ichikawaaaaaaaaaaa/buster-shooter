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

float Gravity = 0.5f;     //�d�͉����x
float jumpHeight = 40 * 1.5;  //�W�����v�̍���
float V0 = -sqrtf(3.0f * Gravity * jumpHeight);//�����v�Z

// �v���C���[�̃��C�t�ƓG�ɐG�ꂽ��
//int life = 3;  // �������C�t��3
//int enemyCollisionCount = 1; // �G�ɐG�ꂽ��

// �R���X�g���N�^

Player::Player()

{
    hImage = LoadGraph("data/image/Player.png");//�L�����摜�̓ǂݍ���
    hImageMoveRight = LoadGraph("data/image/run.png");
    hImageMoveLeft = LoadGraph("data/image/run.png");
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
    //blinkCounter = 0;
    life = 3;

	blinkCounter = 0;  // �v���C���[�̓_�ŏ����p�J�E���^�[
}

// �X�V����

void Player::Update()

{
    //<<<<<<< HEAD
   // std::list<GoalText*> gls = FindGameObjects<GoalText>(); // �S�[�������擾

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

    std::list<GoalText*> gls = FindGameObjects<GoalText>(); // �S�[�������擾
    for (auto g : gls) {
        //�S�[�����Ă�����S�Ă̏������~
        if (g->IsGoal == true)
        {
            return;
        }
    }

    // ��ʊO�ɏo����Q�[���I�[�o�[
    int x = position.x;
    int y = position.y;
    if (y < 0 || y >= SCREEN_HEIGHT) {
        PlaySoundFile("data/sound/GameOver.mp3", DX_PLAYTYPE_NORMAL);
        SceneManager::ChangeScene("GameOver");
        return; // �Q�[���I�[�o�[��̏������I��
    }


    {
        Stage* s = FindGameObject<Stage>();
        if (goaled == false) {
            isMoving = false; // ���t���[��������
            // �E�ړ��i�L�[�{�[�h�j
            if (CheckHitKey(KEY_INPUT_D)) {
                position.x += 5;
                int push = s->IsWallRight(position + VECTOR2(39, 0));
                position.x -= push;
                push = s->IsWallRight(position + VECTOR2(39, 39));
                position.x -= push;
                isMoving = true;
            }
            // �E�ړ��i�p�b�h�j
            if (XInput > 100) {
                position.x += 5;
                int push = s->IsWallRight(position + VECTOR2(39, 0));
                position.x -= push;
                push = s->IsWallRight(position + VECTOR2(39, 39));
                position.x -= push;
                isMoving = true;
            }
            // ���ړ��i�L�[�{�[�h�j
            if (CheckHitKey(KEY_INPUT_A)) {
                position.x -= 5;
                int push = s->IsWallLeft(position + VECTOR2(0, 0));
                position.x += push;
                push = s->IsWallLeft(position + VECTOR2(0, 29));
                position.x += push;
                isMoving = true;
            }
            // ���ړ��i�p�b�h�j
            if (XInput < -100) {
                position.x -= 5;
                int push = s->IsWallLeft(position + VECTOR2(0, 0));
                position.x += push;
                push = s->IsWallLeft(position + VECTOR2(0, 39));
                position.x += push;
                isMoving = true;
            }
        }
        // �A�j���[�V�����̍X�V
        //animationCounter++;
        if (animationCounter >= animationSpeed) {
            animationCounter = 0;
            if (isMoving) {
                animationFrame = (animationFrame + 1) % 2;  // �ړ�����2�t���[���A�j���[�V����
            }
           else {
                animationFrame = (animationFrame + 1) % 2;  // ��~����2�t���[���A�j���[�V����
           }
       }


        //�W�����v
        if (PadInput & PAD_INPUT_1 || CheckHitKey(KEY_INPUT_SPACE)) {
            if (prevJumpKey == false) {
                if (onGround) {
                    PlaySoundFile("data/sound/Jump.mp3", DX_PLAYTYPE_BACK);
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
            PlaySoundFile("data/sound/Attack.mp3", DX_PLAYTYPE_BACK);
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
            PlaySoundFile("data/sound/Attack.mp3", DX_PLAYTYPE_BACK);
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
    //�Փˌ�̏����x������
    if (blinkCounter > 0) {
        blinkCounter--;
        return; // �Փ˔�����s��Ȃ�
    }

    // �G�ƏՓ˂������ǂ����𔻒肷��t���O
    bool collided = false;
    // �v���C���[�ƓG�̏Փ˔���
    if (blinkCounter == 0) {
        std::list<Jet*> Jets = FindGameObjects<Jet>();
        for (Jet* j : Jets) {
            if (CircleHit(position, j->position, 45)) {
                // 1�񂾂����C�t�����炷
                if (!collided) {
                    collided = true;
                    life--; // ���C�t��1���炷
                    // ���C�t��0�ɂȂ�����Q�[���I�[�o�[
                    if (life <= 0) {
                        SceneManager::ChangeScene("GameOver");
                        return; // �Q�[���I�[�o�[��̏������I��
                    }
                    blinkCounter = 50;
                    isBlinking = true;
                }
            }
        }
    }
    // ���̓G�iSpring��Walker�j�ɑ΂���Փ˔�������l�ɍs��
    std::list<Spring*> Springs = FindGameObjects<Spring>();
    for (Spring* s : Springs) {
        if (CircleHit(position, s->position, 37)) {
            if (!collided) {
                collided = true;
                life--; // ���C�t��1���炷
                if (life <= 0) {
                    SceneManager::ChangeScene("GameOver");
                    return; // �Q�[���I�[�o�[��̏������I��
                }
                blinkCounter = 50;
                isBlinking = true;
            }
        }
    }
    // ���̓G�iWalker�j�ɑ΂���Փ˔���
    std::list<Walker*> Walkers = FindGameObjects<Walker>();
    for (Walker* w : Walkers) {
        if (CircleHit(position, w->position, 34)) {
            if (!collided) {
                collided = true;
                life--; // ���C�t��1���炷
                if (life <= 0) {
                    SceneManager::ChangeScene("GameOver");
                    return; // �Q�[���I�[�o�[��̏������I��
                }
                blinkCounter = 50;
                isBlinking = true;
            }
        }
    }



}



void Player::Draw()


{
// ���C�t�A�C�R����`��i�E���獶�Ɍ��炷�j
    for (int i = 0; i < 3; i++) {
        // �ő�3�̃n�[�g
        if (i < life) {
            // ����ɔz�u���邽�߁A(i * 40)�ŉ��ʒu������
            // �E���������悤�ɂ��邽�߁A(i)���g���ĉE����z�u
            DrawGraph(40 * i, 34, hImagelife, TRUE);  // ����ɔz�u
        }

        if (blinkCounter % 5 != 0) {
            return;
        }


        Stage* s = FindGameObject<Stage>();

        int spriteWidth = 32;  // �摜�̕�
        int spriteHeight = 40; // �摜�̍���
        int spriteX = animationFrame * spriteWidth; // �A�j���[�V������X���W
        int imageToDraw = hImage;  // �f�t�H���g�̗�����ԉ摜



        // ���ړ����Ă���ꍇ�A�ړ��p�A�j���[�V������K�p
        if (XInput > 100 || CheckHitKey(KEY_INPUT_D)) {
            imageToDraw = hImageMoveRight; // �E�ړ��̉摜
        }
        else if (XInput < -100 || CheckHitKey(KEY_INPUT_A)) {
            imageToDraw = hImageMoveLeft; // ���ړ��̉摜
        }
        DrawRectGraph(position.x - s->scroll, position.y, spriteX, 0, spriteWidth, spriteHeight, imageToDraw, TRUE);
    
    // �N���b�N��Ԃ�D��
    if (isRightClicked) {
        imageToDraw = hImageRightClick;
    }
    else if (isLeftClicked) {
        imageToDraw = hImageLeftClick;
    }
    // �摜��`��i�A�j���[�V�����t���[���l���j
    DrawRectGraph(position.x - s->scroll, position.y, spriteX, 0, spriteWidth, spriteHeight, imageToDraw, TRUE);

   
    }
}

