#include"Player.h"


void Player::Initialize(Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm, 
    uint32_t textureHandle) {
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
	
	textureHandle_ = textureHandle;
	//ワールド返還の初期化
	worldTransform_.Initialize();
	// Transration
	worldTransform_.translation_ = {0, -2, 0};
	// Scale
	worldTransform_.scale_ = {1, 1, 1};
	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
}

void Player::Update() {
		
	////キャラクターの移動ベクトル
	//Vector3 move = {0, 0, 0};
	////キャラクターの移動速さ
	//const float kCharacterSpeed = 0.2f;
	////おした方向で移動ベクトルを変更(左右)
	//if (input_->PushKey(DIK_LEFT)) {
	//	move.x -= kCharacterSpeed;
	//} else if (input_->PushKey(DIK_RIGHT)) {
	//	move.x += kCharacterSpeed;
	//}
	//	// おした方向で移動ベクトルを変更(奥と手前)
	//if (input_->PushKey(DIK_UP)) {
	//	move.z += kCharacterSpeed;
	//} else if (input_->PushKey(DIK_DOWN)) {
	//	move.z -= kCharacterSpeed;
	//}
	////座標移動(ベクトルの加算)
	//worldTransform_.translation_.x += move.x;
	//worldTransform_.translation_.z += move.z;

	
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
		MakeAffineMatrix(
		    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
		worldTransform_.UpdateMatrix();
		// Y軸周り角度
		worldTransform_.rotation_.y = std::atan2(move.x, move.z);
	}
}

void Player::Draw(const ViewProjection& ViewProjection) {
	// 3Dモデルを描画
	modelFighterBody_->Draw(worldTransform_, ViewProjection);
	modelFighterHead_->Draw(worldTransform_, ViewProjection);
	modelFighterL_arm_->Draw(worldTransform_, ViewProjection);
	modelFighterR_arm_->Draw(worldTransform_, ViewProjection);

}

void Player::InitializeFloatingGimmick() { 
	floatingParameter_ = 0.0f; 
}

void Player::UpdateFloatingGimmick() {
//浮遊移動のサイクル<frame>
	//uint16_t frame = 3;
	//const uint16_t cycle = frame;
	////1フレームでのパラメータ加算値
	//const float step = 2.0f * M_PI / cycle;
	////パラメータを1ステップ分加算
	//floatingParameter_ += step;
	////2πを超えたら0に戻す
	//floatingParameter_ = std::fmod(floatingParameter_, 2.0f * M_PI);
	////浮遊の振幅<m>
	//const float m = 3;
	////浮遊を座標に反映
	//worldTransformBody_.translation_.y = std::sin(floatingParameter_) * m;


	//数値調整
	//ImGui::Begin("Player");

}
