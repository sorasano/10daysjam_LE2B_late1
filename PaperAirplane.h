#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "Affine.h"
#include "DebugText.h"

class PaperAirplane
{
public:

	void Initialize(Model* model,uint32_t textureHandle,Vector3 trans, Vector3 rot);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	//bool IsDead() const { return isDead_; }

	//衝突したら呼び出されるコールバック関数
	void OnCollision(float windPower, Vector3 fanTrans);

	//ワールド座標を取得
	Vector3 GetWorldPosition();

	//速度計さん
	void CalculationSpeed();

	void Move();

	//速度などをセット
	void Set(float windPower, Vector3 fanTrans);

	bool GetIsLanding() const { return isLanding_; }

	void LandingJudge();

	void Reset();
private:
	//ワールド変換データ
	WorldTransform worldtransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	DebugText* debugText_ = nullptr;

	//寿命
	static const int32_t kLifeTime = 60 * 5;
	//デスタイマー
	int32_t deathTimer_ = kLifeTime;
	//デスフラグ
	bool isDead_ = false;

	//0 停止 1 移動
	int move_ = 0;

	//アフィン行列
	Affine* affine_ = nullptr;

	//統合スピード
	Vector3 velocity_ = { 0,0,0 };

	float endY = -20;
	bool isLanding_ = 0;

private:
	//通常スピード
	float speed_ = 0.1;

	//落下スピード
	float fallSpeed_ = 0.1;

	//減速率
	float decelerationRate_ = 0.001;
};

