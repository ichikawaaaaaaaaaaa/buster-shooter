#pragma once

#include "../Library/gameObject.h"

#include "Vector2.h"

class Jet : public GameObject
{
public:
	// コンストラクタとデストラクタ
	Jet();
	~Jet();
	// 更新処理
	void Update() override;
	// 描画処理
	void Draw() override;
	// 位置取得
	VECTOR2 GetPosition() const;
	// 衝突時の処理
	void OnCollide() override;
private:
	// メンバ変数
	int hImage;          // 画像のハンドル
	int imageWidth;      // 画像の幅
	int imageHeight;     // 画像の高さ
	VECTOR2 position;    // 現在位置
	VECTOR2 speed;       // 移動速度
	int patternX;        // パターンX (アニメーション用)
	int patternY;        // パターンY (アニメーション用)
	int currentImage;    // 現在の画像
	int frameWidth;      // 1フレームの幅
	int frameHeight;     // 1フレームの高さ
	int maxFrames;       // 総フレーム数
	int currentFrame;    // 現在のフレーム
	int frameTimer;      // フレーム切り替えタイマー
	int animationSpeed;  // アニメーション速度
	int timer;           // 攻撃タイマー
	bool attacking;      // 攻撃中かどうか
	bool dead;           // 死亡状態
	int deadCounter;     // 死亡カウンタ
	// 衝突判定用
	float velocity;      // 速度
	bool onGround;       // 地面に接触しているか
};
