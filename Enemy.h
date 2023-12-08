#pragma once
#include "BaseCharacter.h"
#include <cassert>

class Enemy:public BaseCharacter {
public:
	void Initialize(Model* modelBody, Model* modelL_arm, Model* modelR_arm);
	void Update();
	void Draw(const ViewProjection& ViewProjection);

	// 親となるワールドトランスフォーム
	void SetParent(const WorldTransform* parent);
	private:
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
