#pragma once
#include "../Library/gameObject.h"

class GameClear : public SceneBase
{
private://	�Q�[���N���A

	const char* KEY_GRAPH_PATH = "image/GameClear.png";

	const int OVER_GRAPH_X = 370;			//	[GAMEOVER]�\���ʒu(X)
	const int OVER_GRAPH_Y = 450;		//	[GAMEOVER]�\���ʒu(Y)

private:
	int bgHandle;			//	�摜�n���h��(�^�C�g�����)


public:
	GameClear();
	~GameClear();
	void Update() override;
	void Draw() override;
	int hBGImageII;
};
