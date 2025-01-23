#include "Ball.h"
#include "config.h"
#include "Player.h"
#include "Stage.h"  // 壁判定用
#include "Vector2.h"
#include "Enemy.h"
#include "../Library/time.h"


// コンストラクタで初期化

Ball::Ball() {
    hImage = LoadGraph("data/image/Ball.png");           // 通常のボール画像（スプライトシート）

    hImageCollide = LoadGraph("data/image/Ball_Collide.png"); // 衝突後のボール画像
    position.x = 10;   // 初期X座標
    position.y = 100;  // 初期Y座標
    velocity.x = 5;    // ボールのX方向の速度
    velocity.y = 0;    // ボールのY方向の速度
    currentImage = hImage;  // 初期状態では通常のボール画像

    // アニメーションの設定
    frameWidth = 23;  // 1フレームの幅（ピクセル）
    frameHeight = 23; // 1フレームの高さ（ピクセル）
    maxFrames = 8;    // フレーム数（スプライトシートに含まれるフレーム数）
    currentFrame = 0; // 現在のフレーム
    frameTimer = 0;   // フレーム切り替えタイマー
    animationSpeed = 10; // アニメーション速度（フレームごとの更新頻度）
}

Ball::~Ball() {
    DeleteGraph(hImage);      // 通常のボール画像を解放
    DeleteGraph(hImageCollide); // 衝突後のボール画像を解放
}

void Ball::Update() {
    Stage* s = FindGameObject<Stage>();
    if (goaled) return;
    // 左の壁との衝突判定
    
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

            position.x += push;  // 衝突時に位置を修正
            DestroyMe();         // 壁と衝突したら消す
        }

        push = s->IsWallLeft(position + VECTOR2(0, 22));
        if (push != 0) {
            position.x += push;  // 衝突時に位置を修正
            DestroyMe();         // 壁と衝突したら消す
        }

        //　右の壁との衝突判定
        {
            int push = s->IsWallRight(position + VECTOR2(26, 0));
            if (push != 0) {

                position.x += push;  // 衝突時に位置を修正
                DestroyMe();         // 壁と衝突したら消す
            }

            push = s->IsWallRight(position + VECTOR2(22, 22));
            if (push != 0) {
                position.x += push;  // 衝突時に位置を修正
                DestroyMe();
            }
        }
    }

    // アニメーションの更新

    frameTimer++;
    if (frameTimer >= animationSpeed) {
        frameTimer = 0;
        currentFrame = (currentFrame + 1) % maxFrames; // フレームをループ
    }

    position.x += velocity.x;
    position.y += velocity.y;
    velocity.y += Gravity; // 必要に応じて重力を追加


    // 敵との衝突判定

    Enemy* enemy = FindGameObject<Enemy>();
    if (enemy) {
        float dx = position.x - enemy->GetPosition().x;
        float dy = position.y - enemy->GetPosition().y;
        float distance = sqrt(dx * dx + dy * dy);

        if (distance < 12) {  // 衝突判定（ボールと敵の半径が23と仮定）
            currentImage = hImageCollide;  // 衝突後のボール画像に変更
            enemy->OnCollide();           // 衝突時の処理を呼ぶ
        }
    }
}

void Ball::Draw()
{
    Stage* s = FindGameObject<Stage>();
    // 現在のフレーム位置を計算

    int frameX = (currentFrame % maxFrames) * frameWidth; // 横方向のフレーム位置
    int frameY = 0;                                      // スプライトシートが1行の場合

    // スプライトシートの指定した部分を描画

    DrawRectGraph(
        position.x - s->scroll, position.y,
        frameX, frameY, frameWidth, frameHeight,
        currentImage, TRUE
    );
}