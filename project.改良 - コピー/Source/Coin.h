#pragma once
#include "../Library/gameObject.h"
#include "VECTOR2.h"

class Coin : public GameObject 
{
public:
	Coin();
	~Coin();
	void Update() override;
	void Draw() override;

	int hImage;
	VECTOR2 position;

	bool got; //取られた
	int counter;
	float v; //跳ねる動きの速度
};

