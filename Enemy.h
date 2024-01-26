﻿#pragma once
#include "BaseCharacter.h"
#include <cassert>
#include"MyMath.h"
#include "EnemyBullet.h"
#include <Player.h>

class Enemy:public BaseCharacter {
public:
	void Initialize(const std::vector<Model*>& models)override;
	void Update()override;
	void Draw(const ViewProjection& viewProjection_) override;
	// 攻撃
	//void Fire(Model*model_);

	// 衝突を検知したら呼び出されるコールバック関数
	void OnCollision();

	// 弾リストを取得
	const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }
	// 発射間隔
	static const int kFireInterval = 180;

	// 親となるワールドトランスフォーム
	void SetParent(const WorldTransform* parent);

	// setterの利用
	void SetPlayer(Player* player) { player_ = player; }

	// ワールド座標を取得
	Vector3 GetWorldPosition() {

		// ワールド座標を入れる変数
		Vector3 worldPos{};
		worldTransformBody_.matWorld_.m;
		// ワールド行列の平行移動成分を取得(ワールド座標)
		worldPos.x = worldTransformBody_.matWorld_.m[3][0];
		worldPos.y = worldTransformBody_.matWorld_.m[3][1];
		worldPos.z = worldTransformBody_.matWorld_.m[3][2];
		return worldPos;
	}
	// 大きさ取得
	Vector3 GetRadius() { return worldTransformBody_.scale_; }; 

	private:
	enum { kModelIndexBody,
		kModelIndexL_arm,
		kModelIndexR_arm };

	// 行動フェーズ
	enum class Phase {
		Approach, // 接近する
		Leave,    // 離脱する
	};

		//ワールド変換
	WorldTransform worldTransform_;
	    WorldTransform worldTransformBody_;
	WorldTransform worldTransformL_arm_;
	    WorldTransform worldTransformR_arm_;

		// モデル
	    Model* modelFighterBody_ = nullptr;
	    Model* modelFighterL_arm_ = nullptr;
	    Model* modelFighterR_arm_ = nullptr;

		// テクスチャハンドル
	    uint32_t textureHandle_ = 0u;

// フェーズ　
	    Phase phase_;
	    // 弾
	    EnemyBullet* bullet_ = nullptr;
	    // 引っ越した
	    std::list<EnemyBullet*> bullets_;

	    // 発射タイマー
	    int32_t FireTimer = 0;

		// スピード
	    Vector3 Speed = {0.05f, 0.05f, 0};

		// 速度
	    Vector3 velocity_ = {0, 0, 0};

		// 自キャラ
	    Player* player_ = nullptr;

	    // デスフラグ
	    bool isDead_ = false;
};
