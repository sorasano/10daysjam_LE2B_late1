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

	Vector3 GetWorldPosition(int i);

	void OnCollision(int i, float windPower, Vector3 fanTrans);

	bool GetIsLanding(int i) const { return isLanding_[i]; }

	void Reset();

	int GetIsCol(int i) { return isCol[i]; }

	void SetIsCol(int i);

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

	PaperAirplane *paperAirplane_[10];
	PaperCircle *paperCircle_[10];
	
	int flag = 0;

	//������������
	int isCol[10] = {};

	//���W
	Vector3 trans[10] = {};
	//�p�x
	Vector3 rot[10] = {};

	//��s�@�^���ی^��
	int type[10] = {0,0,1,0,0,1,0,0,1,0};//0��s�@ 1��

	//����������
	int isLanding_[10] = {};

	//�ς��Ȃ��l(����)
	float transY = 0;
	float transZ = 5;

	float rotX = 0;
	float rotZ = 0;

	//�z�u����ʒu�̒[
	float maxLeft = -30.0f;
	float maxRight = 20.0f;

	//�z�u����ő�Ԋu
	float space = 4.0f;
	
	//��]��
	float rotdiff = 6;

	//�O�̍��W
	float beforeTrans = 0;

	//�T�C�Y
	int size = 4.5;

};

