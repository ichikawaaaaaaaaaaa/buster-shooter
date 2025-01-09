#pragma once
#include "../Library/gameObject.h"
#include "VECTOR2.h"

class Stage : public GameObject {
public:
	Stage();
	~Stage();
	void Draw() override;
	int IsWallRight(VECTOR2 pos);
	int IsWallDown(VECTOR2 pos);
	int IsWallLeft(VECTOR2 pos);
	int IsWallUP(VECTOR2 pos);
	
	bool IsWall(const VECTOR2& position);  // 壁判定用のメソッド


	float goalX, goalY;
	float goalWidth, goalHeight;
	bool IsGoal(VECTOR2 position);

	int hImage;

	int scroll;
};