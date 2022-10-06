#pragma once

#include "Affine.h"
#include "PlayerBullet.h"
#include "Matrix4.h"

class Texture
{
public:

	//������
	void Initialize(Model *model);

	//�X�V
	void Update();

	//�`��
	void DrawTitle(ViewProjection& viewProjection_);

	void DrawClear(ViewProjection& viewProjection_);

	void DrawGameOver(ViewProjection& viewProjection_);

private:

	//���[���h�ϊ��f�[�^
	WorldTransform worldtransform_;
	//���f��
	Model* model_ = nullptr;

	//�e�N�X�`���n���h��
	uint32_t titleTextureHandle_ = 0u;
	uint32_t clearTextureHandle_ = 0u;
	uint32_t gameOverTextureHandle_ = 0u;

	DebugText* debugText_ = nullptr;

	//�A�t�B���s��
	Affine* affine_ = nullptr;

	Vector3 position = Vector3(0, 0, -48);

};

