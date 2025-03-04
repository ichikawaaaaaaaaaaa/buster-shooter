#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"
#include <DxLib.h>

//GameObject クラスの継承
class Player : public GameObject {
public:
	Player();//コンストラクタ
	//~Player();//デストラクタ
	void Update() override;//プレイヤーの更新処理
	void Draw() override;
	void Animation();
	//プレイヤーの描画処理

	int hImage;//プレイヤーの画像ハンドル
	VECTOR2 position;// プレイヤーの座標（Vector2）
	float velocity;  // 垂直方向の速度
	bool prevJumpKey;      // 前フレームのジャンプキーの状態
	bool onGround; // プレイヤーが地面に接しているか
	int IsGoal;  // ゴールフラグ
	int goaled;    // ゴール達成フラグ

	int scroll;  // スクロール位置（仮想）

	int patternX;  
	int patternY;
	int frameCounter;

	bool crying;

	bool prevRightMouse;
	bool prevLeftMouse;

	int XInput;
	int YInput;

	//int GetJoypadInputState(int InputType);

	//int GetJoypadAnalogInput(int* XBuf, int* YBuf, int InputType);

};



