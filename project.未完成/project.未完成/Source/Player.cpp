#include "Player.h"
#include "GoalText.h"
#include "Stage.h"
#include "Ball.h"
#include "config.h"
#include "Enemy.h"
#include "VECTOR2.h"
#include "../Library/time.h"


float Gravity = 0.1f;     //重力加速度
float jumpHeight = 20*2;  //ジャンプの高さ
float V0 = -sqrtf(3.0f * Gravity * jumpHeight);//初速計算

//コンストラクタ
Player::Player()
{
	hImage = LoadGraph("data/image/Player.png");//キャラ画像の読み込み
	position.x = 10;  //初期X座標
	position.y = 100;  //初期座標
	velocity = 0;    //初期速度
	prevJumpKey = false;   //初期ジャンプキー状態
	onGround = false;  //地上判定初期化
	IsGoal = 0;//ゴールフラグ初期化
	goaled = 0;  //ゴール達成フラグ初期化
	scroll = 0;  //スクロール位置初期化
}

//デストラクタ
Player::~Player()
{
	DeleteGraph(hImage);
}

//更新処理
void Player::Update()
{
	Stage* s = FindGameObject<Stage>();// ステージオブジェクト取得
	if (goaled)return;  // ゴール済みの場合、処理を終了

	//左右の移動処理

		//左の移動処理
	if (CheckHitKey(KEY_INPUT_A)) {
		position.x -= 2;  //左に〇(数字)ピクセル移動

		//左の壁との衝突判定
		//キャラクターの左上隅ので衝突をチェックする場合
		int push = s->IsWallLeft(position + VECTOR2(0, 0));

		//衝突した場合、その押し返し量　(壁にぶつからないようにする)

		position.x += push; //壁の奥に進まないように位置を調節

		//キャラクターの下端の位置でも衝突判定を行う場合
		//キャラクターの下半分で衝突を確認
		push = s->IsWallLeft(position + VECTOR2(0, 39));  //例(1111)はキャラクターの高さ

		//下側で壁にぶつかっていた場合、その押し返し量を考慮して位置を調整
		position.x += push;
	}

	//右の移動処理
	if (CheckHitKey(KEY_INPUT_D)) {
		position.x += 2;  //右に〇(数字)ピクセル移動

		//右の壁との衝突判定
		//キャラクターの右上隅の位置での衝突をチェックする場合
		int push = s->IsWallRight(position + VECTOR2(39, 0)); //例(1111)はキャラクターの高さ

		//衝突した場合、その押し返し量　(壁にぶつからないようにする)

		position.x -= push; //壁の手前に位置を戻して調節

		//キャラクターの下端の位置でも衝突判定を行う場合
		//キャラクターの下半分衝突の確認
		push = s->IsWallRight(position + VECTOR2(39, 39)); //例(1111)はキャラクターの高さ

		//下側で壁にぶつかっていた場合、その押し返し量を考慮して位置を調整
		position.x -= push;
	}
	// ジャンプ処理
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		if (!prevJumpKey && onGround) { //地上にいてジャンプキーが押された場合

			velocity = V0;             //初速を設定
		}
	}
	prevJumpKey = CheckHitKey(KEY_INPUT_SPACE); //現在のジャンプキー状態を記録

	// 垂直方向の移動と重力処理
	position.y += velocity;  //座標に速度を加算
	velocity += Gravity;     //速度に重力を加算
	onGround = false;        //地面接触フラグをリセット

	// 地面衝突判定
	if (velocity >= 0) {
		// キャラクターの位置に応じた地面衝突判定
		int push = s->IsWallDown(position + VECTOR2(0, 39 + 1));//例(1111)はキャラクターの高さ

		if (push > 0) { // 地面に触れた場合
			velocity = 0.0f; // 速度を0にする
			position.y -= push - 1; // 地面に押し戻す
			onGround = true;        // 地上判定をON
		}

		else {
			// 頭の衝突判定
			push = s->IsWallUP(position + VECTOR2(0, 0));

			if (push > 0) {
				velocity = 0.0f;  // 頭に衝突した場合、速度を0にする
				position.y += push; // 頭上に押し戻す
			}

			push = s->IsWallUP(position + VECTOR2(39, 0));//例(1111)はキャラクターの高さ

			if (push > 0) {
				velocity = 0.0f;
				position.y += push;
			}
		}

		// 右足地面判定
		push = s->IsWallDown(position + VECTOR2(39, 39));//例(1111)はキャラクターの高さ
		if (push > 0) {
			velocity = 0.0f;
			position.y -= push - 1;
			onGround = true; // 地面に着地したとき、地上判定をONにする
		}
	}

	// Ballを投げる
	if (GetMouseInput() & MOUSE_INPUT_RIGHT) {
		if (prevRightMouse == false) {
			Ball* Ba = Instantiate<Ball>();
			// 代入してから足す方法
			Ba->position = position;
			Ba->position.x += 130;
			Ba->position.y += 5;
			// ここまで、どちらかを使う
		}
		prevRightMouse = true;
	}
	else {
		prevRightMouse = false;
	}

	//Enemyの当たり判定
	std::list<Enemy*> enemys = FindGameObjects<Enemy>();
	for (Enemy* e : enemys) {
		if (CircleHit(position, e->position, 100)) {
			patternY = 4;
			crying = true;
			break;
		}
	}
	if (crying)
	{
		if (timer <= 5.0f)
		{
			CheckHitKey(KEY_INPUT_D);
			{
				position.x += 0;
			}
			CheckHitKey(KEY_INPUT_A);
			{
				position.x += 0;
			}
			CheckHitKey(KEY_INPUT_W);
			{
				position.y += 0;
			}
			CheckHitKey(KEY_INPUT_S);
			{
				position.x += 0;
			}
		}
		timer += Time::DeltaTime();
		if (timer >= 10.0f)
		{
			SceneManager::ChangeScene("TitleScene");
		}	
		
	}
	//400までプレイヤーが行ったらスクロール

	//- s->scrollしているがscrollに値を入れていないので　ただのposition.x(プレイヤーのx座標）
	if (position.x - s->scroll > 400) {
		s->scroll = position.x - 400;
	}


	if (position.x - s->scroll < 200) {
		s->scroll = position.x - 200;
	}
	if (goaled == false && s->IsGoal(position + VECTOR2(20, 20))) {

		goaled = true;

		Instantiate<GoalText>();

	}


}


void Player::Draw()
{
	Stage* s = FindGameObject<Stage>();
	DrawRectGraph(position.x - s->scroll, position.y , 0, 0, 40, 40, hImage, TRUE);
}
