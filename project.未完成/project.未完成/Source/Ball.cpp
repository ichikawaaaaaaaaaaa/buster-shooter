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
        return;
}
void Ball::Draw() {
    DrawGraph(position.x, position.y, hImage, TRUE); // �΂̕`��
}

