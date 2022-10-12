#pragma once

#include "WorldTransform.h"
#include "WinApp.h"
#include "Model.h"
#include "DebugText.h"
#include "Input.h"
#include "Affine.h"
#include "FanWind.h"
#include <memory>
#include <list>
#include "Matrix4.h"

class Fan {

public:
	//������
	void Initialize(Model* model, uint32_t textureHandle);

	//�X�V
	void Update();

	//�`��
	void Draw(ViewProjection& viewProjection_);

	//����
	void Rotate();

	//�U��
	void Attack();

	//�ړ�
	void Move();

	//mode�ύX
	void ModeChange();

	//���ʃQ�[�W(�p���[�𑪂�)
	void measureWindPower();

	//���[���h���W���擾
	Vector3 GetWorldPosition();

	//�Փ˂�����Ăяo�����R�[���o�b�N�֐�
	void OnCollision();

	//�e���X�g���擾
	const std::list<std::unique_ptr<FanWind>>& GetBullets() { return bullets_; }

	float GetWindPower();

private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldtransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	//�A�t�B���s��
	Affine* affine_;

	//��@�̏�� 0��~ 1�E 2�� 3���ˌ�
	int mode = 1;

	//�L�����N�^�[�̈ړ�����
	const float speed = 0.1f;

	//�ړ����E����
	int moveLimitLeft = -20;
	int moveLimitRight = 20;

	//����
	float windPower = 0;
	//���ʂ̏㏸��
	float powerSpeed = 0.1;
	//���ʂ̌��E�l
	float maxPower = 10;

	int push = 0;

private:
	//�e
	std::list<std::unique_ptr<FanWind>> bullets_;
};