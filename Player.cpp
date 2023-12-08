#include"Player.h"


void Player::Initialize(
    const std::vector<Model*>& models) {
	//基底クラスの初期化
	BaseCharacter::Initialize(models);
	// NULLポインタチェック
	assert(modelBody);
	assert(modelHead);
	assert(modelL_arm);
	assert(modelR_arm);

	// 引数として受け取ったデータをメンバ関数に記録(代入)する
	modelFighterBody_ = modelBody;
	modelFighterHead_ = modelHead;
	modelFighterL_arm_ = modelL_arm;
	modelFighterR_arm_ = modelR_arm;
	
	//textureHandle_ = textureHandle;
	//ワールド返還の初期化
	worldTransform_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();

	//ボディの親をにする
	worldTransformBody_.parent_ = &worldTransform_;
	//ヘッドの親をボディにする
	worldTransformHead_.parent_ = &worldTransformBody_;
	//Lの腕の親をボディにする
	worldTransformL_arm_.parent_ = &worldTransformBody_;
	//Rの腕の親をボディにする
	worldTransformR_arm_.parent_ = &worldTransformBody_;

	// Transration
	worldTransform_.translation_ = {0, -2, 0};
	worldTransformBody_.translation_ = {0, -1, 0};
	worldTransformHead_.translation_ = {0, 1, 0};
	worldTransformL_arm_.translation_ = {-1, 1, 0};
	worldTransformR_arm_.translation_ = {1, 1, 0};
	// Scale
	worldTransform_.scale_ = {1, 1, 1};
	worldTransformBody_.scale_ = {1, 1, 1};
	worldTransformHead_.scale_ = {1, 1, 1};
	worldTransformL_arm_.scale_ = {1, 1, 1};
	worldTransformR_arm_.scale_ = {1, 1, 1};
	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
}

void Player::Update() {
	//浮遊ギミック
	UpdateFloatingGimmick();
	
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// 速さ
		const float speed = 0.3f;
		// 移動量
		Vector3 move = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX * speed, 0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX * speed};
		// 移動量に速さを反映
		move = Multiply(speed, Normalize(move));
		// 移動ベクトルをカメラの角度だけ回転する
		Vector3 offset = TransformNormal(offset, worldTransform_.matWorld_);
		// 移動
		worldTransform_.translation_.x += move.x;
		worldTransform_.translation_.z += move.z;

		// 行列を更新
		//本体
		MakeAffineMatrix(
		    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
		worldTransform_.UpdateMatrix();
		//体
		MakeAffineMatrix(
		    worldTransformBody_.scale_, worldTransformBody_.rotation_, worldTransformBody_.translation_);
		worldTransformBody_.UpdateMatrix();
		//頭
		MakeAffineMatrix(
		    worldTransformHead_.scale_, worldTransformHead_.rotation_, worldTransformHead_.translation_);
		worldTransformHead_.UpdateMatrix();
		//Lうで
		MakeAffineMatrix(
		    worldTransformL_arm_.scale_, worldTransformL_arm_.rotation_, worldTransformL_arm_.translation_);
		worldTransformL_arm_.UpdateMatrix();
		//Rうで
		MakeAffineMatrix(
		    worldTransformR_arm_.scale_, worldTransformR_arm_.rotation_, worldTransformR_arm_.translation_);
		worldTransformR_arm_.UpdateMatrix();

		// Y軸周り角度
		worldTransform_.rotation_.y = std::atan2(move.x, move.z);
	}
}

void Player::Draw(const ViewProjection& ViewProjection) {
	// 3Dモデルを描画
	modelFighterBody_->Draw(worldTransformBody_, ViewProjection);
	modelFighterHead_->Draw(worldTransformHead_, ViewProjection);
	modelFighterL_arm_->Draw(worldTransformL_arm_, ViewProjection);
	modelFighterR_arm_->Draw(worldTransformR_arm_, ViewProjection);

	models_[kModelIndexBody]->Draw(worldTransformBody_, ViewProjection);
}

void Player::InitializeFloatingGimmick() { 
	floatingParameter_ = 0.0f; 
}

void Player::UpdateFloatingGimmick() {
//浮遊移動のサイクル<frame>
	uint16_t frame = 180;
	//1フレームでのパラメータ加算値
	const float step = (float)(2.0f * M_PI / frame);
	//パラメータを1ステップ分加算
	floatingParameter_ += step;
	//2πを超えたら0に戻す
	floatingParameter_ = (float)std::fmod(floatingParameter_, 2.0 * M_PI);
	//浮遊の振幅<m>
	const float SwingWidth = 0.5;
	//浮遊を座標に反映
	//体上下
	worldTransformBody_.translation_.y = std::sin(floatingParameter_) * SwingWidth;
	//腕振り
	worldTransformL_arm_.rotation_.x = std::sin(floatingParameter_) * SwingWidth;
	worldTransformR_arm_.rotation_.x = std::sin(floatingParameter_) * SwingWidth;

	//数値調整
	//ImGui::Begin("Player");
	////ImGui::SliderFloat3("Head Translation", &(worldTransformHead_, SliderMin.x, SliderMax.x));
	//ImGui::SliderInt3("Head Translation", &worldTransformHead_, SliderMin.x, SliderMax.x);

	//ImGui::End();
}

void Player::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}

