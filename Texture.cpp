#include "Texture.h"


void Texture::Initialize(Model* model) {

	model_ = model;
	//�V���O���g���C���X�^���X���擾����
	debugText_ = DebugText::GetInstance();

	//�A�t�B���s��
	affine_ = new Affine();

	//���[���h�ϊ�������
	worldtransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldtransform_.translation_ = { position.x,position.y,position.z };

	//�s��X�V
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

	//3D���f����`��
	model_->Draw(worldtransform_, viewProjection_, titleTextureHandle_);


}

void Texture::DrawClear(ViewProjection& viewProjection_) {

	//3D���f����`��
	model_->Draw(worldtransform_, viewProjection_, clearTextureHandle_);


}

void Texture::DrawGameOver(ViewProjection& viewProjection_) {

	//3D���f����`��
	model_->Draw(worldtransform_, viewProjection_, gameOverTextureHandle_);


}