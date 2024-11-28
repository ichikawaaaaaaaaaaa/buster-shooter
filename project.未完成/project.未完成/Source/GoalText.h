#pragma once
#include "../Library/gameObject.h"

class GoalText : public GameObject
{
public:
	GoalText();
	~GoalText();
	void Update()override;
	void Draw() override;


	float timer;
	bool fadeStarted;
};

