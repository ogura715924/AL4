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
#include<optional>
#include"FollowCamera.h"
#include"Xinput.h"

#define _USE_MATH_DEFINES
#include <math.h>

//BaceCharacterの継承
class Player : public BaseCharacter {
public:
	// 初期化
	void Initialize(const std::vector<Model*>& models) override;
	// 更新
	void Update()override;
	// 描画
	void Draw(const ViewProjection& viewProjection_)override;

	//浮遊ギミック初期化
	void InitializeFloatingGimmick();
	//浮遊ギミック更新
	void UpdateFloatingGimmick();
	
	//通常行動初期化
	void BehaviorRootInitialaize();
	//通常行動更新
	void BehaviorRootUpdate();
	// 攻撃行動
	//攻撃行動更新
	void BehaviorAttackUpdate();
	void BehaviorAttackInitialize();
	

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
		kModelIndexR_arm,
		//武器
		kModelIndexHammer
	};

	//振るまい
	enum class Behavior {
		kRoot,//通常状態
		kAttack,//攻撃中
	};

	struct Animation {
		// 時間
		float time;
		// 最高時間
		float kAnimMaxTime;
		// 全部のフレーム
		float kAllFrame;
	};

	// ワールド変換データ
	WorldTransform worldTransform_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
	//武器
	WorldTransform worldTransformHummer_;

	// モデル
	Model* modelFighterBody_ = nullptr;
	Model* modelFighterHead_ = nullptr;
	Model* modelFighterL_arm_ = nullptr;
	Model* modelFighterR_arm_ = nullptr;
	//武器
	Model* modelHammer = nullptr;

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

	//攻撃ギミックの媒介変数
	float floatingParameterAttack_ = 0.0f;

	//振るまい
	Behavior behavior_ = Behavior::kAttack;
	//次の振るまいリクエスト
	std::optional<Behavior> behaviorRequest_ = std::nullopt;

	//攻撃のアニメーション
	Animation attack_;
	float kDegreeToRadian;
float EaseInBack(float x);

	static void (Player::*pBehaviorUpdateTable[])();
static void (Player::*pBehaviorInitTable[])();
};