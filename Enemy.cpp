#include "Enemy.h"

void Enemy::Initialize(
    Model* modelBody, Model* modelL_arm, Model* modelR_arm) {
	// NULLポインタチェック
	assert(modelBody);
	assert(modelL_arm);
	assert(modelR_arm);

	// 引数として受け取ったデータをメンバ関数に記録(代入)する
	modelFighterBody_ = modelBody;
	modelFighterL_arm_ = modelL_arm;
	modelFighterR_arm_ = modelR_arm;

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
}

void Enemy::Update() {}

void Enemy::Draw(const ViewProjection& ViewProjection) {
	// 3Dモデルを描画
	modelFighterBody_->Draw(worldTransformBody_, ViewProjection);
	modelFighterL_arm_->Draw(worldTransformL_arm_, ViewProjection);
	modelFighterR_arm_->Draw(worldTransformR_arm_, ViewProjection);
	//GameScene何も書いてない敵のモデルは入ってる
}

void Enemy::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}
