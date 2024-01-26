#include "Player.h"

void (Player::*Player::pBehaviorUpdateTable[])() = {
    &Player::BehaviorRootUpdate,
    &Player::BehaviorAttackUpdate,
};

void (Player::*Player::pBehaviorInitTable[])() = {
    &Player::BehaviorRootInitialaize,
    &Player::BehaviorAttackInitialize,
};

void Player::Initialize(const std::vector<Model*>& models) {
	// 基底クラスの初期化
	BaseCharacter::Initialize(models);
	// NULLポインタチェック
	//assert(models.size());

	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();
	// ワールド変換の初期化武器
	worldTransformHammer_.Initialize();

	// 基底クラスのベースキャラクターworldTransformを親子関係のベースとする
	// ボディの親をにする
	worldTransformBody_.parent_ = &worldTransform_;
	// ヘッドの親をボディにする
	worldTransformHead_.parent_ = &worldTransformBody_;
	// Lの腕の親をボディにする
	worldTransformL_arm_.parent_ = &worldTransformBody_;
	// Rの腕の親をボディにする
	worldTransformR_arm_.parent_ = &worldTransformBody_;
	// 武器の親をLの腕にする
	worldTransformHammer_.parent_ = &worldTransformL_arm_;

	// Transration
	worldTransform_.translation_ = {0, -1, 0};
	worldTransformBody_.translation_ = {0, 0, 0};
	worldTransformHead_.translation_ = {0, 0, 0};
	worldTransformL_arm_.translation_ = {0, 0, 0};
	worldTransformR_arm_.translation_ = {0, 0, 0};
	// 武器
	worldTransformHammer_.translation_ = {0, 0, 0};

	// Scale
	worldTransform_.scale_ = {1, 1, 1};
	worldTransformBody_.scale_ = {1, 1, 1};
	worldTransformHead_.scale_ = {1, 1, 1};
	worldTransformL_arm_.scale_ = {1, 1, 1};
	worldTransformR_arm_.scale_ = {1, 1, 1};
	// 武器
	worldTransformHammer_.scale_ = {1, 1, 1};

	// rotation
	worldTransform_.rotation_ = {0, 0,0 };
	// 武器
	worldTransformHammer_.rotation_ = {0, 0, 0};

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
}

void Player::Update() {

	// 基底クラス
	BaseCharacter::Update();

	// リクエストがあったら初期化と次の行動に移行
	if (behaviorRequest_) {
		behavior_ = behaviorRequest_.value();
		(this->*pBehaviorInitTable[static_cast<size_t>(behavior_)])();
		// ふるまいリクエストリセット
		behaviorRequest_ = std::nullopt;
	}
	(this->*pBehaviorUpdateTable[static_cast<size_t>(behavior_)])();

	//ImGui::Begin("window");
	//ImGui::DragFloat3("worldTransformL_arm_ transform", &worldTransformL_arm_.translation_.x);
	//ImGui::DragFloat3("worldTransformL_arm_ rotation", &worldTransformL_arm_.rotation_.x);
	//ImGui::DragFloat3("worldTransformHummer_ transform", &worldTransformHammer_.translation_.x);
	//ImGui::DragFloat3("worldTransformHummer_ rotation", &worldTransformHammer_.rotation_.x);
	//ImGui::End();

	// 行列を更新
	// 本体
	worldTransform_.UpdateMatrix();
	// 体
	worldTransformBody_.UpdateMatrix();
	// 頭
	worldTransformHead_.UpdateMatrix();
	// Lうで
	worldTransformL_arm_.UpdateMatrix();
	// Rうで
	worldTransformR_arm_.UpdateMatrix();
	// 武器
	worldTransformHammer_.UpdateMatrix();
}

void Player::Draw(const ViewProjection& ViewProjection) {
	// 3Dモデルを描画
	models_[kModelIndexBody]->Draw(worldTransformBody_, ViewProjection);
	models_[kModelIndexHead]->Draw(worldTransformHead_, ViewProjection);
	models_[kModelIndexL_arm]->Draw(worldTransformL_arm_, ViewProjection);
	models_[kModelIndexR_arm]->Draw(worldTransformR_arm_, ViewProjection);
	// 武器
		models_[kModelIndexHammer]->Draw(worldTransformHammer_, ViewProjection);
}

void Player::InitializeFloatingGimmick() { floatingParameter_ = 0.0f; }

void Player::UpdateFloatingGimmick() {
	// 浮遊移動のサイクル<frame>
	uint16_t frame = 180;
	// 1フレームでのパラメータ加算値
	const float step = (float)(2.0f * M_PI / frame);
	// パラメータを1ステップ分加算
	floatingParameter_ += step;
	// 2πを超えたら0に戻す
	floatingParameter_ = (float)std::fmod(floatingParameter_, 2.0 * M_PI);
	// 浮遊の振幅<m>
	const float SwingWidth = 0.5;
	// 浮遊を座標に反映
	// 体上下
	worldTransformBody_.translation_.y = std::sin(floatingParameter_) * SwingWidth;
	// 腕振り
	worldTransformL_arm_.rotation_.x = std::sin(floatingParameter_) * SwingWidth;
	worldTransformR_arm_.rotation_.x = std::sin(floatingParameter_) * SwingWidth;
}

void Player::BehaviorRootInitialaize() {
	worldTransformL_arm_.translation_ = {0, 0, 0};
	worldTransformHammer_.translation_ = {0, 0, 0};

	worldTransformL_arm_.rotation_ = {0, 0, 0};
	worldTransformR_arm_.rotation_ = {0, 0, 0};
	// 武器
	worldTransformHammer_.rotation_ = {0, 0, 0};
}

void Player::BehaviorRootUpdate() {
	// 浮遊ギミック
	UpdateFloatingGimmick();

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// 速さ
		const float speed = 0.5f;
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

		// Y軸周り角度
		worldTransform_.rotation_.y = std::atan2(move.x, move.z);

		// Aボタンの判定
		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_A) {
			// Attack挙動に遷移
			//behavior_ = Behavior::kAttack;
			behaviorRequest_ = Behavior::kAttack;
		}
	}
}

void Player::BehaviorAttackInitialize() { 
	attack_.time = 20;

	worldTransformL_arm_.translation_ = {4, 2, 0};
	worldTransformHammer_.translation_ = {1, 2, 0};

	worldTransformL_arm_.rotation_ = {0, 0, 9};
	worldTransformHammer_.rotation_ = {5, 0, -1};
}


void Player::BehaviorAttackUpdate() {

	//
	attack_.time--;
	if (attack_.time <= 0) {
		// behavior_ = Behavior::kRoot;
		behaviorRequest_ = Behavior::kRoot;
	}
		
	// アニメーション
	if (attack_.time <= 15) {
		worldTransformL_arm_.translation_ = {4, 1, 1};
		worldTransformL_arm_.rotation_ = {-1, 0, 9};

		worldTransformHammer_.translation_ = {1, 2, 0};
		worldTransformHammer_.rotation_ = {2, 0, -1};
	}

	if (attack_.time <= 10) {
		worldTransformL_arm_.translation_ = {2, 2, 0};
		worldTransformL_arm_.rotation_ = {2, -2, 1};

		worldTransformHammer_.translation_ = {1, 2, 0};
		worldTransformHammer_.rotation_ = {0, 0, -1};
	}

	if (attack_.time <=5) {
		worldTransformL_arm_.translation_ = {2, -1, 0};
		worldTransformL_arm_.rotation_ = {-8, -1, 8};

		worldTransformHammer_.translation_ = {1, 2, 0};
		worldTransformHammer_.rotation_ = {0, 0, -1};
	}
	
}
void Player::HammerOnCollision() {  }

// 親子関係を結ぶ
void Player::SetParent(const WorldTransform* parent) {
	worldTransform_.parent_ = parent;
}

float Player::EaseInBack(float x) { return x; }
