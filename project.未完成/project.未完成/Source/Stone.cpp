#include "Stone.h"
#include "config.h"
#include "Stage.h" // �ǔ���p
Stone::Stone() {
    hImage = LoadGraph("data/image/Stone.png");
    position.x = 10;   // ����X���W
    position.y = 100;  // ����Y���W
}
Stone::~Stone() {
    DeleteGraph(hImage); // �摜�̉��
}
void Stone::Update() {
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
void Stone::Draw() {
    DrawGraph(position.x, position.y, hImage, TRUE); // �΂̕`��
}