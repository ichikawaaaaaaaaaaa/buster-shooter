#include "Ball.h"
#include "config.h"
#include "Player.h"
#include "Stage.h"  // �ǔ���p
#include "Vector2.h"
#include "Enemy.h"

Ball::Ball() {

    hImage = LoadGraph("data/image/Ball.png");            // �ʏ�̃{�[���摜
    hImageCollide = LoadGraph("data/image/Ball_Collide.png");  // �Փˌ�̃{�[���摜

    position.x = 10;   // ����X���W
    position.y = 100;  // ����Y���W
    velocity.x = 5;    // �{�[����X�����̑��x
    velocity.y = 0;    // �{�[����Y�����̑��x
    currentImage = hImage;  // ������Ԃł͒ʏ�̃{�[���摜
}

Ball::~Ball() 
{
    DeleteGraph(hImage);      // �ʏ�̃{�[���摜�����
    DeleteGraph(hImageCollide); // �Փˌ�̃{�[���摜�����
}

void Ball::Update() {

    Stage* s = FindGameObject<Stage>();
    if (goaled) return;

    // ���̕ǂƂ̏Փ˔���

    {
        int push = s->IsWallLeft(position + VECTOR2(0, 0));

        if (push != 0) {
            position.x += push;  // �Փˎ��Ɉʒu���C��
            DestroyMe();         // �ǂƏՓ˂��������
        }

        push = s->IsWallLeft(position + VECTOR2(0, 23));

        if (push != 0) {
            position.x += push;  // �Փˎ��Ɉʒu���C��
            DestroyMe();         // �ǂƏՓ˂��������
        }
    }

    // �E�̕ǂƂ̏Փ˔���
    {

        int push = s->IsWallRight(position + VECTOR2(23, 0));

        if (push != 0) {
            position.x -= push;  // �Փˎ��Ɉʒu���C��
            DestroyMe();         // �ǂƏՓ˂��������
        }

        push = s->IsWallRight(position + VECTOR2(23, 23));

        if (push != 0) {
            position.x -= push;  // �Փˎ��Ɉʒu���C��
            DestroyMe();         // �ǂƏՓ˂��������
        }
    }

    position.x += velocity.x;
    position.y += velocity.y;
    // �K�v�ɉ����ďd�͂�ǉ�
    velocity.y += Gravity;
    // ��ʊO�ɏo����폜

    if (position.x < 0 || position.x > SCREEN_WIDTH ||
        position.y > SCREEN_HEIGHT) {
        DestroyMe();
    }


    // �G�Ƃ̏Փ˔���

    Enemy* enemy = FindGameObject<Enemy>();  // �G���擾

    
}

void Ball::Draw() {

    Stage* s = FindGameObject<Stage>();

    printf("Drawing ball at position (%f, %f) with image %d\n", 
        position.x, position.y, currentImage);  //�f�o�b�N�p (�摜ID�ƈʒu���m�F)

    DrawGraph(position.x - s->scroll, position.y, currentImage, TRUE); // ���݂̃{�[���摜��`��

}