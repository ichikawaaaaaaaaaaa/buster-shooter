#pragma once
#include "Vector2.h"
class Ball  {
public:
	Ball(float startX, float startY, float speedX, float speedY);  // コンストラクタ
	void Update();  // 玉の位置を更新
	void Draw();    // 玉を描画
	VECTOR2 position;  // 玉の位置
	VECTOR2 velocity;  // 玉の速度
	bool active;       // 玉が有効かどうか
};