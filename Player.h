#pragma once
#include "Input.h"
#include "Vector3.h"
#include <list>
#include <Model.h>
#include<WorldTransform.h>
#include<Input.h>


class Player {
public:
	// 初期化
	void Initialize(Model* model_, uint32_t textureHandle);
	// 更新
	void Update();
	// 描画
	void Draw(const ViewProjection& viewProjection_);

	// キーボード入力
	Input* input_ = nullptr;

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};