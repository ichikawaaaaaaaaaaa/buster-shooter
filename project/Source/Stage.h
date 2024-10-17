#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"

class Stage : public GameObject {
public:
	Stage();
	~Stage();
	void Draw() override;
	int IswallRigth(VECTOR2 pos);
	int IswallDown(VECTOR2 pos);
	int IswallLeft(VECTOR2 pos);
	int IswallUp(VECTOR2 pos);
	int hImage;
};