#include "Paper.h"

//初期化
void Paper::Initialize(Model* planeModel, Model* circleModel, uint32_t planeTextureHandle, uint32_t circleTextureHandle) {

	////NULLポインタチェック
	//assert(model);

	////因数としてうけとったデータを記録
	//モデル
	planeModel_ = planeModel;
	circleModel_ = circleModel;

	//テクスチャハンドル
	planeTextureHandle_ = planeTextureHandle;
	circleTextureHandle_ = circleTextureHandle;

	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ワールド変換初期化
	worldtransform_.Initialize();

	//アフィン行列
	affine_ = new Affine();

};

//更新
void Paper::Update() {

};

//配置
void Paper::Set() {

	

}

//座標配置
void Paper::SetTrans() {

	//srand(time(NULL));               /* 乱数の初期化 */
	//trans[i] = rand() % 10;           /* 乱数の取得、剰余を用いて０～９の整数を得る */


}

//角度配置
void Paper::SetRot() {

}


//描画
void Paper::Draw(ViewProjection& viewProjection_) {

	////3Dモデルを描画
	//model_->Draw(worldtransform_, viewProjection_, textureHandle_);

};