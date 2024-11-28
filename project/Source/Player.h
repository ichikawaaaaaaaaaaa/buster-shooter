#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"

<<<<<<< HEAD
//GameObject クラスの継承
class Player : public GameObject {
public:
	Player();//コンストラクタ
	~Player();//デストラクタ
	void Update() override;//プレイヤーの更新処理
	void Draw() override;//プレイヤーの描画処理

	int hImage;//プレイヤーの画像ハンドル
	VECTOR2 position;// プレイヤーの座標（Vector2）
	float velocity;  // 垂直方向の速度（ジャンプ・落下用）
	bool prevJumpKey;      // 前フレームのジャンプキーの状態
	bool onGround; // プレイヤーが地面に接しているか
	int IsGoal;  // ゴールフラグ
	int goaled;    // ゴール達成フラグ

	int scroll;  // スクロール位置（仮想）

};



=======
class Player : public GameObject {
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;
	int hImage;
	VECTOR2 position;
	float velocity;
	bool prevJumpKey;	//前のジャンプキー
	bool onGround;	//地面にいる
};
>>>>>>> e687b6cbac460819700e00a87906bba6386f6570
