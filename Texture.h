#pragma once

#include "Affine.h"
#include "PlayerBullet.h"
#include "Matrix4.h"

class Texture
{
public:

	//初期化
	void Initialize(Model *model);

	//更新
	void Update();

	//描画
	void DrawTitle(ViewProjection& viewProjection_);

	void DrawClear(ViewProjection& viewProjection_);

	void DrawGameOver(ViewProjection& viewProjection_);

private:

	//ワールド変換データ
	WorldTransform worldtransform_;
	//モデル
	Model* model_ = nullptr;

	//テクスチャハンドル
	uint32_t titleTextureHandle_ = 0u;
	uint32_t clearTextureHandle_ = 0u;
	uint32_t gameOverTextureHandle_ = 0u;

	DebugText* debugText_ = nullptr;

	//アフィン行列
	Affine* affine_ = nullptr;

	Vector3 position = Vector3(0, 0, -48);

};

