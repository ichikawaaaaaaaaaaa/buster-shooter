#include "GoalText.h"
#include "../Library/time.h"
#include "Fader.h"
#include "Player.h"
#include "Stage.h"


GoalText::GoalText()
{
	hImage = LoadGraph("data/image/Goal.png");
	GaneclearText = LoadGraph("data/image/GameClear.png");
	PushSpaceKey = LoadGraph("data/image/PushSpace.png");

	IsGoal = false;

}

GoalText::~GoalText()
{
}

void GoalText::Update()
{

	//当たり判定
	Player* p = FindGameObject<Player>();//相手のインスタンスを取得
	VECTOR2 playerPos = p->position;//相手の座標を取得

	if (CircleHit(playerPos, position, 40)) {//円の当たり判定
		//DestroyMe();

		IsGoal = true;
	}
	if (IsGoal)
	{
		timer += 1.0f / 60.0f;
		if (fadeStarted) {
			Fader* f = FindGameObject <Fader>();
				if (timer > 3) {
					SceneManager::ChangeScene("TitleScene");
				}
			return;
		}

		timer  += Time::DeltaTime();
		if (timer >= 2.5f) {
			//if (CheckHitKey(KEY_INPUT_SPACE)) {
				Fader* f = FindGameObject <Fader>();
				f->FadeOut(GetColor(0, 0, 0), 0.5f);
				fadeStarted = true;
					//SceneManager::ChangeScene("TitleScene");
			}
		}
	}
//}


void GoalText::Draw()
{
	Stage* s = FindGameObject<Stage>();//絵の表示をする
	if(IsGoal)
	{
		//int size = GetFontSize();
		//SetFontSize(50);
		DrawGraph(200, 200, GaneclearText, TRUE);
		if (timer >= 1.0f) {


		//	SetFontSize(25);
		//	DrawFormatString(200, 300, GetColor(255, 255, 255),
		//		"SCORE..... %6d");
		}
		if (timer >= 2.0f) {
			DrawGraph(300, 2000, PushSpaceKey, TRUE);
		}
		//SetFontSize(size);
	}
}