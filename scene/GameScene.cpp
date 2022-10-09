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
	viewProjection_.eye = {0,30,-30};
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

	//自キャラの更新
	fan_->Update();

	paper_->Update();

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

	//自キャラの更新
	fan_->Draw(viewProjection_);

	//紙描画
	paper_->Draw(viewProjection_);

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
//
//#pragma region 自キャラと敵弾の当たり判定
//
//	//自キャラの座標
//	posA = fan_->GetWorldPosition();
//	//自キャラと敵弾すべての当たり判定
//	for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets) {
//		//敵弾の座標
//		posB = bullet->GetWorldPosition();
//
//		//半径
//		float posAR = 1;
//		float posBR = 1;
//
//		if (((posA.x - posB.x) * (posA.x - posB.x)) + ((posA.y - posB.y) * (posA.y - posB.y)) + ((posA.z - posB.z) * (posA.z - posB.z)) <= ((posAR + posBR) * (posAR + posBR))) {
//
//			//自キャラの衝突時コールバックを呼び出す
//			fan_->OnCollision();
//			//敵弾の衝突時コールバックを呼び出す
//			bullet->OnCollision();
//
//			//debugText_->SetPos(0, 40);
//			//debugText_->Printf("atatta");
//
//		}
//	}
//#pragma endregion
//
//#pragma region 自弾と敵キャラの当たり判定
//
//	//自弾の座標
//	posA = enemy_->GetWorldPosition();
//	//自弾と敵の当たり判定
//	for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets) {
//		//敵の座標
//		posB = bullet->GetWorldPosition();
//
//		//半径
//		float posAR = 1;
//		float posBR = 1;
//
//		if (((posA.x - posB.x) * (posA.x - posB.x)) + ((posA.y - posB.y) * (posA.y - posB.y)) + ((posA.z - posB.z) * (posA.z - posB.z)) <= ((posAR + posBR) * (posAR + posBR))) {
//
//			//自弾の衝突時コールバックを呼び出す
//			bullet->OnCollision();
//			//敵の衝突時コールバックを呼び出す
//			enemy_->OnCollision();
//
//			//debugText_->SetPos(0, 40);
//			//debugText_->Printf("atatta");
//
//		}
//	}
//
//#pragma endregion
//
//#pragma region 自弾と敵弾の当たり判定
//
//	//自弾と敵弾の当たり判定
//	for (const std::unique_ptr<FanWind>& fanwind : fanWinds) {
//		for (int i = 0; i < 10;i++) {
//
//			//自弾の座標
//			posA = fanwind->GetWorldPosition();
//			//敵弾の座標
//			posB = enemyBullet->GetWorldPosition();
//
//			//半径
//			float posAR = 1;
//			float posBR = 1;
//
//			if (((posA.x - posB.x) * (posA.x - posB.x)) + ((posA.y - posB.y) * (posA.y - posB.y)) + ((posA.z - posB.z) * (posA.z - posB.z)) <= ((posAR + posBR) * (posAR + posBR))) {
//
//				//自弾の衝突時コールバックを呼び出す
//				playerBullet->OnCollision();
//				//敵弾の衝突時コールバックを呼び出す
//				enemyBullet->OnCollision();
//
//				//debugText_->SetPos(0, 40);
//				//debugText_->Printf("atatta");
//			}
//		}
//	}
//#pragma endregion
}