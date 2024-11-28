#include "Stage.h"
#include "Player.h"
<<<<<<< HEAD
#include "Enemy.h"
=======
#include "Coin.h"
>>>>>>> e687b6cbac460819700e00a87906bba6386f6570

const int CHIP_SIZE = 40;

#include "stage1.h"

Stage::Stage()
{
	hImage = LoadGraph("data/image/parts.png");
	for (int j = 0; j < HEIGHT; j++) {
		for (int i = 0; i < WIDTH; i++) {
			if (map[j][i] == 9) {
				Player* p = Instantiate<Player>();
<<<<<<< HEAD
				p->position.x = i * 40;
				p->position.y = j * 40;
			}
			
			if (map[j][i] == 3) {
				Enemy* e = Instantiate<Enemy>();
				e->position.x = i * 40;
				e->position.y = j * 40;
=======
				p->position.x = i * 40 ;
				p->position.y = j * 40 ;
			}
			if (map[j][i]==2) {
				Coin* c = Instantiate<Coin>();
				c->position.x = i * 40 ;
				c->position.y = j * 40 ;
>>>>>>> e687b6cbac460819700e00a87906bba6386f6570
			}
		}
	}
	scroll = 0;
}

Stage::~Stage()
{
}

void Stage::Draw()//ècâ°Ç≈âÒÇ∑
{
	//scroll += 1;
	for (int j = 0; j < HEIGHT; j++)
	{
		int y = j * 40;
		for (int i = 0; i < WIDTH; i++)
		{
<<<<<<< HEAD
			int x = i * 40;
			if (map[j][i] == 1)
			{

=======
			int x = i * 40 ;
			if (map[j][i] == 1)
			{
				
>>>>>>> e687b6cbac460819700e00a87906bba6386f6570
				DrawRectGraph(x - scroll, y, 0, 40, 40, 40, hImage, TRUE);
			}
		}
	}
}

int Stage::IsWallRight(VECTOR2 pos)
{
<<<<<<< HEAD
	int i = (pos.x) / 40;
	int j = (pos.y) / 40;
	if (map[j][i] == 1) {
		int push = ((int)pos.x) % 40 + 1;
		return push;
	}
	return 0;
=======
	int i =(pos.x )/40;
	int j =(pos.y )/40;
	if (map[j][i] == 1) {
		int push = ((int)pos.x ) % 40 + 1;
		return push;
	}
		return 0;
>>>>>>> e687b6cbac460819700e00a87906bba6386f6570
}

int Stage::IsWallDown(VECTOR2 pos)
{
<<<<<<< HEAD
	int i = (pos.x) / 40;
	int j = (pos.y) / 40;
	if (map[j][i] == 1) {
		int push = ((int)pos.y) % 40 + 1;
=======
	int i = (pos.x ) / 40;
	int j = (pos.y ) / 40;
	if (map[j][i] == 1) {
		int push = ((int)pos.y ) % 40 + 1;
>>>>>>> e687b6cbac460819700e00a87906bba6386f6570
		return push;
	}
	return 0;
}

int Stage::IsWallLeft(VECTOR2 pos)
{
<<<<<<< HEAD
	int i = (pos.x) / 40;
	int j = (pos.y) / 40;
	if (map[j][i] == 1) {
		int push = 40 - ((int)pos.x) % 40;
=======
	int i = (pos.x ) / 40;
	int j = (pos.y ) / 40;
	if (map[j][i] == 1) {
		int push = 40-((int)pos.x ) % 40 ;
>>>>>>> e687b6cbac460819700e00a87906bba6386f6570
		return push;
	}
	return 0;
}

int Stage::IsWallUP(VECTOR2 pos)
{
	int i = (pos.x) / 40;
<<<<<<< HEAD
	int j = (pos.y) / 40;
	if (map[j][i] == 1) {
		int push = 40 - ((int)pos.y) % 40;
=======
	int j = (pos.y ) / 40;
	if (map[j][i] == 1) {
		int push = 40-((int)pos.y ) % 40;
>>>>>>> e687b6cbac460819700e00a87906bba6386f6570
		return push;
	}
	return 0;
}
