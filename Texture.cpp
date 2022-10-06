#include "Texture.h"


void Texture::Initialize(Model* model) {

	model_ = model;
	//シングルトンインスタンスを取得する
	debugText_ = DebugText::GetInstance();

	//アフィン行列
	affine_ = new Affine();

	//ワールド変換初期化
	worldtransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldtransform_.translation_ = { position.x,position.y,position.z };

	//行列更新
	worldtransform_.matWorld_ = affine_->World(affine_->Scale(affine_->Scale_), affine_->Rot(affine_->RotX(affine_->Rot_.x), affine_->RotY(affine_->Rot_.y), affine_->RotZ(affine_->Rot_.z)), affine_->Trans(worldtransform_.translation_));
	worldtransform_.TransferMatrix();

	titleTextureHandle_ = TextureManager::Load("Title.png");
	clearTextureHandle_ = TextureManager::Load("CLEAR.png");
	gameOverTextureHandle_ = TextureManager::Load("GAMEOVER.png");

}

void Texture::Update() {
	worldtransform_.matWorld_ = affine_->World(affine_->Scale(affine_->Scale_), affine_->Rot(affine_->RotX(affine_->Rot_.x), affine_->RotY(affine_->Rot_.y), affine_->RotZ(affine_->Rot_.z)), affine_->Trans(worldtransform_.translation_));
}

void Texture::DrawTitle(ViewProjection& viewProjection_) {

	//3Dモデルを描画
	model_->Draw(worldtransform_, viewProjection_, titleTextureHandle_);


}

void Texture::DrawClear(ViewProjection& viewProjection_) {

	//3Dモデルを描画
	model_->Draw(worldtransform_, viewProjection_, clearTextureHandle_);


}

void Texture::DrawGameOver(ViewProjection& viewProjection_) {

	//3Dモデルを描画
	model_->Draw(worldtransform_, viewProjection_, gameOverTextureHandle_);


}