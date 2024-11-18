#include "Coin.h"
#include "Player.h"
#include "Stage.h"

Coin::Coin()
{
	//コンストラクターで絵をロードする
	hImage = LoadGraph("data/image/parts.png");
	got = false;
}

Coin::~Coin()
{
}

void Coin::Update()
{
	if (got) {
		position.y += v;
		v += 0.8f; //落ちる速さ
		counter -= 1;
		if (counter == 0) {
			DestroyMe();
		}
		return;
	}

		//当たり判定
		Player* p = FindGameObject<Player>();//相手のインスタンスを取得
		VECTOR2 playerPos = p->position;//相手の座標を取得

		if (CircleHit(playerPos, position, 40)) {//円の当たり判定
			//DestroyMe();

			got = true;
			counter = 20;
			v = -9.0f; //跳ねる高さ
	}
}

void Coin::Draw()
{
	Stage* s = FindGameObject<Stage>();
	//絵の表示をする
	DrawRectGraph(position.x - s->scroll, position.y, 120, 0, 40, 40, hImage, TRUE);
}
