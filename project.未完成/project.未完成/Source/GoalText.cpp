#include "GoalText.h"
#include "../Library/time.h"
#include "Fader.h"
#include "Player.h"
#include "Stage.h"


GoalText::GoalText()
{
	hImage = LoadGraph("data/image/Goal.png");
	IsGoal = false;
	timer = 0.0f;
}

GoalText::~GoalText()
{
}

void GoalText::Update()
{
	//当たり判定
	Player* p = FindGameObject<Player>();//相手のインスタンスを取得
	VECTOR2 playerPos = p->position;//相手の座標を取得

	if (CircleHit(playerPos, position, 10)) {//円の当たり判定
		//DestroyMe();

		IsGoal = true;
	}
	if (IsGoal)
	{
		if (fadeStarted)
		{
			Fader* f = FindGameObject <Fader>();
			if (f->IsFinish())
			{
				SceneManager::ChangeScene("TitleScene");
			}
			return;
		}

		timer += Time::DeltaTime();
		if (timer >= 2.5f)
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				Fader* f = FindGameObject <Fader>();
				f->FadeOut(GetColor(0, 0, 0), 0.5f);
				fadeStarted = true;
				//	SceneManager::ChangeScene("TitleScene");
			}
		}

		if (timer >= 5.0f)
		{
			SceneManager::ChangeScene("TitleScene");
		}
	}
}


void GoalText::Draw()
{
	Stage* s = FindGameObject<Stage>();//絵の表示をする
	DrawRectGraph(position.x - s->scroll, position.y, 0, 0, 40, 40, hImage, TRUE);
	if (IsGoal)
	{
		int size = GetFontSize();
		SetFontSize(50);
		DrawString(200, 200, "GOAL", GetColor(255, 255, 127));
		if (timer >= 1.0f)
		{


			SetFontSize(25);
			DrawFormatString(200, 300, GetColor(255, 255, 255),
				"SCORE..... %6d");
		}
		
	}
}