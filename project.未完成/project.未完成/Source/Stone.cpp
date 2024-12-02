#include "Stone.h"
#include "config.h"
#include "Stage.h" // 壁判定用
Stone::Stone() {
    hImage = LoadGraph("data/image/Stone.png");
    position.x = 10;   // 初期X座標
    position.y = 100;  // 初期Y座標
}
Stone::~Stone() {
    DeleteGraph(hImage); // 画像の解放
}
void Stone::Update() {
    // 石の移動処理
    position.x += 5.0f;
    // ステージの壁判定を取得
   // Stage* stage = FindGameObject<Stage>();
    //f (stage && stage->IsWall(position)) {
        // 壁に当たった場合、石を削除
       // DestroyMe();
    //} 
        return;
}
void Stone::Draw() {
    DrawGraph(position.x, position.y, hImage, TRUE); // 石の描画
}