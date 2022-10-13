#include "Paper.h"
const double PI = 3.141592653589;

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

	for (int i = 0; i < max; i++) {
		paperAirplane_[i] = new PaperAirplane;
		paperCircle_[i] = new PaperCircle;


		//��s�@���ی^�������_��
		//�����V�[�h������
		std::random_device seed_gen;
		//�����Z���k�E�c�C�X�^�[
		std::mt19937_64 engine(seed_gen());
		//�����͈�
		std::uniform_real_distribution<float> typeDist(0, 1.2);

		type[i] = typeDist(engine);
	}
};

//�X�V
void Paper::Update() {

	debugText_->SetPos(0, 120);
	debugText_->Printf("PaperRot[0] = (%f,%f,%f)\nPaperRot[1] = (%f,%f,%f)", rot[0].x, rot[0].y, rot[0].z, rot[1].x, rot[1].y, rot[1].z);

	flag++;

	if (flag == 1) {
		Set();
	}

	for(int i = 0;i < max;i++){
		if (type[i] == 0) {
			paperAirplane_[i]->Update();
			isLanding_[i] = paperAirplane_[i]->GetIsLanding();
		}
		else {
			paperCircle_[i]->Update();
			isLanding_[i] = paperCircle_[i]->GetIsLanding();
		}



	}


};

//�z�u
void Paper::Set() {

	for (int i = 0; i < max; i++) {

		SetTrans(i);
		SetRot(i);
		if (type[i] == 0) {
			paperAirplane_[i]->Initialize(planeModel_, planeTextureHandle_, trans[i], rot[i]);
		}
		else {
			paperCircle_[i]->Initialize(planeModel_, planeTextureHandle_, trans[i], rot[i]);
		}

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
	std::uniform_real_distribution<float> rotDist(0.0f, 2 * PI);


	//������z�u����Ԋu�̍ő�l�ƍŏ��l�ŗ��������(*100��/100��int��float)
	rot[i].y = rotDist(engine);

	rot->x = rotX;
	rot->z = rotZ;

}


//�`��
void Paper::Draw(ViewProjection& viewProjection_) {


	if (flag != 0) {
		for (int i = 0; i < max; i++) {
			if (type[i] == 0) {
				paperAirplane_[i]->Draw(viewProjection_);
			}
			else {
				paperCircle_[i]->Draw(viewProjection_);
			}
		}
	}
	////3D���f����`��
	//model_->Draw(worldtransform_, viewProjection_, textureHandle_);

};

Vector3 Paper::GetWorldPosition(int i) {

	Vector3 Pos = trans[i];

	if (type[i] == 0) {
		Pos = paperAirplane_[i]->GetWorldPosition();
	}
	else {
		Pos = paperCircle_[i]->GetWorldPosition();
	}

	return Pos;

}

void Paper::OnCollision(int i, float windPower, Vector3 fanTrans) {
	if (type[i] == 0) {
		paperAirplane_[i]->OnCollision(windPower,fanTrans);
	}
	else {
		paperCircle_[i]->OnCollision(windPower, fanTrans);
	}

	isCol[i] = 1;

}

void Paper::Reset()
{
	flag = 0;
	beforeTrans = 0;
	for (int i = 0; i < max; i++) {
		paperAirplane_[i]->Reset();
		paperCircle_[i]->Reset();
	}
}

void Paper::SetIsCol(int i)
{
	isCol[i] = 2;

}

