#pragma once
#include "Input.h"
#include "Vector3.h"
#include <list>
#include <Model.h>
#include<WorldTransform.h>
#include<Input.h>
#include <assert.h>
#include <cassert>
#include <imgui.h>
#include <MyMath.h>

#define _USE_MATH_DEFINES
#include <math.h>

class Player {
public:
	// 初期化
	void Initialize(Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm,
	    uint32_t textureHandle);
	// 更新
	void Update();
	// 描画
	void Draw(const ViewProjection& viewProjection_);

	//浮遊ギミック初期化
	void InitializeFloatingGimmick();
	//浮遊ギミック更新
	void UpdateFloatingGimmick();

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

	//親となるワールドトランスフォーム
	void SetParent(const WorldTransform* parent);
	//void SetParentPlayer(const WorldTransform* parent);


	const WorldTransform& GetWorldTransform() { return worldTransform_; }
	//const WorldTransform& GetWorldTransformPlayer() { return worldTransformBody_; }

	// キーボード入力
	Input* input_ = nullptr;

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
	// モデル
	Model* modelFighterBody_ = nullptr;
	Model* modelFighterHead_ = nullptr;
	Model* modelFighterL_arm_ = nullptr;
	Model* modelFighterR_arm_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;
	//カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;
//浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;
};