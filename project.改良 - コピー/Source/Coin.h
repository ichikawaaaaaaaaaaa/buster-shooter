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

	bool got; //���ꂽ
	int counter;
	float v; //���˂铮���̑��x
};

