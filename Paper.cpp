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

	//for (int i = 0; i < max; i++) {
	//	paperAirplane_[i] = new PaperAirplane;
	//	paperCircle_[i] = new PaperCircle;
	//}

};

//�X�V
void Paper::Update() {

	flag++;

	if (flag == 1) {
		Set();
	}

	debugText_->SetPos(0, 80);
	debugText_->Printf("PaperTrans[0] = (%f,%f,%f)\nPaperTrans[1] = (%f,%f,%f)", trans[0].x, trans[0].y, trans[0].z, trans[1].x, trans[1].y, trans[1].z);

};

//�z�u
void Paper::Set() {

	//for (int i = 0; i < max; i++) {

	//	SetTrans(i);
	//	SetRot(i);

	//}

	int num = 0;

	for (std::unique_ptr<PaperAirplane>& paperAirplane : paperAirplanes_) {
		SetTrans(num);
		SetRot(num);
		paperAirplane->Initialize(planeModel_,planeTextureHandle_,trans[num],rot[num]);
		num++;
	}


}

//���W�z�u
void Paper::SetTrans(int i) {

	//�����V�[�h������
	std::random_device seed_gen;
	//�����Z���k�E�c�C�X�^�[
	std::mt19937_64 engine(seed_gen());
	//�����͈�(���W�p)
	std::uniform_real_distribution<float> transDist(0.0f, space);


	//������z�u����Ԋu�̍ő�l�ƍŏ��l�ŗ��������(*100��/100��int��float)
	trans[i].x = transDist(engine);

	if (i == 0) {
		trans[0].x = maxLeft;
	}

	//�O�̍��W�𑫂��č��W���ړ�
	trans[i].x += beforeTrans;
	//���̍��W���L�^ + size�ł��Ԃ���Ȃ���
	beforeTrans = (trans[i].x + size);

	trans[i].y = transY;
	trans[i].z = transZ;

}

//�p�x�z�u
void Paper::SetRot(int i) {

	//�����V�[�h������
	std::random_device seed_gen;
	//�����Z���k�E�c�C�X�^�[
	std::mt19937_64 engine(seed_gen());
	//�����͈�(��]�p�p)
	std::uniform_real_distribution<float> rotDist(0.0f, rotdiff);


	//������z�u����Ԋu�̍ő�l�ƍŏ��l�ŗ��������(*100��/100��int��float)
	rot[i].y = rotDist(engine);

	if (i == 0) {
		rot[0].y = maxLeft;
	}

	rot->x = rotX;
	rot->z = rotZ;

}


//�`��
void Paper::Draw(ViewProjection& viewProjection_) {

	if (flag != 0) {
		for (std::unique_ptr<PaperAirplane>& paperAirplane : paperAirplanes_) {
			paperAirplane->Draw(viewProjection_);
		}
	}

	////3D���f����`��
	//model_->Draw(worldtransform_, viewProjection_, textureHandle_);

};