#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"
#include <DxLib.h>

class Player : public GameObject {

public:
    Player(); // コンストラクタ
    void Update() override; // プレイヤーの更新処理
    void Draw() override;   // プレイヤーの描画処理
    void DrawLife();
    void Animation();       // プレイヤーのアニメーション処理
    void UpdateAnimation(); // 新規追加：アニメーション更新処理

    // プレイヤーの画像ハンドル
    int hImage;             // プレイヤーのデフォルトの画像
    int hImageRightClick;
    int hImageLeftClick;
    int hImagelife;

    // 右移動、左移動用の画像
    int hImageMoveRight;    // 右移動時の画像
    int hImageMoveLeft;     // 左移動時の画像

    // プレイヤーの位置と状態
    VECTOR2 position;       // プレイヤーの座標（Vector2）
    float velocity;         // 垂直方向の速度
    bool prevJumpKey;       // 前フレームのジャンプキーの状態
    bool onGround;          // プレイヤーが地面に接しているか
    int IsGoal;             // ゴールフラグ
    int goaled;             // ゴール達成フラグ
    int scroll;             // スクロール位置（仮想）

    // アニメーション関連の変数
    int patternX;           // アニメーション用Xパターン
    int patternY;           // アニメーション用Yパターン
    int frameCounter;       // フレームカウント
    bool crying;            // 泣いている状態
    bool prevRightMouse;    // 右クリックの前回の状態
    bool prevLeftMouse;     // 左クリックの前回の状態

    // クリック状態
    bool isRightClicked = false;  // 右クリックされているかの状態
    bool isLeftClicked = false;   // 左クリックされているかの状態

    // ジョイパッドの入力
    int XInput;                // ジョイパッドX軸入力
    int YInput;                // ジョイパッドY軸入力

    // ライフと敵との衝突処理
    int life;                  // プレイヤーのライフ
    int enemyCollisionCount;   // 敵に触れた回数

    // ゲームオーバー処理
    void GameOver();           // ゲームオーバー処理（後で実装）

    // 横移動アニメーションの管理
    int moveAnimationFrame;    // 横移動のアニメーションフレーム
    int moveAnimationCounter;  // 横移動アニメーションのカウンター

    int animationCounter;
    int animationFrame;
    int animationSpeed = 10;
    int blinkCounter;
    int isMoving;

    int prevRightClick;
    int prevLeftClick;
};