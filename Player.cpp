#include"Player.h"
#include "WorldTransform.h"
#include <assert.h>
#include <cassert>
#include <imgui.h>
#include <math.h>

#define _USE_MATH_DEFINES




void Player::Initialize(Model* model, uint32_t textureHandle) {
	// NULLポインタチェック
	assert(model);
	model_ = model;
	
	//引数として受け取ったデータをメンバ関数に記録(代入)する
	model_ = model;
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
		
	worldTransform_.UpdateMatrix(); 

	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	//キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;
	//おした方向で移動ベクトルを変更(左右)
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
		// おした方向で移動ベクトルを変更(奥と手前)
	if (input_->PushKey(DIK_UP)) {
		move.z += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.z -= kCharacterSpeed;
	}
	//座標移動(ベクトルの加算)
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.z += move.z;

}

void Player::Draw(const ViewProjection& ViewProjection) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, ViewProjection);

}