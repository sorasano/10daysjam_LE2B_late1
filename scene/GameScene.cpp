#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include "Matrix4.h"

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
	delete fan_;
	delete paper_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	model_ = Model::Create();


	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");

	//自キャラの生成
	fan_ = new Fan();
	//自キャラの初期化
	fan_->Initialize(model_, textureHandle_);

	//紙の生成
	paper_ = new Paper();
	//自キャラの初期化
	paper_->Initialize(model_, model_, textureHandle_, textureHandle_);

	//視点座標
	viewProjection_.eye = { 0,30,-30 };
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	//デバックカメラの生成
	debugCamera_ = new DebugCamera(500, 500);

	viewProjection_.eye.y = 50;

	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

}

void GameScene::Update() {

	//デバックカメラの更新
	debugCamera_->Update();

	if (scene == 0) {
		debugText_->SetPos(0, 0);
		debugText_->Printf("Preas push SPACE");
	}
	else if (scene == 1) {

		cameramode = 0;
		fan_->Update();
		paper_->Update();
		debugText_->SetPos(0, 0);
		debugText_->Printf("Preas HOLD AND RELEASE SPACE");
		debugText_->SetPos(0, 20);
		debugText_->Printf("POWER = %f (MIN 0 ,MAX 10)",fan_->GetWindPower());

		if (shot >= 1) {
			debugText_->SetPos(0, 60);
			debugText_->Printf("SCORE 1 = %f", paper_->GetWorldPosition(beginshot[0]).z);
			if (shot >= 2) {
				debugText_->SetPos(0, 80);
				debugText_->Printf("SCORE 2 = %f", paper_->GetWorldPosition(beginshot[1]).z);
			}
		}

	}
	else if (scene == 2) {

		paper_->Update();
		fan_->Update();

		debugText_->SetPos(0, 0);
		debugText_->Printf("SCORE = %fM", paper_->GetWorldPosition(touchPaperNum).z);

		if (input_->PushKey(DIK_1)) {
			cameramode = 1;
		}
		else if (input_->PushKey(DIK_2)) {
			cameramode = 2;
		}

		//地面についたらshotを増やす,以前に落ちた弾は除外

		if (paper_->GetIsLanding(touchPaperNum) == 1) {

			if (isLand == 0) {
				isLand = 1;
				beginshot[shot] = touchPaperNum;
				shot++;
				paper_->SetIsCol(touchPaperNum);
			}

		}




		////弾を外した場合
		//const std::list<std::unique_ptr<FanWind>>& fanWinds = fan_->GetBullets();

		//for (const std::unique_ptr<FanWind>& fanwind : fanWinds) {
		//	if (fanwind->GetWorldPosition().z >= 100) {
		//		shot++;
		//	}
		//}

	}
	else if (scene == 3) {
		debugText_->SetPos(0, 0);
		debugText_->Printf("Preas push SPACE");

		debugText_->SetPos(0, 60);
		debugText_->Printf("SCORE 1 = %f", paper_->GetWorldPosition(beginshot[0]).z);
		debugText_->SetPos(0, 80);
		debugText_->Printf("SCORE 2 = %f", paper_->GetWorldPosition(beginshot[1]).z);
		debugText_->SetPos(0, 100);
		debugText_->Printf("SCORE 3 = %f", paper_->GetWorldPosition(beginshot[2]).z);
		debugText_->SetPos(0, 120);
		debugText_->Printf("HIGH SCORE = %f",highScore);
	}

	//カメラ

	//if (input_->PushKey(DIK_0)) {
	//	cameramode = 0;
	//}
	//else if (input_->PushKey(DIK_1)) {
	//	cameramode = 1;
	//}
	//else if (input_->PushKey(DIK_2)) {
	//	cameramode = 2;
	//}

	if (cameramode == 0) {
		//視点座標
		viewProjection_.eye = { 0,30,-30 };
		viewProjection_.target = { 0, 0,0 };


		//viewProjection_.eye.z = paper_->GetWorldPosition(touchPaperNum).z + (-30);
		//viewProjection_.target.z = paper_->GetWorldPosition(touchPaperNum).z;
		viewProjection_.Initialize();

	}
	else if (cameramode == 1) {
		//視点座標
		viewProjection_.eye = { 50,0,3 };
		//viewProjection_.target = { 30, 0,0 };

		viewProjection_.eye.z = paper_->GetWorldPosition(touchPaperNum).z;
		viewProjection_.target.z = paper_->GetWorldPosition(touchPaperNum).z;

		viewProjection_.Initialize();
	}
	else if (cameramode == 2) {
		//視点座標
		viewProjection_.eye = { 500,0,3 };
		viewProjection_.target = { 30, 0,0 };

		viewProjection_.eye.z = paper_->GetWorldPosition(touchPaperNum).z;
		viewProjection_.target.z = paper_->GetWorldPosition(touchPaperNum).z;

		viewProjection_.Initialize();
	}

	//debugText_->SetPos(0, 80);
	//debugText_->Printf("PaperTrans[%d] = (%f,%f,%f)", touchPaperNum, paper_->GetWorldPosition(touchPaperNum).x, paper_->GetWorldPosition(touchPaperNum).y, paper_->GetWorldPosition(touchPaperNum).z);

	//debugText_->SetPos(0, 140);
	//debugText_->Printf("scene = %d", scene);
	//debugText_->SetPos(0, 160);
	//debugText_->Printf("shot = %d", shot);
	//debugText_->SetPos(0, 180);
	//debugText_->Printf("isLand = %d", isLand);

	//シーン切り替え

	if (scene == 0) {
		if (input_->TriggerKey(DIK_SPACE)) {
			scene = 1;
		}
	}
	else if (scene == 1 && paper_->GetIsCol(touchPaperNum) == 1) {
		scene = 2;
		cameramode = 2;
	}
	else if (scene == 2 && shot < 3 && isLand == 1) {

		scene = 1;
		fan_->Reset();
		isLand = 0;
	}
	else if (scene == 2 && shot >= 3 && isLand == 1) {

		scene = 3;
		isLand = 0;

	}
	else if (scene == 3) {
		if (input_->TriggerKey(DIK_SPACE)) {
			scene = 0;
			shot = 0;
			paper_->Reset();
			fan_->Reset();

		}

		if (paper_->GetWorldPosition(beginshot[0]).z > paper_->GetWorldPosition(beginshot[1]).z) {
			highScore = paper_->GetWorldPosition(beginshot[0]).z;
		}
		else {
			highScore = paper_->GetWorldPosition(beginshot[1]).z;
		}

		if (paper_->GetWorldPosition(beginshot[2]).z > highScore) {
			highScore = paper_->GetWorldPosition(beginshot[2]).z;
		}
	}


}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	if (scene == 1 || scene == 2 || scene == 3) {

		//自キャラの更新
		fan_->Draw(viewProjection_);

		//紙描画
		paper_->Draw(viewProjection_);

	}
	//当たり判定
	CheckAllCollisions();

	////3Dモデル描画
	//model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//debugText_->SetPos(0, 20);
	//debugText_->Printf("eye(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);

	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() {
	//判定対象AとBの座標
	Vector3 posA, posB;

	//自弾リストの取得
	const std::list<std::unique_ptr<FanWind>>& fanWinds = fan_->GetBullets();

#pragma region 自弾と敵弾の当たり判定

	//自弾と敵弾の当たり判定
	for (const std::unique_ptr<FanWind>& fanwind : fanWinds) {
		for (int i = 0; i < 10; i++) {

			//自弾の座標
			posA = fanwind->GetWorldPosition();
			//敵弾の座標
			posB = paper_->GetWorldPosition(i);

			//半径
			float posAR = 1;
			float posBR = 1;

			if (((posA.x - posB.x) * (posA.x - posB.x)) + ((posA.y - posB.y) * (posA.y - posB.y)) + ((posA.z - posB.z) * (posA.z - posB.z)) <= ((posAR + posBR) * (posAR + posBR))) {

				//自弾の衝突時コールバックを呼び出す
				fanwind->OnCollision();
				//敵弾の衝突時コールバックを呼び出す
				paper_->OnCollision(i, fan_->GetWindPower(), fan_->GetWorldPosition());

				touchPaperNum = i;

				//debugText_->SetPos(0, 40);
				//debugText_->Printf("atatta");
			}
		}
	}
#pragma endregion
}