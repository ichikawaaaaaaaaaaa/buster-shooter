#include "Ball.h"
#include "DxLib.h"

Ball::Ball(float startX, float startY, float speedX, float speedY) {
    position.x = startX;
    position.y = startY;
    velocity.x = speedX;
    velocity.y = speedY;
    active = true;  // 玉は初めは有効
}

void Ball::Update()
{
    position.x += velocity.x;  // 速度分、x方向に移動
    position.y += velocity.y;  // 速度分、y方向に移動

    // 画面外に出た場合、玉を無効化する
    if (position.x < 0 || position.x > 640 || position.y < 0 || position.y > 480) {
        active = false;  // 画面外に出たら無効化
    }
}

void Ball::Draw() {

    if (active) 
    {
        DrawCircle(position.x, position.y, 5, GetColor(255, 0, 0), TRUE);  // 赤い玉を描画
    }
}