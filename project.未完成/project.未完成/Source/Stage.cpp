#include "Stage.h"
#include "Player.h"
#include "Coin.h"
#include "Enemy.h"
#include "GoalText.h"

const int CHIP_SIZE = 40;

#include "stage1.h"
#include "stage2.h"
#include <iostream>

int map[HEIGHT][WIDTH];

Stage::Stage()
{
	int stageNo = 2;
	
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			switch(stageNo)
			{
				case 1:
					map[y][x] = map_stage1[y][x];
					break;
				case 2:
					map[y][x] = map_stage2[y][x];
					break;
			}
		}
	}

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
			if (map[j][i] == 3) {
				Enemy* e = Instantiate<Enemy>();
				e->position.x = i * 40;
				e->position.y = j * 40;
			}
			if (map[j][i] == 4) {
				GoalText* g = Instantiate<GoalText>();
				g->position.x = i * 40;
				g->position.y = j * 40;
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

bool Stage::IsWall(const VECTOR2& position) {
	if (position.x >= 300 && position.x <= 320 && position.y >= 100 && position.y <= 200) {
		return false;
	}
}



bool Stage::IsGoal(VECTOR2 position)
{
	return position.x > goalX && position.x < goalX + goalWidth &&
		position.y > goalY && position.y < goalY + goalHeight;
}
