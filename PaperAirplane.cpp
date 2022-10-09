#include "PaperAirplane.h"
#include "GameScene.h"

void PaperAirplane::Initialize(Model* model, uint32_t textureHandle,Vector3 trans,Vector3 rot) {

	//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("paperAirplane.png");

	//�A�t�B���s��
	affine_ = new Affine();

	//���[���h�ϊ�������
	worldtransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldtransform_.translation_ = { trans.x,trans.y,trans.z };
	worldtransform_.rotation_ = { rot.x,rot.y,rot.z };

	//�s��X�V
	worldtransform_.matWorld_ = affine_->World(affine_->Scale(affine_->Scale_), affine_->Rot(affine_->RotX(worldtransform_.rotation_.x), affine_->RotY(worldtransform_.rotation_.y), affine_->RotZ(worldtransform_.rotation_.z)), affine_->Trans(worldtransform_.translation_));
	worldtransform_.TransferMatrix();

}

void PaperAirplane::Update() {

	////���W���ړ�������
	//worldtransform_.translation_ += velocity_;
	////�s��X�V
	//worldtransform_.matWorld_ = affine_->World(affine_->Scale(affine_->Scale_), affine_->Rot(affine_->RotX(affine_->Rot_.x), affine_->RotY(affine_->Rot_.y), affine_->RotZ(affine_->Rot_.z)), affine_->Trans(worldtransform_.translation_));
	//worldtransform_.TransferMatrix();

	//if (--deathTimer_ <= 0) {
	//	isDead_ = true;
	//}

}

void PaperAirplane::Draw(const ViewProjection& viewProjection) {

	//3D���f����`��
	model_->Draw(worldtransform_, viewProjection, textureHandle_);

}

void PaperAirplane::OnCollision() {
	isDead_ = true;
}

Vector3 PaperAirplane::GetWorldPosition() {
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��̕��s�ړ��������擾
	worldPos.x = worldtransform_.matWorld_.m[3][0];
	worldPos.y = worldtransform_.matWorld_.m[3][1];
	worldPos.z = worldtransform_.matWorld_.m[3][2];

	return worldPos;
}