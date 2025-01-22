#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"
class Ball : public GameObject {
public:
	Ball();    // コンストラクタ
	~Ball();   // デストラクタ
	void Update() override;   // 更新処理
	void Draw() override;     // 描画処理
	// ボールの画像や状態に関する変数
	int hImage;               // 通常のボール画像
	int hImageCollide;        // 衝突後のボール画像
	int currentImage;         // 現在表示しているボール画像
	VECTOR2 position;         // ボールの位置
	VECTOR2 velocity;         // ボールの速度
	int goaled;               // ゴール達成フラグ
	int scroll;               // スクロール位置（仮想）
private:
	// アニメーションに関する変数
	float Gravity = 0.0f;     // 重力
	bool isColliding = false; // 衝突状態フラグ
	int collisionTimer = 0;   // 衝突後のタイマー
	// アニメーションのフレーム管理
	int currentFrame;     // 現在のフレーム
	int frameWidth;     // 各フレームの幅
	int frameHeight;     // 各フレームの高さ
	int totalFrames = 8;      // アニメーションフレームの総数
	int frameCounter = 0;     // アニメーションのカウンタ
	int maxFrames;
	int frameTimer;
	int animationSpeed;
};