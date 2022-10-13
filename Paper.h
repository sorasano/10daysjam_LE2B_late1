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
#include "PaperAirplane.h"
#include "PaperCircle.h"
#include <random>

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
	void SetTrans(int i);

	//角度配置
	void SetRot(int i);

	//描画
	void Draw(ViewProjection& viewProjection_);

	Vector3 GetWorldPosition(int i);

	void OnCollision(int i, float windPower, Vector3 fanTrans);

	bool GetIsLanding(int i) const { return isLanding_[i]; }

	void Reset();

	int GetIsCol(int i) { return isCol[i]; }

	void SetIsCol(int i);

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

	PaperAirplane *paperAirplane_[10];
	PaperCircle *paperCircle_[10];
	
	int flag = 0;

	//あったったか
	int isCol[10] = {};

	//座標
	Vector3 trans[10] = {};
	//角度
	Vector3 rot[10] = {};

	//飛行機型か丸型か
	int type[10] = {0,0,1,0,0,1,0,0,1,0};//0飛行機 1丸

	//落下したか
	int isLanding_[10] = {};

	//変わらない値(統一)
	float transY = 0;
	float transZ = 5;

	float rotX = 0;
	float rotZ = 0;

	//配置する位置の端
	float maxLeft = -30.0f;
	float maxRight = 20.0f;

	//配置する最大間隔
	float space = 4.0f;
	
	//回転差
	float rotdiff = 6;

	//前の座標
	float beforeTrans = 0;

	//サイズ
	int size = 4.5;

};

