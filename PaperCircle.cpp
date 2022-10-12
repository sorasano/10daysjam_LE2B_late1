#include "PaperCircle.h"
#include "GameScene.h"

void PaperCircle::Initialize(Model* model, uint32_t textureHandle, Vector3 trans, Vector3 rot) {

	//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("paperCircle.png");

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

void PaperCircle::Update() {

	////���W���ړ�������
	//worldtransform_.translation_ += velocity_;
	////�s��X�V
	//worldtransform_.matWorld_ = affine_->World(affine_->Scale(affine_->Scale_), affine_->Rot(affine_->RotX(affine_->Rot_.x), affine_->RotY(affine_->Rot_.y), affine_->RotZ(affine_->Rot_.z)), affine_->Trans(worldtransform_.translation_));
	//worldtransform_.TransferMatrix();

	//if (--deathTimer_ <= 0) {
	//	isDead_ = true;
	//}

	Vector3 velocity_ = { 0,0,1 };

	if (move == 1) {
		//�s��X�V
		worldtransform_.translation_ += velocity_;
		worldtransform_.matWorld_ = affine_->World(affine_->Scale(affine_->Scale_), affine_->Rot(affine_->RotX(worldtransform_.rotation_.x), affine_->RotY(worldtransform_.rotation_.y), affine_->RotZ(worldtransform_.rotation_.z)), affine_->Trans(worldtransform_.translation_));
		worldtransform_.TransferMatrix();

	}

}

void PaperCircle::Draw(const ViewProjection& viewProjection) {

	//3D���f����`��
	model_->Draw(worldtransform_, viewProjection, textureHandle_);

}

void PaperCircle::OnCollision() {
	move = 1;
}

Vector3 PaperCircle::GetWorldPosition() {
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��̕��s�ړ��������擾
	worldPos.x = worldtransform_.matWorld_.m[3][0];
	worldPos.y = worldtransform_.matWorld_.m[3][1];
	worldPos.z = worldtransform_.matWorld_.m[3][2];

	return worldPos;
}