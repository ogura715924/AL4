﻿#pragma once
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
	
	// 衝突を検知したら呼び出されるコールバック関数
	void OnCollision();
	// ハンマー
	void HammerOnCollision();

	//親となるワールドトランスフォーム
	void SetParent(const WorldTransform* parent);
	//void SetParentPlayer(const WorldTransform* parent);


	const WorldTransform& GetWorldTransform() { return worldTransform_; }
	//const WorldTransform& GetWorldTransformPlayer() { return worldTransformBody_; }

	// ワールド座標を取得
	Vector3 GetWorldPosition() {

		// ワールド座標を入れる変数
		Vector3 worldPos{};
		worldTransform_.matWorld_.m;
		// ワールド行列の平行移動成分を取得(ワールド座標)
		worldPos.x = worldTransform_.matWorld_.m[3][0];
		worldPos.y = worldTransform_.matWorld_.m[3][1];
		worldPos.z = worldTransform_.matWorld_.m[3][2];
		return worldPos;
	}
	// 大きさ取得
	Vector3 GetRadius() { return worldTransform_.scale_; }; 
	 

	//ハンマー
	// ワールド座標を取得
	Vector3 GetHummerWorldPosition() {

		// ワールド座標を入れる変数
		Vector3 worldPos{};
		worldTransformHummer_.matWorld_.m;
		// ワールド行列の平行移動成分を取得(ワールド座標)
		worldPos.x = worldTransformHummer_.matWorld_.m[3][0];
		worldPos.y = worldTransformHummer_.matWorld_.m[3][1];
		worldPos.z = worldTransformHummer_.matWorld_.m[3][2];
		return worldPos;
	}
	// 大きさ取得
	Vector3 GetHummerRadius() { return worldTransformHummer_.scale_; }; 

	// メンバ関数の追加
	bool IsDead() const { return isDead_; }
	// デスフラグ
	bool isDead_ = false;

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
	Behavior behavior_ = Behavior::kRoot;
	//次の振るまいリクエスト
	std::optional<Behavior> behaviorRequest_ = std::nullopt;

	//攻撃のアニメーション
	Animation attack_;
	float kDegreeToRadian;
float EaseInBack(float x);

	static void (Player::*pBehaviorUpdateTable[])();
static void (Player::*pBehaviorInitTable[])();
};