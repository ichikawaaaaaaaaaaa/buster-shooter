#include "Jet.h"
#include "Ball.h"
#include "Vector2.h"
#include "Player.h"
#include "Stage.h"
#include "config.h"
#include "GoalText.h"


// コンストラクタ
Jet::Jet()
{
    hImage = LoadGraph("data/image/Jet.png");
    // スプライトシートの幅と高さを取得
    GetGraphSize(hImage, &imageWidth, &imageHeight);
    position.x = rand() % 1000; // 初期位置 (x座標)
    position.y = rand() % 700; // 初期位置 (y座標)
    speed.x = 0.0f;
    speed.y = 0.0f;
    patternX = 0;
    patternY = 0;
    currentImage = hImage;
    // アニメーションの設定
    frameWidth = 50;  // 1フレームの幅
    frameHeight = 50; // 1フレームの高さ
    maxFrames = 2;    // 総フレーム数 (フレーム数が 2 に設定)
    currentFrame = 0; // 現在のフレーム
    frameTimer = 0;   // フレーム切り替えタイマー
    animationSpeed = 10; // アニメーション速度
    timer = 60;
    attacking = false;
    dead = false;
    deadCounter = 0;

    Jetlife = 4; //敵ライフ
}
Jet::~Jet()
{
    DeleteGraph(hImage); // 使用した画像を削除
}
void Jet::Update()
{
    std::list<GoalText*> gls = FindGameObjects<GoalText>(); // ゴール処理取得
    for (auto g : gls) {
        //ゴールしていたら全ての処理を停止
        if (g->IsGoal == true)
        {
            return;
        }
    }


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
    if (attacking) // 攻撃モードの場合
    {
        Player* player = FindGameObject<Player>();
        if (player)
        {
            VECTOR2 to = VSub(player->position, position); // プレイヤーへのベクトル
            to = VNorm(to); // 正規化
            position = VAdd(position, VScale(to, 2.0f)); // 移動処理
        }
    }
    else // 通常モードの場合
    {
        timer -= 1;
        if (timer == 0)
        {
            attacking = true; // 攻撃モード開始
            timer = rand() % (5 * 60) + 60; // 次の攻撃開始タイマーをリセット
        }
        position.x -= 2.0f; // 左方向に移動
        if (position.x < -64) // 画面外に出た場合
        {
            position.x = SCREEN_WIDTH;
            position.y = rand() % 700;
        }
    }
    // 弾との衝突判定
    std::list<Ball*> balls = FindGameObjects<Ball>();
    for (Ball* Ba : balls)
    {
        VECTOR2 sCenter = { Ba->position.x + frameWidth / 2, Ba->position.y + frameHeight / 2 }; // 弾の中心座標
        VECTOR2 bCenter = { position.x + frameWidth / 2, position.y + frameHeight / 2 }; // 敵の中心座標
        if (CircleHit(sCenter, bCenter, 20 + 8)) // 衝突半径: 弾(8) + 敵(20)
        {
            Jetlife--;
            Ba->DestroyMe();
            if (Jetlife <= 0)
            {
                dead = true; // 敵を死亡状態にする
                deadCounter = 0;
                currentFrame = maxFrames - 1; // 最後のフレームを死亡状態に設定
                return; //処理終了
            }
        }
    }
    Stage* s = FindGameObject<Stage>();
    {
        int push = s->IsWallLeft(position + VECTOR2(0, 0));
        position.x += push;
        push = s->IsWallLeft(position + VECTOR2(0, 49));
        position.x += push;
    }
    {
        int push = s->IsWallRight(position + VECTOR2(49, 0));
        position.x -= push;
        push = s->IsWallRight(position + VECTOR2(49, 49));
        position.x -= push;
    }
    if (velocity >= 0) {
        // キャラクターの位置に応じた地面衝突判定
        int push = s->IsWallDown(position + VECTOR2(0, 49 + 1)); // 例(1111)はキャラクターの高さ
        if (push > 0) { // 地面に触れた場合
            velocity = 0.0f; // 速度を0にする
            position.y -= push - 1; // 地面に押し戻す
            onGround = true;        // 地上判定をON
        }
        else {
            // 頭の衝突判定
            push = s->IsWallUP(position + VECTOR2(0, 0));
            if (push > 0) {
                velocity = 0.0f;  // 頭に衝突した場合、速度を0にする
                position.y += push; // 頭上に押し戻す
            }
            push = s->IsWallUP(position + VECTOR2(49, 0)); // 例(1111)はキャラクターの高さ
            if (push > 0) {
                velocity = 0.0f;
                position.y += push;
            }
        }
        // 右足地面判定
        push = s->IsWallDown(position + VECTOR2(49, 49)); // 例(1111)はキャラクターの高さ
        if (push > 0) {
            velocity = 0.0f;
            position.y -= push - 1;
            onGround = true; // 地面に着地したとき、地上判定をONにする
        }
    }
}
void Jet::Draw()
{
    Stage* s = FindGameObject<Stage>();
    if (s)
    {
        // 現在のフレーム位置を計算
        int frameX = (currentFrame % maxFrames) * frameWidth;
        int frameY = 0;   // 横方向のフレーム位置
        // スプライトシートの指定した部分を描画
        DrawRectGraph(
            position.x - s->scroll,
            position.y,
            frameX,
            frameY,
            frameWidth,
            frameHeight,
            currentImage,
            TRUE
        );
    }
}
VECTOR2 Jet::GetPosition() const
{
    return position;
}
void Jet::OnCollide()
{
    DestroyMe(); // 衝突時に削除
}