#include "Ball.h"
#include "config.h"
#include "Player.h"
#include "Stage.h"  // �ǔ���p
#include "Vector2.h"
#include "Enemy.h"
#include "../Library/time.h"


// �R���X�g���N�^�ŏ�����

Ball::Ball() {
    hImage = LoadGraph("data/image/Ball.png");           // �ʏ�̃{�[���摜�i�X�v���C�g�V�[�g�j

    hImageCollide = LoadGraph("data/image/Ball_Collide.png"); // �Փˌ�̃{�[���摜
    position.x = 10;   // ����X���W
    position.y = 100;  // ����Y���W
    velocity.x = 5;    // �{�[����X�����̑��x
    velocity.y = 0;    // �{�[����Y�����̑��x
    currentImage = hImage;  // ������Ԃł͒ʏ�̃{�[���摜

    // �A�j���[�V�����̐ݒ�
    frameWidth = 23;  // 1�t���[���̕��i�s�N�Z���j
    frameHeight = 23; // 1�t���[���̍����i�s�N�Z���j
    maxFrames = 8;    // �t���[�����i�X�v���C�g�V�[�g�Ɋ܂܂��t���[�����j
    currentFrame = 0; // ���݂̃t���[��
    frameTimer = 0;   // �t���[���؂�ւ��^�C�}�[
    animationSpeed = 10; // �A�j���[�V�������x�i�t���[�����Ƃ̍X�V�p�x�j
}

Ball::~Ball() {
    DeleteGraph(hImage);      // �ʏ�̃{�[���摜�����
    DeleteGraph(hImageCollide); // �Փˌ�̃{�[���摜�����
}

void Ball::Update() {
    Stage* s = FindGameObject<Stage>();
    if (goaled) return;
    // ���̕ǂƂ̏Փ˔���
    
    {
        timer += Time::DeltaTime();
<<<<<<< HEAD
        if (timer >= 1.1f)
=======
        if (timer >= 1.0f)
>>>>>>> 55a783797ac8b7ff05f08afb14431916d62ecdf2
        {
            DestroyMe();
        }
        int push = s->IsWallLeft(position + VECTOR2(0, 0));
        if (push != 0) {

            position.x += push;  // �Փˎ��Ɉʒu���C��
            DestroyMe();         // �ǂƏՓ˂��������
        }

        push = s->IsWallLeft(position + VECTOR2(0, 22));
        if (push != 0) {
            position.x += push;  // �Փˎ��Ɉʒu���C��
            DestroyMe();         // �ǂƏՓ˂��������
        }

        //�@�E�̕ǂƂ̏Փ˔���
        {
            int push = s->IsWallRight(position + VECTOR2(26, 0));
            if (push != 0) {

                position.x += push;  // �Փˎ��Ɉʒu���C��
                DestroyMe();         // �ǂƏՓ˂��������
            }

            push = s->IsWallRight(position + VECTOR2(22, 22));
            if (push != 0) {
                position.x += push;  // �Փˎ��Ɉʒu���C��
                DestroyMe();
            }
        }
    }

    // �A�j���[�V�����̍X�V

    frameTimer++;
    if (frameTimer >= animationSpeed) {
        frameTimer = 0;
        currentFrame = (currentFrame + 1) % maxFrames; // �t���[�������[�v
    }

    position.x += velocity.x;
    position.y += velocity.y;
    velocity.y += Gravity; // �K�v�ɉ����ďd�͂�ǉ�


    // �G�Ƃ̏Փ˔���

    Enemy* enemy = FindGameObject<Enemy>();
    if (enemy) {
        float dx = position.x - enemy->GetPosition().x;
        float dy = position.y - enemy->GetPosition().y;
        float distance = sqrt(dx * dx + dy * dy);

        if (distance < 12) {  // �Փ˔���i�{�[���ƓG�̔��a��23�Ɖ���j
            currentImage = hImageCollide;  // �Փˌ�̃{�[���摜�ɕύX
            enemy->OnCollide();           // �Փˎ��̏������Ă�
        }
    }
}

void Ball::Draw()
{
    Stage* s = FindGameObject<Stage>();
    // ���݂̃t���[���ʒu���v�Z

    int frameX = (currentFrame % maxFrames) * frameWidth; // �������̃t���[���ʒu
    int frameY = 0;                                      // �X�v���C�g�V�[�g��1�s�̏ꍇ

    // �X�v���C�g�V�[�g�̎w�肵��������`��

    DrawRectGraph(
        position.x - s->scroll, position.y,
        frameX, frameY, frameWidth, frameHeight,
        currentImage, TRUE
    );
}