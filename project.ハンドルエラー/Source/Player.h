#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"
#include <DxLib.h>

//GameObject クラスの継承
class Player : public GameObject {
public:
    Player(); // コンストラクタ
    //~Player(); // デストラクタ（必要に応じてコメントアウトを外してください）
    void Update() override; // プレイヤーの更新処理
    void Draw() override;   // プレイヤーの描画処理
    void Animation();       // プレイヤーのアニメーション処理
    int hImage;             // プレイヤーの画像ハンドル
    int hImageKEY_D_Click;
    int hImageKEY_A_Click;
    int hImageRightClick;
    int hImageLeftClick;
    int hImagelife;
    VECTOR2 position;       // プレイヤーの座標（Vector2）
    float velocity;         // 垂直方向の速度
    bool prevJumpKey;       // 前フレームのジャンプキーの状態
    bool onGround;          // プレイヤーが地面に接しているか
    int IsGdoal;             // ゴールフラグ
    int goaled;             // ゴール達成フラグ
    int scroll;             // スクロール位置（仮想）
    int patternX;           // アニメーション用Xパターン
    int patternY;           // アニメーション用Yパターン
    int frameCounter;       // フレームカウント
    bool crying;            // 泣いている状態
    bool prevRightMouse;    // 右クリックの前回の状態
    bool prevLeftMouse;     // 左クリックの前回の状態
    int XInput;             // ジョイパッドX軸入力
    int YInput;             // ジョイパッドY軸入力

    // ライフ管理

    int life;               // プレイヤーのライフ
    int enemyCollisionCount; // 敵に触れた回数
    // ゲームオーバー処理
    void GameOver();        // ゲームオーバー処理（後で実装）

    //Dクリックを検出して画像を変更する処理
    bool prevKEY_D_Click = false;
    bool isKEY_D_Click = false;

    //Aクリックを検出して画像を変更する処理
    bool prevKEY_A_Click = false;
    bool isKEY_A_Click = false;

    // 右クリックを検出して画像を変更する処理
    bool prevRightClick = false;  // 右クリックの前回状態
    bool isRightClicked = false;  // 現在右クリックされているかの状態

    // 左クリックを検出して画像を変更する処理
    bool prevLeftClick = false;  // 右クリックの前回状態
    bool isLeftClicked = false;  // 現在右クリックされているかの状態

    bool Changeflame;
    float timer;
    int blinkCounter;

};
