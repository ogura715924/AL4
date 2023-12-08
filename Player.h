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
#include"BaseCharacter.h"

#define _USE_MATH_DEFINES
#include <math.h>

//BaceCharacterの継承
class Player : public BaseCharacter {
public:
		
	// 初期化
	void Initialize(
	    const std::vector<Model*>& models) override;
	// 更新
	void Update()override;
	// 描画
	void Draw(const ViewProjection& viewProjection_)override;

	//浮遊ギミック初期化
	void InitializeFloatingGimmick();
	//浮遊ギミック更新
	void UpdateFloatingGimmick();

	

	//親となるワールドトランスフォーム
	void SetParent(const WorldTransform* parent);
	//void SetParentPlayer(const WorldTransform* parent);


	const WorldTransform& GetWorldTransform() { return worldTransform_; }
	//const WorldTransform& GetWorldTransformPlayer() { return worldTransformBody_; }

	// キーボード入力
	Input* input_ = nullptr;

private:
	enum  {
		kModelIndexBody,
		kModelIndexHead,
		kModelIndexL_arm,
		kModelIndexR_arm
	};
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
	//デバック
	float inputFloat3[3] = {0, 0, 0};
	Vector3 SliderMin = {-1000, -1000, -1000};
	Vector3 SliderMax = {1000,1000,1000};
};