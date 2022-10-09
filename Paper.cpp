#include "Paper.h"

//初期化
void Paper::Initialize(Model* planeModel, Model* circleModel, uint32_t planeTextureHandle, uint32_t circleTextureHandle) {

	////NULLポインタチェック
	//assert(model);

	////因数としてうけとったデータを記録
	//モデル
	planeModel_ = planeModel;
	circleModel_ = circleModel;

	//テクスチャハンドル
	planeTextureHandle_ = planeTextureHandle;
	circleTextureHandle_ = circleTextureHandle;

	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ワールド変換初期化
	worldtransform_.Initialize();

	//アフィン行列
	affine_ = new Affine();

	for (int i = 0; i < max; i++) {
		paperAirplane_[i] = new PaperAirplane;
		paperCircle_[i] = new PaperCircle;
	}

};

//更新
void Paper::Update() {

	flag++;

	if (flag == 1) {
		Set();
	}

	for(int i = 0;i < 10;i++){
		paperAirplane_[i]->Update();
	}
	debugText_->SetPos(0, 80);
	debugText_->Printf("PaperTrans[0] = (%f,%f,%f)\nPaperTrans[1] = (%f,%f,%f)", trans[0].x, trans[0].y, trans[0].z, trans[1].x, trans[1].y, trans[1].z);

};

//配置
void Paper::Set() {

	for (int i = 0; i < max; i++) {

		SetTrans(i);
		SetRot(i);
		paperAirplane_[i]->Initialize(planeModel_,planeTextureHandle_,trans[i],rot[i]);

	}


}

//座標配置
void Paper::SetTrans(int i) {

	//乱数シード生成器
	std::random_device seed_gen;
	//メルセンヌ・ツイスター
	std::mt19937_64 engine(seed_gen());
	//乱数範囲(座標用)
	std::uniform_real_distribution<float> transDist(0.0f, space);


	//乱数を配置する間隔の最大値と最小値で乱数を取る(*100と/100はint→float)
	trans[i].x = transDist(engine);

	if (i == 0) {
		trans[0].x = maxLeft;
	}

	//前の座標を足して座標を移動
	trans[i].x += beforeTrans;
	//今の座標を記録 + sizeでかぶりをなくす
	beforeTrans = (trans[i].x + size);

	trans[i].y = transY;
	trans[i].z = transZ;

}

//角度配置
void Paper::SetRot(int i) {

	//乱数シード生成器
	std::random_device seed_gen;
	//メルセンヌ・ツイスター
	std::mt19937_64 engine(seed_gen());
	//乱数範囲(回転角用)
	std::uniform_real_distribution<float> rotDist(0.0f, rotdiff);


	//乱数を配置する間隔の最大値と最小値で乱数を取る(*100と/100はint→float)
	rot[i].y = rotDist(engine);

	if (i == 0) {
		rot[0].y = maxLeft;
	}

	rot->x = rotX;
	rot->z = rotZ;

}


//描画
void Paper::Draw(ViewProjection& viewProjection_) {

	if (flag != 0) {
		for (int i = 0; i < max; i++) {
			paperAirplane_[i]->Draw(viewProjection_);
		}
	}
	////3Dモデルを描画
	//model_->Draw(worldtransform_, viewProjection_, textureHandle_);

};

Vector3 Paper::GetWorldPosition(int i) {

	Vector3 Pos = trans[i];
	return Pos;

}

void Paper::OnCollision(int i) {
	paperAirplane_[i]->OnCollision();
}
