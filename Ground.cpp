﻿#include "Ground.h"
#include <cassert>

void Ground::Initialize(Model*model)
{
	assert(model);
	model_ = model;

	//初期化
	worldTransform_.Initialize();
	//Transration
	worldTransform_.translation_ = { 0,-3,0 };
	//Scale
	worldTransform_.scale_ = { 50,50,50 };
	//ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
}

void Ground::Update()
{
}

void Ground::Draw(const ViewProjection& viewProjection_) {
	//3Dモデル描画
	model_->Draw(worldTransform_, viewProjection_);
}