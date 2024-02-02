#pragma once
#include "WorldTransform.h"

class Collider {
public:
	// 初期化
	void Initilize();

	//半径を取得
	float GetRadius() { return radius; };
	//半径を設定
	float SetRadius(int value) { radius = value; };

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
	float radius = 1.5f;
};