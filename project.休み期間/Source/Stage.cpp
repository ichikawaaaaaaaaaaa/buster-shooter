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
	// pos.x�̓{�[���̉E�[�̍��W
	int i = pos.x / CHIP_SIZE; // x���W���}�X�P�ʂɕϊ�
	int j = pos.y / CHIP_SIZE; // y���W���}�X�P�ʂɕϊ�
	// �{�[�����ǂ̉E�[�ɓ����邩�ǂ������`�F�b�N
	if (map[j][i] == 1) 
	{  // map[j][i] == 1�͕ǂ̈ʒu���Ӗ�
		int push = ((int)pos.x) % CHIP_SIZE + 1;  // �ǂ̉E�[�܂ł̋���
		return push;  // �ǂɓ��������狗����Ԃ�
	}
	return 0;  // �ǂɓ������Ă��Ȃ��ꍇ��0��Ԃ�
}
int Stage::IsWallLeft(VECTOR2 pos) 
{
	// pos.x�̓{�[���̍��[�̍��W
	int i = (pos.x) / CHIP_SIZE;  // x���W���}�X�P�ʂɕϊ�
	int j = pos.y / CHIP_SIZE;    // y���W���}�X�P�ʂɕϊ�
	// �{�[�����ǂ̍��[�ɓ����邩�ǂ������`�F�b�N
	if (map[j][i] == 1) 
	{  // map[j][i] == 1�͕ǂ̈ʒu���Ӗ�
		int push = CHIP_SIZE - ((int)pos.x) % CHIP_SIZE;  // �ǂ̍��[�܂ł̋���
		return push;  // �ǂɓ��������狗����Ԃ�
	}
	return 0;  // �ǂɓ������Ă��Ȃ��ꍇ��0��Ԃ�
}
int Stage::IsWallDown(VECTOR2 pos) {
	// pos.y�̓{�[���̉��[�̍��W
	int i = pos.x / CHIP_SIZE;  // x���W���}�X�P�ʂɕϊ�
	int j = pos.y / CHIP_SIZE;  // y���W���}�X�P�ʂɕϊ�
	// �{�[�������[�ɓ����邩�ǂ������`�F�b�N
	if (map[j][i] == 1) {  // map[j][i] == 1�͕ǂ̈ʒu���Ӗ�
		int push = ((int)pos.y) % CHIP_SIZE + 1;  // �ǂ̉��[�܂ł̋���
		return push;  // �ǂɓ��������狗����Ԃ�
	}
	return 0;  // �ǂɓ������Ă��Ȃ��ꍇ��0��Ԃ�
}
int Stage::IsWallUP(VECTOR2 pos) {
	// pos.y�̓{�[���̏�[�̍��W
	int i = pos.x / CHIP_SIZE;  // x���W���}�X�P�ʂɕϊ�
	int j = pos.y / CHIP_SIZE;  // y���W���}�X�P�ʂɕϊ�
	// �{�[������[�ɓ����邩�ǂ������`�F�b�N
	if (map[j][i] == 1) {  // map[j][i] == 1�͕ǂ̈ʒu���Ӗ�
		int push = CHIP_SIZE - ((int)pos.y) % CHIP_SIZE;  // �ǂ̏�[�܂ł̋���
		return push;  // �ǂɓ��������狗����Ԃ�
	}
	return 0;  // �ǂɓ������Ă��Ȃ��ꍇ��0��Ԃ�
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
