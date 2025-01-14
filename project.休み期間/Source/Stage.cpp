#include "Stage.h"
#include "Player.h"
#include "Coin.h"
#include "Enemy.h"
#include "Enemy1.h"
#include "GoalText.h"
const int CHIP_SIZE = 40;
#include "CsvReader.h"
#include "../StageUtility.h"

using namespace std;
//#include "stage1.h"
Stage::Stage()


//hashira.png
{
	map.clear();
	std::string filename = "data/stage.";
	filename += std::to_string(StageUtility::GetStageNo());
	filename += ".csv";
	CsvReader* csv = new CsvReader(filename);
	for (int y = 0; y < csv->GetLines(); y++) {
		vector<int> m;
		for (int x = 0; x < csv->GetColumns(y); x++) {
			m.push_back(csv->GetInt(y, x));
		}
		map.push_back(m);
	}
	HEIGHT = csv->GetLines();
	WIDTH = csv->GetColumns(0);
	delete csv;

	hImage = LoadGraph("data/image/maptile_renga.png");
	for (int j = 0; j < HEIGHT; j++) {
		for (int i = 0; i < WIDTH; i++) {
			if (map[j][i] == 9) {
				Player* p = Instantiate<Player>();
				p->position.x = i * 40;
				p->position.y = j * 40;
			}
			//if (map[j][i] == 2) {
			//	Coin* c = Instantiate<Coin>();
			//	c->position.x = i * 40;
			//	c->position.y = j * 40;
			//}
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
			if (map[j][i] == 6) {
				Enemy1* e1 = Instantiate<Enemy1>();
				e1->position.x = i * 40;
				e1->position.y = j * 40;
			}


		}
	}
	scroll = 0;
}
Stage::~Stage()
{
}

void Stage::Draw()//縦横で回す
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

				int x = i * 40;
				if (map[j][i] == 0)
				{

					DrawRectGraph(x - scroll, y, 0, 40, 40, 40, hImage, TRUE);
				}
			}

		}
	}
}

int Stage::IsWallRight(VECTOR2 pos) 
{
	// pos.xはボールの右端の座標
	int i = pos.x / CHIP_SIZE; // x座標をマス単位に変換
	int j = pos.y / CHIP_SIZE; // y座標をマス単位に変換
	// ボールが壁の右端に当たるかどうかをチェック
	if (map[j][i] == 1) 
	{  // map[j][i] == 1は壁の位置を意味
		int push = ((int)pos.x) % CHIP_SIZE + 1;  // 壁の右端までの距離
		return push;  // 壁に当たったら距離を返す
	}
	return 0;  // 壁に当たっていない場合は0を返す
}
int Stage::IsWallLeft(VECTOR2 pos) 
{
	// pos.xはボールの左端の座標
	int i = (pos.x) / CHIP_SIZE;  // x座標をマス単位に変換
	int j = pos.y / CHIP_SIZE;    // y座標をマス単位に変換
	// ボールが壁の左端に当たるかどうかをチェック
	if (map[j][i] == 1) 
	{  // map[j][i] == 1は壁の位置を意味
		int push = CHIP_SIZE - ((int)pos.x) % CHIP_SIZE;  // 壁の左端までの距離
		return push;  // 壁に当たったら距離を返す
	}
	return 0;  // 壁に当たっていない場合は0を返す
}
int Stage::IsWallDown(VECTOR2 pos) {
	// pos.yはボールの下端の座標
	int i = pos.x / CHIP_SIZE;  // x座標をマス単位に変換
	int j = pos.y / CHIP_SIZE;  // y座標をマス単位に変換
	// ボールが下端に当たるかどうかをチェック
	if (map[j][i] == 1) {  // map[j][i] == 1は壁の位置を意味
		int push = ((int)pos.y) % CHIP_SIZE + 1;  // 壁の下端までの距離
		return push;  // 壁に当たったら距離を返す
	}
	return 0;  // 壁に当たっていない場合は0を返す
}
int Stage::IsWallUP(VECTOR2 pos) {
	// pos.yはボールの上端の座標
	int i = pos.x / CHIP_SIZE;  // x座標をマス単位に変換
	int j = pos.y / CHIP_SIZE;  // y座標をマス単位に変換
	// ボールが上端に当たるかどうかをチェック
	if (map[j][i] == 1) {  // map[j][i] == 1は壁の位置を意味
		int push = CHIP_SIZE - ((int)pos.y) % CHIP_SIZE;  // 壁の上端までの距離
		return push;  // 壁に当たったら距離を返す
	}
	return 0;  // 壁に当たっていない場合は0を返す
}


bool Stage::IsWall(const VECTOR2& position){
	if (position.x >= 300 && position.x <= 320 && position.y >= 100 && position.y <= 200) {
		return false;
	}
}

bool Stage::IsGoal(VECTOR2 position)
{
	return position.x > goalX && position.x < goalX + goalWidth &&
		position.y > goalY && position.y < goalY + goalHeight;
}
