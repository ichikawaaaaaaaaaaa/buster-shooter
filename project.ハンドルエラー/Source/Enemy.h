#pragma once

#include "../Library/gameObject.h"

#include "Vector2.h"

class Enemy : public GameObject {

public:

    Enemy();            // コンストラクタ
    ~Enemy();           // デストラクタ

    void Update() override;  // 更新処理
    void Draw() override;    // 描画処理
    VECTOR2 position;        // 敵の位置
    VECTOR2 speed;           // 敵の速度

    int hImage;              // 敵の画像ハンドル
    int patternX;            // 表示パターンの横番号
    int patternY;            // 表示パターンの縦番号
    int velocity;
    VECTOR2 GetPosition() const;  // 敵の位置を取得する
    void OnCollide();             // 衝突時の処理

    int timer;               // タイマー
    bool attacking;          // 攻撃中フラグ
    bool dead;               // 死亡フラグ
    int deadCounter;         // 死亡状態のカウンタ
    bool onGround;           // 地面にいるかどうかのフラグ

    // アニメーション関連

    int imageWidth;          // 画像の幅
    int imageHeight;         // 画像の高さ
    int frameWidth;          // 1フレームの幅
    int frameHeight;         // 1フレームの高さ
    int framesPerRow;        // 1行あたりのフレーム数
    int maxFrames;           // 最大フレーム数
    int currentImage;        // 現在使用中の画像
    int currentFrame;        // 現在のフレーム番号
    int frameTimer;          // フレーム切り替え用タイマー
    int animationSpeed;      // アニメーションの速度
};