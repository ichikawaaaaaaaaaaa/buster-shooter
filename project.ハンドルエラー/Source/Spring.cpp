#include "Spring.h"
#include "Ball.h"
#include "Vector2.h"
#include "Player.h"
#include "Stage.h"
#include "config.h"

float SpringGravity = 0.5f;     //�d�͉����x
float SpringjumpHeight = 1 * 60.0;  //�W�����v�̍���
float SpringV0 = -sqrtf(3.0f * SpringGravity * SpringjumpHeight);//�����v�Z


// �R���X�g���N�^
Spring::Spring()
{


    hImage = LoadGraph("data/image/Spring.png");
    // �X�v���C�g�V�[�g�̕��ƍ������擾
    GetGraphSize(hImage, &imageWidth, &imageHeight);
    position.x = rand() % 1000; // �����ʒu (x���W)
    position.y = rand() % 700; // �����ʒu (y���W)
    speed.x = 4.0f;
    speed.y = 0.0f;
    patternX = 0;
    patternY = 0;
    currentImage = hImage;
    velocity = 0; //�������x
    // �A�j���[�V�����̐ݒ�
    frameWidth = 33;  // 1�t���[���̕�
    frameHeight = 40; // 1�t���[���̍���
    maxFrames = 2;    // ���t���[���� (�t���[������ 2 �ɐݒ�)
    currentFrame = 0; // ���݂̃t���[��
    frameTimer = 0;   // �t���[���؂�ւ��^�C�}�[
    animationSpeed = 10; // �A�j���[�V�������x
    timer = 60;
    attacking = false;
    dead = false;
    deadCounter = 0;

    Springlife = 3; //�G���C�t

    int PlaySoundFile(char* FileName, int PlayType);
}

Spring::~Spring()
{
    DeleteGraph(hImage); // �g�p�����摜���폜
}
void Spring::Update()
{



    if (dead) // �G�����S���Ă���ꍇ�̏���
    {

        deadCounter++;
        if (deadCounter >= 20)
        {
            DestroyMe(); // ��莞�Ԍo�ߌ�A�G���폜
        }

        return;

    }
    // �A�j���[�V�����̍X�V
    frameTimer++;
    if (frameTimer >= animationSpeed)
    {
        frameTimer = 0;
        currentFrame = (currentFrame + 1) % maxFrames; // �t���[�������[�v
    }


    // �e�Ƃ̏Փ˔���
    std::list<Ball*> balls = FindGameObjects<Ball>();
    for (Ball* Ba : balls)
    {
        VECTOR2 sCenter = { Ba->position.x + frameWidth / 2, Ba->position.y + frameHeight / 2 }; // �e�̒��S���W
        VECTOR2 bCenter = { position.x + frameWidth / 2, position.y + frameHeight / 2 }; // �G�̒��S���W
        if (CircleHit(sCenter, bCenter, 20 + 8)) // �Փ˔��a: �e(8) + �G(20)
        {
            Springlife--;
            Ba->DestroyMe();
            if (Springlife <= 0)
            {
                PlaySoundFile("data/sound/EnemyDeth.mp3", DX_PLAYTYPE_BACK);
                dead = true; // �G�����S��Ԃɂ���
                deadCounter = 0;
                currentFrame = maxFrames - 1; // �Ō�̃t���[�������S��Ԃɐݒ�
                DestroyMe(); // �e���폜
                return;
            }
        }

    }
    Stage* s = FindGameObject<Stage>();
    {
        //���[�V����
        position.x += speed.x;
        int push = s->IsWallRight(position + VECTOR2(33, 0));
        if (push > 0) {

            position.x -= push;
            speed.x = -4;
        }
        push = s->IsWallRight(position + VECTOR2(33, 20));
        if (push > 0) {
            position.x -= push;
            speed.x = -4;

        }
        push = s->IsWallLeft(position + VECTOR2(0, 20));
        if (push > 0) {
            position.x += push;
            speed.x = 4;
        }
    }
    {
        int push = s->IsWallLeft(position + VECTOR2(0, 0));
        if (push > 0) {
            position.x += push;
            speed.x = 4;
        }
    }
    //    if (velocity >= 0) {
            // �L�����N�^�[�̈ʒu�ɉ������n�ʏՓ˔���
    int push1 = s->IsWallDown(position + VECTOR2(0, 39 + 5)); // ��(1111)�̓L�����N�^�[�̍���
    int push2 = s->IsWallDown(position + VECTOR2(39, 39 + 5)); // ��(1111)�̓L�����N�^�[�̍���
    if (push1 == 0 || push2 == 0) {
        speed.x = -speed.x;
    }



    //�W�����v
    {
        if (onGround) {
            velocity = SpringV0; // ���������߂�
            onGround = false;

        }

        position.y += velocity; // ���W�ɂ͑��x�𑫂�
        velocity += SpringGravity; // ���x�ɂ͏d�͂𑫂�
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



        //   // �E���n�ʔ���
     //   push = s->IsWallDown(position + VECTOR2(49, 49)); // ��(1111)�̓L�����N�^�[�̍���
     //   if (push > 0) {
     //       velocity = 0.0f;
     //       position.y -= push - 1;
     //       onGround = true; // �n�ʂɒ��n�����Ƃ��A�n�㔻���ON�ɂ���
     //   }
    //    }
    }
}

void Spring::Draw()
{
    Stage* s = FindGameObject<Stage>();

    if (s)
    {
        // ���݂̃t���[���ʒu���v�Z
        int frameX = (currentFrame % maxFrames) * frameWidth;
        int frameY = 0;   // �������̃t���[���ʒu
        // �X�v���C�g�V�[�g�̎w�肵��������`��
        DrawRectGraph(
            position.x - s->scroll, position.y, frameX, frameY, frameWidth, frameHeight, currentImage, TRUE);
    }
}
VECTOR2 Spring::GetPosition() const
{
    return position;
}
void Spring::OnCollide()
{
    DestroyMe(); // �Փˎ��ɍ폜
}


    //Stage* s = FindGameObject<Stage>();

 // if (velocity >= 0) {
 //     // �L�����N�^�[�̈ʒu�ɉ������n�ʏՓ˔���
 //     int push = s->IsWallDown(position + VECTOR2(0, 49 + 1)); // ��(1111)�̓L�����N�^�[�̍���
 //     if (push > 0) { // �n�ʂɐG�ꂽ�ꍇ
 //         velocity = 0.0f; // ���x��0�ɂ���
 //         position.y -= push - 1; // �n�ʂɉ����߂�
 //         onGround = true;        // �n�㔻���ON
 //     }
 //   else {
 //        ���̏Փ˔���
 //         int push = s->IsWallUP(position + VECTOR2(0, 0));
 //         if (push > 0) {
 //             velocity = 0.0f;  // ���ɏՓ˂����ꍇ�A���x��0�ɂ���
 //             position.y += push; // ����ɉ����߂�
 //         }
 //         push = s->IsWallUP(position + VECTOR2(49, 0)); // ��(1111)�̓L�����N�^�[�̍���
 //         if (push > 0) {
 //             velocity = 0.0f;
 //             position.y += push;

