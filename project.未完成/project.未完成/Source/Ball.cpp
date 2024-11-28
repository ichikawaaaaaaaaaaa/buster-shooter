#include "Ball.h"
#include "DxLib.h"

Ball::Ball(float startX, float startY, float speedX, float speedY) {
    position.x = startX;
    position.y = startY;
    velocity.x = speedX;
    velocity.y = speedY;
    active = true;  // �ʂ͏��߂͗L��
}

void Ball::Update()
{
    position.x += velocity.x;  // ���x���Ax�����Ɉړ�
    position.y += velocity.y;  // ���x���Ay�����Ɉړ�

    // ��ʊO�ɏo���ꍇ�A�ʂ𖳌�������
    if (position.x < 0 || position.x > 640 || position.y < 0 || position.y > 480) {
        active = false;  // ��ʊO�ɏo���疳����
    }
}

void Ball::Draw() {

    if (active) 
    {
        DrawCircle(position.x, position.y, 5, GetColor(255, 0, 0), TRUE);  // �Ԃ��ʂ�`��
    }
}