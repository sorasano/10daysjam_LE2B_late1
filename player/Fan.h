#pragma once

#include "WorldTransform.h"
#include "WinApp.h"
#include "Model.h"
#include "DebugText.h"
#include "Input.h"
#include "Affine.h"
#include "FanWind.h"
#include <memory>
#include <list>
#include "Matrix4.h"

class Fan {

public:
	//初期化
	void Initialize(Model* model, uint32_t textureHandle);

	//更新
	void Update();

	//描画
	void Draw(ViewProjection& viewProjection_);

	//旋回
	void Rotate();

	//攻撃
	void Attack();

	//移動
	void Move();

	//mode変更
	void ModeChange();

	//風量ゲージ(パワーを測る)
	void measureWindPower();

	//ワールド座標を取得
	Vector3 GetWorldPosition();

	//衝突したら呼び出されるコールバック関数
	void OnCollision();

	//弾リストを取得
	const std::list<std::unique_ptr<FanWind>>& GetBullets() { return bullets_; }

	float GetWindPower();

private:
	//ワールド変換データ
	WorldTransform worldtransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	//アフィン行列
	Affine* affine_;

	//扇風機の状態 0停止 1右 2左 3発射後
	int mode = 1;

	//キャラクターの移動速さ
	const float speed = 0.1f;

	//移動限界距離
	int moveLimitLeft = -20;
	int moveLimitRight = 20;

	//風量
	float windPower = 0;
	//風量の上昇量
	float powerSpeed = 0.1;
	//風量の限界値
	float maxPower = 10;

	int push = 0;

private:
	//弾
	std::list<std::unique_ptr<FanWind>> bullets_;
};