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

	int hImage;
};