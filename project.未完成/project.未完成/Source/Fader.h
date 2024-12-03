#pragma once
#include "../Library/gameObject.h"

class Fader : public GameObject
{
 public:
	Fader();
	~Fader();
	void Update();
	void Draw();
	void FadeOut(unsigned int color, float time);
	bool IsFinish();

	float alpha;
	unsigned int fadeColor;
	float fadeTime;//フェードアウトする時間
	float timer;//実際の経過時間
};

