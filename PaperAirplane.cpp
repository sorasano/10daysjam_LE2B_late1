#include "PaperAirplane.h"
#include "GameScene.h"

const float PI = 3.1415926535;

void PaperAirplane::Initialize(Model* model, uint32_t textureHandle,Vector3 trans,Vector3 rot) {

	//NULLポインタチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("paperAirplane.png");
	
	//アフィン行列
	affine_ = new Affine();

	//ワールド変換初期化
	worldtransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldtransform_.translation_ = { trans.x,trans.y,trans.z };
	worldtransform_.rotation_ = { rot.x,rot.y,rot.z };

	//行列更新
	worldtransform_.matWorld_ = affine_->World(affine_->Scale(affine_->Scale_), affine_->Rot(affine_->RotX(worldtransform_.rotation_.x), affine_->RotY(worldtransform_.rotation_.y), affine_->RotZ(worldtransform_.rotation_.z)), affine_->Trans(worldtransform_.translation_));
	worldtransform_.TransferMatrix();

	debugText_ = DebugText::GetInstance();

}

void PaperAirplane::Update() {

	////座標を移動させる
	//worldtransform_.translation_ += velocity_;
	////行列更新
	//worldtransform_.matWorld_ = affine_->World(affine_->Scale(affine_->Scale_), affine_->Rot(affine_->RotX(affine_->Rot_.x), affine_->RotY(affine_->Rot_.y), affine_->RotZ(affine_->Rot_.z)), affine_->Trans(worldtransform_.translation_));
	//worldtransform_.TransferMatrix();

	//if (--deathTimer_ <= 0) {
	//	isDead_ = true;
	//}
	

	CalculationSpeed();

	if (move_ == 1) {
		Move();
	}

	//落下判定
	LandingJudge();

}

void PaperAirplane::Draw(const ViewProjection& viewProjection) {

	//3Dモデルを描画
	model_->Draw(worldtransform_, viewProjection, textureHandle_);

}

void PaperAirplane::OnCollision(float windPower, Vector3 fanTrans) {
	move_ = 1;
	Set(windPower,fanTrans);
}

Vector3 PaperAirplane::GetWorldPosition() {
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行移動成分を取得
	worldPos.x = worldtransform_.matWorld_.m[3][0];
	worldPos.y = worldtransform_.matWorld_.m[3][1];
	worldPos.z = worldtransform_.matWorld_.m[3][2];

	return worldPos;
}

void PaperAirplane::CalculationSpeed()
{
	//速度を計算
	velocity_ = {0,-fallSpeed_,speed_};

	//減速
	if (speed_ >= 0.1) {
		speed_ -= decelerationRate_;
	}
}

void PaperAirplane::Move()
{

	//行列更新
	worldtransform_.translation_ += velocity_;
	worldtransform_.matWorld_ = affine_->World(affine_->Scale(affine_->Scale_), affine_->Rot(affine_->RotX(worldtransform_.rotation_.x), affine_->RotY(worldtransform_.rotation_.y), affine_->RotZ(worldtransform_.rotation_.z)), affine_->Trans(worldtransform_.translation_));
	worldtransform_.TransferMatrix();

}

void PaperAirplane::Set(float windPower,Vector3 fanTrans)
{
	//速度,落下スピード,減速をセット

	//風速をそのままスピードに代入
	speed_ = (windPower / 10) + 0.01;//0.1～1.1の範囲

	//紙飛行機と扇風機の座標の差が落下スピード
	//if文でマイナスにならないようにする
	if ((fanTrans.x - worldtransform_.translation_.x) > 0) {
		fallSpeed_ = (fanTrans.x - worldtransform_.translation_.x) / 10;
	}
	else {
		fallSpeed_ = (worldtransform_.translation_.x- fanTrans.x) / 10;
	}

	if (fallSpeed_ <= 0.02) {
		fallSpeed_ = 0.02;
	}

	////減速率を計算,角度が0(まっすぐ)に近いほど減速率は少ない
	//if (worldtransform_.rotation_.y < PI) {
	//	decelerationRate_ = worldtransform_.rotation_.y / 100;
	//}
	//else {
	//	decelerationRate_ = (PI - worldtransform_.rotation_.y) / 100;
	//}

	//減速率を計算,角度が0(まっすぐ)に近いほど減速率は少ない
	if (worldtransform_.rotation_.y < PI) {
		decelerationRate_ = (worldtransform_.rotation_.y);
	}
	else {
		decelerationRate_ = (worldtransform_.rotation_.y - PI);

		if (decelerationRate_ < (PI / 2)) {
			decelerationRate_ = (PI - decelerationRate_);
		}
		else {
			decelerationRate_ = (PI - decelerationRate_);
			//decelerationRate_ += (decelerationRate_ + decelerationRate_);
		}

	}

	decelerationRate_ = decelerationRate_ / 100;
}

void PaperAirplane::LandingJudge()
{

	if (worldtransform_.translation_.y <= endY) {
		isLanding_ = 1;
		move_ = 0;
	}

}

void PaperAirplane::Reset()
{
	//0 停止 1 移動
	move_ = 0;
	isLanding_ = 0;

}

