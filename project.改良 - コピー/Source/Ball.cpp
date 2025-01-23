#include "Ball.h"
#include "config.h"
#include "Player.h"
#include "Stage.h"  // 壁判定用
#include "Vector2.h"
#include "Enemy.h"

Ball::Ball() {

    hImage = LoadGraph("data/image/Ball.png");            // 通常のボール画像
    hImageCollide = LoadGraph("data/image/Ball_Collide.png");  // 衝突後のボール画像

    position.x = 10;   // 初期X座標
    position.y = 100;  // 初期Y座標
    velocity.x = 5;    // ボールのX方向の速度
    velocity.y = 0;    // ボールのY方向の速度
    currentImage = hImage;  // 初期状態では通常のボール画像
}

Ball::~Ball() 
{
    DeleteGraph(hImage);      // 通常のボール画像を解放
    DeleteGraph(hImageCollide); // 衝突後のボール画像を解放
}

void Ball::Update() {

    Stage* s = FindGameObject<Stage>();
    if (goaled) return;

    // 左の壁との衝突判定

    {
        int push = s->IsWallLeft(position + VECTOR2(0, 0));

        if (push != 0) {
            position.x += push;  // 衝突時に位置を修正
            DestroyMe();         // 壁と衝突したら消す
        }

        push = s->IsWallLeft(position + VECTOR2(0, 23));

        if (push != 0) {
            position.x += push;  // 衝突時に位置を修正
            DestroyMe();         // 壁と衝突したら消す
        }
    }

    // 右の壁との衝突判定
    {

        int push = s->IsWallRight(position + VECTOR2(23, 0));

        if (push != 0) {
            position.x -= push;  // 衝突時に位置を修正
            DestroyMe();         // 壁と衝突したら消す
        }

        push = s->IsWallRight(position + VECTOR2(23, 23));

        if (push != 0) {
            position.x -= push;  // 衝突時に位置を修正
            DestroyMe();         // 壁と衝突したら消す
        }
    }

    position.x += velocity.x;
    position.y += velocity.y;
    // 必要に応じて重力を追加
    velocity.y += Gravity;
    // 画面外に出たら削除

    if (position.x < 0 || position.x > SCREEN_WIDTH ||
        position.y > SCREEN_HEIGHT) {
        DestroyMe();
    }


    // 敵との衝突判定

    Enemy* enemy = FindGameObject<Enemy>();  // 敵を取得

    
}

void Ball::Draw() {

    Stage* s = FindGameObject<Stage>();

    printf("Drawing ball at position (%f, %f) with image %d\n", 
        position.x, position.y, currentImage);  //デバック用 (画像IDと位置を確認)

    DrawGraph(position.x - s->scroll, position.y, currentImage, TRUE); // 現在のボール画像を描画

}