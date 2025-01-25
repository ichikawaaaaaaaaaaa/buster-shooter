#pragma once
#include "../Library/gameObject.h"

class GameOver : public SceneBase
{
private://	ゲームオーバー

	const char* KEY_GRAPH_PATH = "data/image/GameOver.png";

	int PushSpaceKey;

	const int OVER_GRAPH_X = 370;			//	[GAMEOVER]表示位置(X)
	const int OVER_GRAPH_Y = 450;		//	[GAMEOVER]表示位置(Y)

private:
	int bgHandle;			//	画像ハンドル(タイトル画面)
	float timer;               // タイマー（テキストの表示時間）


public:
	GameOver();
	~GameOver();
	void Update() override;
	void Draw() override;
	int hBGImageII;

	int XInput;             // ジョイパッドX軸入力
	int YInput;             // ジョイパッドY軸入力
	bool fadeStarted;          // フェード開始フラグ
	int alpha;                 // 文字の透明度（フェード用）
};
