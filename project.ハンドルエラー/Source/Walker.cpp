#include "Walker.h"
#include "Ball.h"
#include "Vector2.h"
#include "Player.h"
#include "Stage.h"
#include "config.h"
// �R���X�g���N�^
Walker::Walker()
{

 
    hImage = LoadGraph("data/image/Walker.png");
    // �X�v���C�g�V�[�g�̕��ƍ������擾
    GetGraphSize(hImage, &imageWidth, &imageHeight);
    position.x = rand() % 1000; // �����ʒu (x���W)
    position.y = rand() % 700; // �����ʒu (y���W)
    speed.x = 4.0f;
    speed.y = 0.0f;
    patternX = 0;
    patternY = 0;
    currentImage = hImage;
    // �A�j���[�V�����̐ݒ�
    frameWidth = 55;  // 1�t���[���̕�
    frameHeight = 40; // 1�t���[���̍���
    maxFrames = 2;    // ���t���[���� (�t���[������ 2 �ɐݒ�)
    currentFrame = 0; // ���݂̃t���[��
    frameTimer = 0;   // �t���[���؂�ւ��^�C�}�[
    animationSpeed = 10; // �A�j���[�V�������x
    timer = 60;
    attacking = false;
    dead = false;
    deadCounter = 0;

	Walkerlife = 4; //�G���C�t

    int PlaySoundFile(char* FileName, int PlayType);
}

Walker::~Walker()
{
    DeleteGraph(hImage); // �g�p�����摜���폜
}
void Walker::Update()
{

   

    if (dead) // �G�����S���Ă���ꍇ�̏���
    {
        PlaySoundFile("data/sound/EnemyDeth.mp3", DX_PLAYTYPE_NORMAL);
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

  //  if (attacking) // �U�����[�h�̏ꍇ
  //  {
  //      Player* player = FindGameObject<Player>();
  //      if (player)
  //      {
  //          VECTOR2 to = VSub(player->position, position); // �v���C���[�ւ̃x�N�g��
  //          to = VNorm(to); // ���K��
  //          position = VAdd(position, VScale(to, 2.0f)); // �ړ�����
  //      }
  //  }
   // else // �ʏ탂�[�h�̏ꍇ
   // {
   //     timer -= 1;
   //     if (timer == 0)
   //     {
   //         attacking = true; // �U�����[�h�J�n
   //         timer = rand() % (5 * 60) + 60; // ���̍U���J�n�^�C�}�[�����Z�b�g
   //     }
   //     position.x -= 2.0f; // �������Ɉړ�
   //     if (position.x < -64) // ��ʊO�ɏo���ꍇ
   //     {
   //         position.x = SCREEN_WIDTH;
   //         position.y = rand() % 700;
   //     }
   // }
    // �e�Ƃ̏Փ˔���
    std::list<Ball*> balls = FindGameObjects<Ball>();
    for (Ball* Ba : balls)
    {
        VECTOR2 sCenter = { Ba->position.x + frameWidth / 2, Ba->position.y + frameHeight / 2 }; // �e�̒��S���W
        VECTOR2 bCenter = { position.x + frameWidth / 2, position.y + frameHeight / 2 }; // �G�̒��S���W
        if (CircleHit(sCenter, bCenter, 20 + 8)) // �Փ˔��a: �e(8) + �G(20)
        {
            Walkerlife--;
            Ba->DestroyMe();
            if (Walkerlife <= 0)
            {
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
        int push = s->IsWallRight(position + VECTOR2(55, 0));
        if (push > 0) {
            
            position.x -= push;
            speed.x = -4;
       }
        push = s->IsWallRight(position + VECTOR2(55, 20));
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
        //   // �E���n�ʔ���
     //   push = s->IsWallDown(position + VECTOR2(49, 49)); // ��(1111)�̓L�����N�^�[�̍���
     //   if (push > 0) {
     //       velocity = 0.0f;
     //       position.y -= push - 1;
     //       onGround = true; // �n�ʂɒ��n�����Ƃ��A�n�㔻���ON�ɂ���
     //   }
//    }
}

void Walker::Draw()
{
    Stage* s = FindGameObject<Stage>();
   
    if (s)
    {
        // ���݂̃t���[���ʒu���v�Z
        int frameX = (currentFrame % maxFrames) * frameWidth;
        int frameY = 0;   // �������̃t���[���ʒu
        // �X�v���C�g�V�[�g�̎w�肵��������`��
        DrawRectGraph(
            position.x - s->scroll,position.y,frameX,frameY, frameWidth,frameHeight,currentImage,TRUE);
    }
}
VECTOR2 Walker::GetPosition() const
{
    return position;
}
void Walker::OnCollide()
{
    DestroyMe(); // �Փˎ��ɍ폜
}