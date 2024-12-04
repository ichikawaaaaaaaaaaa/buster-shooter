#include "Ball.h"
#include "config.h"
#include "Stage.h" // 壁判定用

Ball::Ball() {
    hImage = LoadGraph("data/image/Stone.png");
    position.x = 10;   // 初期X座標
    position.y = 100;  // 初期Y座標
}
Ball::~Ball() {
    DeleteGraph(hImage); // 画像の解放
}
void Ball::Update() {
    // 石の移動処理
    position.x += 5.0f;
    // ステージの壁判定を取得
   // Stage* stage = FindGameObject<Stage>();
    //f (stage && stage->IsWall(position)) {
        // 壁に当たった場合、石を削除
       // DestroyMe();
    //} 

    Stage* stage = FindGameObject<Stage>();
    if (stage && stage->IsWall(position)) {
        // 壁に当たった場合、ボールを削除
        DestroyMe();
        return;
    }
    //画面外に出た場合の削除
    if (position.x > SCREEN_WIDTH || position.y > SCREEN_HEIGHT || position.x < 0 || position.y < 0) {
        DestroyMe();
    }
}

//描画処理
void Ball::Draw() {
    DrawGraph(position.x, position.y, hImage, TRUE); // 石の描画
}

