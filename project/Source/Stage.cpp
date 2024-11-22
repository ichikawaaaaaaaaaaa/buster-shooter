#include "Stage.h"
#include "Player.h"
#include "Coin.h"

const int CHIP_SIZE = 40;

#include "stage1.h"

Stage::Stage()
{
	hImage = LoadGraph("data/image/parts.png");
	for (int j = 0; j < HEIGHT; j++) {
		for (int i = 0; i < WIDTH; i++) {
			if (map[j][i] == 9) {
				Player* p = Instantiate<Player>();
				p->position.x = i * 40 ;
				p->position.y = j * 40 ;
			}
			if (map[j][i]==2) {
				Coin* c = Instantiate<Coin>();
				c->position.x = i * 40 ;
				c->position.y = j * 40 ;
			}
		}
	}
	scroll = 0;
}

Stage::~Stage()
{
}

void Stage::Draw()//�c���ŉ�
{
	//scroll += 1;
	for (int j = 0; j < HEIGHT; j++)
	{
		int y = j * 40;
		for (int i = 0; i < WIDTH; i++)
		{
			int x = i * 40 ;
			if (map[j][i] == 1)
			{
				
				DrawRectGraph(x - scroll, y, 0, 40, 40, 40, hImage, TRUE);
			}
		}
	}
}

int Stage::IsWallRight(VECTOR2 pos)
{
	int i =(pos.x )/40;
	int j =(pos.y )/40;
	if (map[j][i] == 1) {
		int push = ((int)pos.x ) % 40 + 1;
		return push;
	}
		return 0;
}

int Stage::IsWallDown(VECTOR2 pos)
{
	int i = (pos.x ) / 40;
	int j = (pos.y ) / 40;
	if (map[j][i] == 1) {
		int push = ((int)pos.y ) % 40 + 1;
		return push;
	}
	return 0;
}

int Stage::IsWallLeft(VECTOR2 pos)
{
	int i = (pos.x ) / 40;
	int j = (pos.y ) / 40;
	if (map[j][i] == 1) {
		int push = 40-((int)pos.x ) % 40 ;
		return push;
	}
	return 0;
}

int Stage::IsWallUP(VECTOR2 pos)
{
	int i = (pos.x) / 40;
	int j = (pos.y ) / 40;
	if (map[j][i] == 1) {
		int push = 40-((int)pos.y ) % 40;
		return push;
	}
	return 0;
}
