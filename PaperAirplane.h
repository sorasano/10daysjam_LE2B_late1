#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "Affine.h"

class PaperAirplane
{
public:

	void Initialize(Model* model,uint32_t textureHandle,Vector3 trans, Vector3 rot);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	//bool IsDead() const { return isDead_; }

	//衝突したら呼び出されるコールバック関数
	void OnCollision();

	//ワールド座標を取得
	Vector3 GetWorldPosition();

private:
	//ワールド変換データ
	WorldTransform worldtransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//寿命
	static const int32_t kLifeTime = 60 * 5;
	//デスタイマー
	int32_t deathTimer_ = kLifeTime;
	//デスフラグ
	bool isDead_ = false;

	//0 停止 1 移動
	int move = 0;

	//アフィン行列
	Affine* affine_ = nullptr;
};

