#include "Paper.h"

//������
void Paper::Initialize(Model* planeModel, Model* circleModel, uint32_t planeTextureHandle, uint32_t circleTextureHandle) {

	////NULL�|�C���^�`�F�b�N
	//assert(model);

	////�����Ƃ��Ă����Ƃ����f�[�^���L�^
	//���f��
	planeModel_ = planeModel;
	circleModel_ = circleModel;

	//�e�N�X�`���n���h��
	planeTextureHandle_ = planeTextureHandle;
	circleTextureHandle_ = circleTextureHandle;

	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//���[���h�ϊ�������
	worldtransform_.Initialize();

	//�A�t�B���s��
	affine_ = new Affine();

};

//�X�V
void Paper::Update() {

};

//�z�u
void Paper::Set() {

	

}

//���W�z�u
void Paper::SetTrans() {

	//srand(time(NULL));               /* �����̏����� */
	//trans[i] = rand() % 10;           /* �����̎擾�A��]��p���ĂO�`�X�̐����𓾂� */


}

//�p�x�z�u
void Paper::SetRot() {

}


//�`��
void Paper::Draw(ViewProjection& viewProjection_) {

	////3D���f����`��
	//model_->Draw(worldtransform_, viewProjection_, textureHandle_);

};