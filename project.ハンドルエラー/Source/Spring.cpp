#include "Spring.h"
#include "Ball.h"
#include "Vector2.h"
#include "Player.h"
#include "Stage.h"
#include "config.h"

float SpringGravity = 0.5f;     //重力加速度
float SpringjumpHeight = 1 * 60.0;  //ジャンプの高さ
float SpringV0 = -sqrtf(3.0f * SpringGravity * SpringjumpHeight);//初速計算


// コンストラクタ
Spring::Spring()
{


    hImage = LoadGraph("data/image/Spring.png");
    // スプライトシートの幅と高さを取得
    GetGraphSize(hImage, &imageWidth, &imageHeight);
    position.x = rand() % 1000; // 初期位置 (x座標)
    position.y = rand() % 700; // 初期位置 (y座標)
    speed.x = 4.0f;
    speed.y = 0.0f;
    patternX = 0;
    patternY = 0;
    currentImage = hImage;
    velocity = 0; //初期速度
    // アニメーションの設定
    frameWidth = 33;  // 1フレームの幅
    frameHeight = 40; // 1フレームの高さ
    maxFrames = 2;    // 総フレーム数 (フレーム数が 2 に設定)
    currentFrame = 0; // 現在のフレーム
    frameTimer = 0;   // フレーム切り替えタイマー
    animationSpeed = 10; // アニメーション速度
    timer = 60;
    attacking = false;
    dead = false;
    deadCounter = 0;

    Springlife = 3; //敵ライフ

    int PlaySoundFile(char* FileName, int PlayType);
}

Spring::~Spring()
{
    DeleteGraph(hImage); // 使用した画像を削除
}
void Spring::Update()
{



    if (dead) // 敵が死亡している場合の処理
    {

        deadCounter++;
        if (deadCounter >= 20)
        {
            DestroyMe(); // 一定時間経過後、敵を削除
        }

        return;

    }
    // アニメーションの更新
    frameTimer++;
    if (frameTimer >= animationSpeed)
    {
        frameTimer = 0;
        currentFrame = (currentFrame + 1) % maxFrames; // フレームをループ
    }


    // 弾との衝突判定
    std::list<Ball*> balls = FindGameObjects<Ball>();
    for (Ball* Ba : balls)
    {
        VECTOR2 sCenter = { Ba->position.x + frameWidth / 2, Ba->position.y + frameHeight / 2 }; // 弾の中心座標
        VECTOR2 bCenter = { position.x + frameWidth / 2, position.y + frameHeight / 2 }; // 敵の中心座標
        if (CircleHit(sCenter, bCenter, 20 + 8)) // 衝突半径: 弾(8) + 敵(20)
        {
            Springlife--;
            Ba->DestroyMe();
            if (Springlife <= 0)
            {
                PlaySoundFile("data/sound/EnemyDeth.mp3", DX_PLAYTYPE_BACK);
                dead = true; // 敵を死亡状態にする
                deadCounter = 0;
                currentFrame = maxFrames - 1; // 最後のフレームを死亡状態に設定
                DestroyMe(); // 弾を削除
                return;
            }
        }

    }
    Stage* s = FindGameObject<Stage>();
    {
        //モーション
        position.x += speed.x;
        int push = s->IsWallRight(position + VECTOR2(33, 0));
        if (push > 0) {

            position.x -= push;
            speed.x = -4;
        }
        push = s->IsWallRight(position + VECTOR2(33, 20));
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
            // キャラクターの位置に応じた地面衝突判定
    int push1 = s->IsWallDown(position + VECTOR2(0, 39 + 5)); // 例(1111)はキャラクターの高さ
    int push2 = s->IsWallDown(position + VECTOR2(39, 39 + 5)); // 例(1111)はキャラクターの高さ
    if (push1 == 0 || push2 == 0) {
        speed.x = -speed.x;
    }



    //ジャンプ
    {
        if (onGround) {
            velocity = SpringV0; // 初速を決める
            onGround = false;

        }

        position.y += velocity; // 座標には速度を足す
        velocity += SpringGravity; // 速度には重力を足す
        if (velocity >= 0) {
            int push = s->IsWallDown(position + VECTOR2(1, 38));
            // ジャンプの足元チェックは、１ドット下を見て、
            // 押し返す量は、-1する
            if (push > 0) { // 地面に触れたので
                velocity = 0.0f; // 地面に触ったら速度を0にする
                position.y -= push - 1; // 地面の上に押し返す
                onGround = true;
            }

            push = s->IsWallDown(position + VECTOR2(39, 40));
            if (push > 0) {
                velocity = 0.0f;
                position.y -= push - 1;
                onGround = true;
            }
        }
        else {
            int push = s->IsWallUP(position + VECTOR2(0, 0));
            if (push > 0) {
                velocity = 0.0f;
                position.y += push;
            }
            push = s->IsWallUP(position + VECTOR2(39, 0));
            if (push > 0) {
                velocity = 0.0f;
                position.y += push;
            }
        }



        //   // 右足地面判定
     //   push = s->IsWallDown(position + VECTOR2(49, 49)); // 例(1111)はキャラクターの高さ
     //   if (push > 0) {
     //       velocity = 0.0f;
     //       position.y -= push - 1;
     //       onGround = true; // 地面に着地したとき、地上判定をONにする
     //   }
    //    }
    }
}

void Spring::Draw()
{
    Stage* s = FindGameObject<Stage>();

    if (s)
    {
        // 現在のフレーム位置を計算
        int frameX = (currentFrame % maxFrames) * frameWidth;
        int frameY = 0;   // 横方向のフレーム位置
        // スプライトシートの指定した部分を描画
        DrawRectGraph(
            position.x - s->scroll, position.y, frameX, frameY, frameWidth, frameHeight, currentImage, TRUE);
    }
}
VECTOR2 Spring::GetPosition() const
{
    return position;
}
void Spring::OnCollide()
{
    DestroyMe(); // 衝突時に削除
}


    //Stage* s = FindGameObject<Stage>();

 // if (velocity >= 0) {
 //     // キャラクターの位置に応じた地面衝突判定
 //     int push = s->IsWallDown(position + VECTOR2(0, 49 + 1)); // 例(1111)はキャラクターの高さ
 //     if (push > 0) { // 地面に触れた場合
 //         velocity = 0.0f; // 速度を0にする
 //         position.y -= push - 1; // 地面に押し戻す
 //         onGround = true;        // 地上判定をON
 //     }
 //   else {
 //        頭の衝突判定
 //         int push = s->IsWallUP(position + VECTOR2(0, 0));
 //         if (push > 0) {
 //             velocity = 0.0f;  // 頭に衝突した場合、速度を0にする
 //             position.y += push; // 頭上に押し戻す
 //         }
 //         push = s->IsWallUP(position + VECTOR2(49, 0)); // 例(1111)はキャラクターの高さ
 //         if (push > 0) {
 //             velocity = 0.0f;
 //             position.y += push;

