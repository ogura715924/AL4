#pragma once
#include "BaseCharacter.h"
#include <cassert>
#include"MyMath.h"

class Enemy:public BaseCharacter {
public:
	void Initialize(const std::vector<Model*>& models)override;
	void Update()override;
	void Draw(const ViewProjection& viewProjection_) override;

	// 親となるワールドトランスフォーム
	void SetParent(const WorldTransform* parent);
	private:
	enum { kModelIndexBody,
		kModelIndexL_arm,
		kModelIndexR_arm };

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
};
