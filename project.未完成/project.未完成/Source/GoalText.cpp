#include "GoalText.h"
#include "../Library/time.h"
#include "Fader.h"


GoalText::GoalText()
{
	timer = 0.0f;
}

GoalText::~GoalText()
{
}

void GoalText::Update()
{
	if (fadeStarted) {
		Fader* f = FindGameObject <Fader>();
		if (f->IsFinish()) {
			SceneManager::ChangeScene("TitleScene");
		}
		return;
	}

	timer += Time::DeltaTime();
	if (timer >= 2.5f) {
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			Fader* f = FindGameObject <Fader>();
			f->FadeOut(GetColor(0, 0, 0), 0.5f);
			fadeStarted = true;
			//	SceneManager::ChangeScene("TitleScene");
		}
	}
}


void GoalText::Draw()
{
	int size = GetFontSize();
	SetFontSize(50);
	DrawString(200, 200, "GOAL", GetColor(255, 255, 127));
	if (timer >= 1.0f) {


		SetFontSize(25);
		DrawFormatString(200, 300, GetColor(255, 255, 255),
			"SCORE..... %6d");
	}
	if (timer >= 2.0f) {
		DrawString(200, 500, "PUSH SPACE KEY", GetColor(255, 255, 255));
	}
	SetFontSize(size);



}