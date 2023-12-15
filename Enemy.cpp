﻿#include "Enemy.h"

//Playerと同じようにする
void Enemy::Initialize(const std::vector<Model*>& models) {
	// 基底クラスの初期化
	BaseCharacter::Initialize(models);
	// NULLポインタチェック

	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();

	// ボディの親をにする
	worldTransformBody_.parent_ = &worldTransform_;
	// Lの腕の親をボディにする
	worldTransformL_arm_.parent_ = &worldTransformBody_;
	// Rの腕の親をボディにする
	worldTransformR_arm_.parent_ = &worldTransformBody_;

	// Transration
	worldTransform_.translation_ = {0, -2, 0};
	worldTransformBody_.translation_ = {0, 0, 0};
	worldTransformL_arm_.translation_ = {-1, 1, 0};
	worldTransformR_arm_.translation_ = {1, 1, 0};
	// Scale
	worldTransform_.scale_ = {1, 1, 1};
	worldTransformBody_.scale_ = {1, 1, 1};
	worldTransformL_arm_.scale_ = {1, 1, 1};
	worldTransformR_arm_.scale_ = {1, 1, 1};
}

void Enemy::Update() {
	//移動の速さ
	const float speed = 0.1f;

	worldTransform_.rotation_.y += 0.01f;

//移動量
	Vector3 move{0, 0, speed};
	//回転行列
	Matrix4x4 matRotY = MakeRotateYMatrix(worldTransform_.rotation_.y);
	//移動量を回転に合わせて回転させる
	move = TransformNormal(move, matRotY);
	//移動
	Add( worldTransform_.translation_,  move);


	// 行列を更新
	// 本体
	worldTransform_.UpdateMatrix();
	// 体
	worldTransformBody_.UpdateMatrix();
	// Lうで
	worldTransformL_arm_.UpdateMatrix();
	// Rうで
	worldTransformR_arm_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& ViewProjection) {
	// 3Dモデルを描画
	models_[kModelIndexBody]->Draw(worldTransformBody_, ViewProjection);
	models_[kModelIndexL_arm]->Draw(worldTransformL_arm_, ViewProjection);
	models_[kModelIndexR_arm]->Draw(worldTransformR_arm_, ViewProjection);
	//GameScene何も書いてない敵のモデルは入ってる
}

void Enemy::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}