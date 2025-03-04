#pragma once
#include "../Library/gameObject.h"
#include "DxLib.h"  // 描画用
#include "Vector2.h"
class GoalText : public GameObject {
public:
	GoalText();                // コンストラクタ
	~GoalText();               // デストラクタ
	void Update() override;    // 更新処理
	void Draw() override;      // 描画処理
	VECTOR2 position;
	int hImage;
	bool IsGoal;

private:
	int timer;               // タイマー（テキストの表示時間）
	bool fadeStarted;          // フェード開始フラグ
	int alpha;                 // 文字の透明度（フェード用）

};