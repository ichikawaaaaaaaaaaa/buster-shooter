#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"

class Enemy : public GameObject {
public:
	Enemy(); // コンストラクター (最初に一回だけ呼ばれる)
	~Enemy(); // デストラクター（最後に一回だけ呼ばれる)
	void Update() override;
	void Draw() override;

	int hImage; // 画像
	VECTOR2 position;
	VECTOR2 speed;

	int patternX; //表示パターンの横の番号
	int patternY; //表示パターンの縦の番号

	int frameCounter;

	int timer; //時間を測るため
	bool attacking; //突入してます。
};
