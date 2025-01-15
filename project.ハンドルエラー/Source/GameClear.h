#pragma once
#include "../Library/gameObject.h"

class GameClear : public SceneBase
{
private://	ゲームクリア

	const char* KEY_GRAPH_PATH = "image/GameClear.png";

	const int OVER_GRAPH_X = 370;			//	[GAMEOVER]表示位置(X)
	const int OVER_GRAPH_Y = 450;		//	[GAMEOVER]表示位置(Y)

private:
	int bgHandle;			//	画像ハンドル(タイトル画面)


public:
	GameClear();
	~GameClear();
	void Update() override;
	void Draw() override;
	int hBGImageII;
};
