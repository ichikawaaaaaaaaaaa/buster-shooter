#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"

class Ball : public GameObject {
public:
	Ball();
	~Ball();
	void Update() override;
	void Draw() override;


	int hImage; // �摜
	VECTOR2 position;
};