#include "Ball.h"
#include "config.h"
#include "Stage.h" // �ǔ���p

Ball::Ball() {
    hImage = LoadGraph("data/image/Stone.png");
    position.x = 10;   // ����X���W
    position.y = 100;  // ����Y���W
}
Ball::~Ball() {
    DeleteGraph(hImage); // �摜�̉��
}
void Ball::Update() {
    // �΂̈ړ�����
    position.x += 5.0f;
    // �X�e�[�W�̕ǔ�����擾
   // Stage* stage = FindGameObject<Stage>();
    //f (stage && stage->IsWall(position)) {
        // �ǂɓ��������ꍇ�A�΂��폜
       // DestroyMe();
    //} 

    Stage* stage = FindGameObject<Stage>();
    if (stage && stage->IsWall(position)) {
        // �ǂɓ��������ꍇ�A�{�[�����폜
        DestroyMe();
        return;
    }
    //��ʊO�ɏo���ꍇ�̍폜
    if (position.x > SCREEN_WIDTH || position.y > SCREEN_HEIGHT || position.x < 0 || position.y < 0) {
        DestroyMe();
    }
}

//�`�揈��
void Ball::Draw() {
    DrawGraph(position.x, position.y, hImage, TRUE); // �΂̕`��
}

