#pragma once
#include "../Library/gameObject.h"

class GameOver : public SceneBase
{
private://	�Q�[���I�[�o�[

	const char* KEY_GRAPH_PATH = "image/GameOver.png";

	const int OVER_GRAPH_X = 370;			//	[GAMEOVER]�\���ʒu(X)
	const int OVER_GRAPH_Y = 450;		//	[GAMEOVER]�\���ʒu(Y)

private:
	int bgHandle;			//	�摜�n���h��(�^�C�g�����)


public:
	GameOver();
	~GameOver();
	void Update() override;
	void Draw() override;
	int hBGImageII;
};
