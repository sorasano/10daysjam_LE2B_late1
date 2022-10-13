#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <DirectXMath.h>
#include "DebugCamera.h"
#include "Fan.h"
#include "Affine.h"
#include "Paper.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
  /// <summary>
  /// コンストクラタ
  /// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//3Dモデル
	Model* model_ = nullptr;

	//ビュープロジェクション
	ViewProjection viewProjection_;

	//デバックカメラ
	DebugCamera* debugCamera_ = nullptr;

	//カメラモード
	int cameramode = 0;//0 上から //1横から

	//デバックカメラ有効
	bool isDebugCameraActive_ = false;

	//自キャラ
	Fan* fan_ = nullptr;

	//紙
	Paper* paper_ = nullptr;

	//何番の紙飛行機が当たったか
	int touchPaperNum = 0;

	//0　タイトル　1射撃準備 2紙飛行機飛び 3リザルト
	int scene = 0;

	//何回打ったか
	int shot = 0;
	//地面についてるか
	int isLand = 0;

	////何番をもう打ったか
	//int beginshot[3] = {};

	//////アフィン変換
	//Affine* affine_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};