#include "PaperAirplane.h"
#include "GameScene.h"

void PaperAirplane::Initialize(Model* model, uint32_t textureHandle,Vector3 trans,Vector3 rot) {

	//NULLポインタチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("paperAirplane.png");

	//アフィン行列
	affine_ = new Affine();

	//ワールド変換初期化
	worldtransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldtransform_.translation_ = { trans.x,trans.y,trans.z };
	worldtransform_.rotation_ = { rot.x,rot.y,rot.z };

	//行列更新
	worldtransform_.matWorld_ = affine_->World(affine_->Scale(affine_->Scale_), affine_->Rot(affine_->RotX(worldtransform_.rotation_.x), affine_->RotY(worldtransform_.rotation_.y), affine_->RotZ(worldtransform_.rotation_.z)), affine_->Trans(worldtransform_.translation_));
	worldtransform_.TransferMatrix();

}

void PaperAirplane::Update() {

	////座標を移動させる
	//worldtransform_.translation_ += velocity_;
	////行列更新
	//worldtransform_.matWorld_ = affine_->World(affine_->Scale(affine_->Scale_), affine_->Rot(affine_->RotX(affine_->Rot_.x), affine_->RotY(affine_->Rot_.y), affine_->RotZ(affine_->Rot_.z)), affine_->Trans(worldtransform_.translation_));
	//worldtransform_.TransferMatrix();

	//if (--deathTimer_ <= 0) {
	//	isDead_ = true;
	//}

}

void PaperAirplane::Draw(const ViewProjection& viewProjection) {

	//3Dモデルを描画
	model_->Draw(worldtransform_, viewProjection, textureHandle_);

}

void PaperAirplane::OnCollision() {
	isDead_ = true;
}

Vector3 PaperAirplane::GetWorldPosition() {
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行移動成分を取得
	worldPos.x = worldtransform_.matWorld_.m[3][0];
	worldPos.y = worldtransform_.matWorld_.m[3][1];
	worldPos.z = worldtransform_.matWorld_.m[3][2];

	return worldPos;
}