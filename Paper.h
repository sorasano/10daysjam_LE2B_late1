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
#include <time.h>

class Paper
{
public:

	//初期化
	void Initialize(Model* planeModel, Model* circleModel, uint32_t planeTextureHandle, uint32_t circleTextureHandle);

	//更新
	void Update();

	//配置
	void Set();

	//座標配置
	void SetTrans();

	//角度配置
	void SetRot();

	//描画
	void Draw(ViewProjection& viewProjection_);

private:
	//ワールド変換データ
	WorldTransform worldtransform_;

	//モデル
	Model* planeModel_ = nullptr;
	Model* circleModel_ = nullptr;

	//テクスチャハンドル
	uint32_t planeTextureHandle_ = 0u;
	uint32_t circleTextureHandle_ = 0u;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	//アフィン行列
	Affine* affine_;

	//配置する数
	const int max = 10;

	//座標
	Vector3 trans[10] = {};
	//角度
	Vector3 rot[10] = {};

	//変わらない値(統一)
	float transY = 0;
	float transZ = 0;

	float rotX = 0;
	float rotZ = 0;

	//配置する位置の端
	float maxLeft = -20.0f;
	float maxRight = 20.0f;

	//配置する最小間隔
	float space = 2.0f;

	//飛行機型か丸型か
	int type = 0;//0飛行機 1丸

};

