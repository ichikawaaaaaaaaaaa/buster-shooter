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

	bool got; //Žæ‚ç‚ê‚½
	int counter;
	float v; //’µ‚Ë‚é“®‚«‚Ì‘¬“x
};

