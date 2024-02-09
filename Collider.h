#pragma once
#include "WorldTransform.h"
#include <Model.h>

class Collider {
public:
	// 初期化
	void Initilize();
	//ワールドトランスフォームの更新
	void UpdateWorldTransform();
	//描画
	//void Draw(Model* model, const ViewProjection& viewProjection);

	//半径を取得
	float GetRadius() { return radius_; };
	//半径を設定
	float SetRadius(float value) { radius_ = value; };

	public:
	//衝突時に呼ばれる関数
	    virtual void OnCollision() {}
		//中心座標を取得
	    virtual Vector3 GetCenterPosition() const = 0;
	    virtual ~Collider() = default;

	private:
	// ワールドトランスフォーム
	WorldTransform worldTransform_;

	//衝突半径
	float radius_ = 1.5f;
};