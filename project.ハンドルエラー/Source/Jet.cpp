#include "Jet.h"
#include "Ball.h"
#include "Vector2.h"
#include "Player.h"
#include "Stage.h"
#include "config.h"
#include "GoalText.h"


// �R���X�g���N�^
Jet::Jet()
{
    hImage = LoadGraph("data/image/Jet.png");
    // �X�v���C�g�V�[�g�̕��ƍ������擾
    GetGraphSize(hImage, &imageWidth, &imageHeight);
    position.x = rand() % 1000; // �����ʒu (x���W)
    position.y = rand() % 700; // �����ʒu (y���W)
    speed.x = 0.0f;
    speed.y = 0.0f;
    patternX = 0;
    patternY = 0;
    currentImage = hImage;
    // �A�j���[�V�����̐ݒ�
    frameWidth = 50;  // 1�t���[���̕�
    frameHeight = 50; // 1�t���[���̍���
    maxFrames = 2;    // ���t���[���� (�t���[������ 2 �ɐݒ�)
    currentFrame = 0; // ���݂̃t���[��
    frameTimer = 0;   // �t���[���؂�ւ��^�C�}�[
    animationSpeed = 10; // �A�j���[�V�������x
    timer = 60;
    attacking = false;
    dead = false;
    deadCounter = 0;

    Jetlife = 4; //�G���C�t
}
Jet::~Jet()
{
    DeleteGraph(hImage); // �g�p�����摜���폜
}
void Jet::Update()
{
    std::list<GoalText*> gls = FindGameObjects<GoalText>(); // �S�[�������擾
    for (auto g : gls) {
        //�S�[�����Ă�����S�Ă̏������~
        if (g->IsGoal == true)
        {
            return;
        }
    }


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
    if (attacking) // �U�����[�h�̏ꍇ
    {
        Player* player = FindGameObject<Player>();
        if (player)
        {
            VECTOR2 to = VSub(player->position, position); // �v���C���[�ւ̃x�N�g��
            to = VNorm(to); // ���K��
            position = VAdd(position, VScale(to, 2.0f)); // �ړ�����
        }
    }
    else // �ʏ탂�[�h�̏ꍇ
    {
        timer -= 1;
        if (timer == 0)
        {
            attacking = true; // �U�����[�h�J�n
            timer = rand() % (5 * 60) + 60; // ���̍U���J�n�^�C�}�[�����Z�b�g
        }
        position.x -= 2.0f; // �������Ɉړ�
        if (position.x < -64) // ��ʊO�ɏo���ꍇ
        {
            position.x = SCREEN_WIDTH;
            position.y = rand() % 700;
        }
    }
    // �e�Ƃ̏Փ˔���
    std::list<Ball*> balls = FindGameObjects<Ball>();
    for (Ball* Ba : balls)
    {
        VECTOR2 sCenter = { Ba->position.x + frameWidth / 2, Ba->position.y + frameHeight / 2 }; // �e�̒��S���W
        VECTOR2 bCenter = { position.x + frameWidth / 2, position.y + frameHeight / 2 }; // �G�̒��S���W
        if (CircleHit(sCenter, bCenter, 20 + 8)) // �Փ˔��a: �e(8) + �G(20)
        {
            Jetlife--;
            Ba->DestroyMe();
            if (Jetlife <= 0)
            {
                dead = true; // �G�����S��Ԃɂ���
                deadCounter = 0;
                currentFrame = maxFrames - 1; // �Ō�̃t���[�������S��Ԃɐݒ�
                return; //�����I��
            }
        }
    }
    Stage* s = FindGameObject<Stage>();
    {
        int push = s->IsWallLeft(position + VECTOR2(0, 0));
        position.x += push;
        push = s->IsWallLeft(position + VECTOR2(0, 49));
        position.x += push;
    }
    {
        int push = s->IsWallRight(position + VECTOR2(49, 0));
        position.x -= push;
        push = s->IsWallRight(position + VECTOR2(49, 49));
        position.x -= push;
    }
    if (velocity >= 0) {
        // �L�����N�^�[�̈ʒu�ɉ������n�ʏՓ˔���
        int push = s->IsWallDown(position + VECTOR2(0, 49 + 1)); // ��(1111)�̓L�����N�^�[�̍���
        if (push > 0) { // �n�ʂɐG�ꂽ�ꍇ
            velocity = 0.0f; // ���x��0�ɂ���
            position.y -= push - 1; // �n�ʂɉ����߂�
            onGround = true;        // �n�㔻���ON
        }
        else {
            // ���̏Փ˔���
            push = s->IsWallUP(position + VECTOR2(0, 0));
            if (push > 0) {
                velocity = 0.0f;  // ���ɏՓ˂����ꍇ�A���x��0�ɂ���
                position.y += push; // ����ɉ����߂�
            }
            push = s->IsWallUP(position + VECTOR2(49, 0)); // ��(1111)�̓L�����N�^�[�̍���
            if (push > 0) {
                velocity = 0.0f;
                position.y += push;
            }
        }
        // �E���n�ʔ���
        push = s->IsWallDown(position + VECTOR2(49, 49)); // ��(1111)�̓L�����N�^�[�̍���
        if (push > 0) {
            velocity = 0.0f;
            position.y -= push - 1;
            onGround = true; // �n�ʂɒ��n�����Ƃ��A�n�㔻���ON�ɂ���
        }
    }
}
void Jet::Draw()
{
    Stage* s = FindGameObject<Stage>();
    if (s)
    {
        // ���݂̃t���[���ʒu���v�Z
        int frameX = (currentFrame % maxFrames) * frameWidth;
        int frameY = 0;   // �������̃t���[���ʒu
        // �X�v���C�g�V�[�g�̎w�肵��������`��
        DrawRectGraph(
            position.x - s->scroll,
            position.y,
            frameX,
            frameY,
            frameWidth,
            frameHeight,
            currentImage,
            TRUE
        );
    }
}
VECTOR2 Jet::GetPosition() const
{
    return position;
}
void Jet::OnCollide()
{
    DestroyMe(); // �Փˎ��ɍ폜
}