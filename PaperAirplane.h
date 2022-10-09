#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "Affine.h"

class PaperAirplane
{
public:

	void Initialize(Model* model,uint32_t textureHandle,Vector3 trans, Vector3 rot);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	//bool IsDead() const { return isDead_; }

	//�Փ˂�����Ăяo�����R�[���o�b�N�֐�
	void OnCollision();

	//���[���h���W���擾
	Vector3 GetWorldPosition();

private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldtransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//����
	static const int32_t kLifeTime = 60 * 5;
	//�f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;
	//�f�X�t���O
	bool isDead_ = false;

	//0 ��~ 1 �ړ�
	int move = 0;

	//�A�t�B���s��
	Affine* affine_ = nullptr;
};

