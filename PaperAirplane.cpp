#include "PaperAirplane.h"
#include "GameScene.h"

const float PI = 3.1415926535;

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

	debugText_ = DebugText::GetInstance();

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
	

	CalculationSpeed();

	if (move_ == 1) {
		Move();
	}

	//��������
	LandingJudge();

}

void PaperAirplane::Draw(const ViewProjection& viewProjection) {

	//3D���f����`��
	model_->Draw(worldtransform_, viewProjection, textureHandle_);

}

void PaperAirplane::OnCollision(float windPower, Vector3 fanTrans) {
	move_ = 1;
	Set(windPower,fanTrans);
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

void PaperAirplane::CalculationSpeed()
{
	//���x���v�Z
	velocity_ = {0,-fallSpeed_,speed_};

	//����
	if (speed_ >= 0.1) {
		speed_ -= decelerationRate_;
	}
}

void PaperAirplane::Move()
{

	//�s��X�V
	worldtransform_.translation_ += velocity_;
	worldtransform_.matWorld_ = affine_->World(affine_->Scale(affine_->Scale_), affine_->Rot(affine_->RotX(worldtransform_.rotation_.x), affine_->RotY(worldtransform_.rotation_.y), affine_->RotZ(worldtransform_.rotation_.z)), affine_->Trans(worldtransform_.translation_));
	worldtransform_.TransferMatrix();

}

void PaperAirplane::Set(float windPower,Vector3 fanTrans)
{
	//���x,�����X�s�[�h,�������Z�b�g

	//���������̂܂܃X�s�[�h�ɑ��
	speed_ = (windPower / 10) + 0.01;//0.1�`1.1�͈̔�

	//����s�@�Ɛ�@�̍��W�̍��������X�s�[�h
	//if���Ń}�C�i�X�ɂȂ�Ȃ��悤�ɂ���
	if ((fanTrans.x - worldtransform_.translation_.x) > 0) {
		fallSpeed_ = (fanTrans.x - worldtransform_.translation_.x) / 10;
	}
	else {
		fallSpeed_ = (worldtransform_.translation_.x- fanTrans.x) / 10;
	}

	if (fallSpeed_ <= 0.02) {
		fallSpeed_ = 0.02;
	}

	////���������v�Z,�p�x��0(�܂�����)�ɋ߂��قǌ������͏��Ȃ�
	//if (worldtransform_.rotation_.y < PI) {
	//	decelerationRate_ = worldtransform_.rotation_.y / 100;
	//}
	//else {
	//	decelerationRate_ = (PI - worldtransform_.rotation_.y) / 100;
	//}

	//���������v�Z,�p�x��0(�܂�����)�ɋ߂��قǌ������͏��Ȃ�
	if (worldtransform_.rotation_.y < PI) {
		decelerationRate_ = (worldtransform_.rotation_.y);
	}
	else {
		decelerationRate_ = (worldtransform_.rotation_.y - PI);

		if (decelerationRate_ < (PI / 2)) {
			decelerationRate_ = (PI - decelerationRate_);
		}
		else {
			decelerationRate_ = (PI - decelerationRate_);
			//decelerationRate_ += (decelerationRate_ + decelerationRate_);
		}

	}

	decelerationRate_ = decelerationRate_ / 100;
}

void PaperAirplane::LandingJudge()
{

	if (worldtransform_.translation_.y <= endY) {
		isLanding_ = 1;
		move_ = 0;
	}

}

void PaperAirplane::Reset()
{
	//0 ��~ 1 �ړ�
	move_ = 0;
	isLanding_ = 0;

}

