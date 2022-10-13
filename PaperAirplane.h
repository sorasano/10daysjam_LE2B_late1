#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "Affine.h"
#include "DebugText.h"

class PaperAirplane
{
public:

	void Initialize(Model* model,uint32_t textureHandle,Vector3 trans, Vector3 rot);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	//bool IsDead() const { return isDead_; }

	//�Փ˂�����Ăяo�����R�[���o�b�N�֐�
	void OnCollision(float windPower, Vector3 fanTrans);

	//���[���h���W���擾
	Vector3 GetWorldPosition();

	//���x�v����
	void CalculationSpeed();

	void Move();

	//���x�Ȃǂ��Z�b�g
	void Set(float windPower, Vector3 fanTrans);

	bool GetIsLanding() const { return isLanding_; }

	void LandingJudge();

	void Reset();
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldtransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	DebugText* debugText_ = nullptr;

	//����
	static const int32_t kLifeTime = 60 * 5;
	//�f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;
	//�f�X�t���O
	bool isDead_ = false;

	//0 ��~ 1 �ړ�
	int move_ = 0;

	//�A�t�B���s��
	Affine* affine_ = nullptr;

	//�����X�s�[�h
	Vector3 velocity_ = { 0,0,0 };

	float endY = -20;
	bool isLanding_ = 0;

private:
	//�ʏ�X�s�[�h
	float speed_ = 0.1;

	//�����X�s�[�h
	float fallSpeed_ = 0.1;

	//������
	float decelerationRate_ = 0.001;
};

