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
#include "PaperAirplane.h"
#include "PaperCircle.h"
#include <random>

class Paper
{
public:

	//������
	void Initialize(Model* planeModel, Model* circleModel, uint32_t planeTextureHandle, uint32_t circleTextureHandle);

	//�X�V
	void Update();

	//�z�u
	void Set();

	//���W�z�u
	void SetTrans(int i);

	//�p�x�z�u
	void SetRot(int i);

	//�`��
	void Draw(ViewProjection& viewProjection_);

	//�e���X�g���擾
	const std::list<std::unique_ptr<PaperAirplane>>& GetAirplanes() { return paperAirplanes_; }

	//�e���X�g���擾
	const std::list<std::unique_ptr<PaperCircle>>& GetCircles() { return paperCircles_; }


private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldtransform_;

	//���f��
	Model* planeModel_ = nullptr;
	Model* circleModel_ = nullptr;

	//�e�N�X�`���n���h��
	uint32_t planeTextureHandle_ = 0u;
	uint32_t circleTextureHandle_ = 0u;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	//�A�t�B���s��
	Affine* affine_;

	//�z�u���鐔
	const int max = 10;

	//PaperAirplane *paperAirplane_[10];
	//PaperCircle *paperCircle_[10];
	//�e
	std::list<std::unique_ptr<PaperAirplane>> paperAirplanes_;
	std::list<std::unique_ptr<PaperCircle>> paperCircles_;

	int flag = 0;

	//���W
	Vector3 trans[10] = {};
	//�p�x
	Vector3 rot[10] = {};

	//�ς��Ȃ��l(����)
	float transY = 0;
	float transZ = 5;

	float rotX = 0;
	float rotZ = 0;

	//�z�u����ʒu�̒[
	float maxLeft = -20.0f;
	float maxRight = 20.0f;

	//�z�u����ő�Ԋu
	float space = 4.0f;
	
	//��]��
	float rotdiff = 6;

	//�O�̍��W
	float beforeTrans = 0;

	//�T�C�Y
	int size = 2;

	//��s�@�^���ی^��
	int type = 0;//0��s�@ 1��


};

