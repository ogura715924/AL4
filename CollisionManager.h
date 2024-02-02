#pragma once
#include"Model.h"
#include"Collider.h"
#include"MyMath.h"

class CollisionManager {
public:

	//初期化
	void Initilize();

	//リセット
	void Reset();

	/// <summary>
	/// コライダー2つの衝突判定と応答
	/// </summary>
	/// <param name="colliderA"></param>
	/// <param name="colliderB"></param>
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);

private:
	//コライダー
	std::list<Collider*> colliders_;

	// デバック表示用モデル
	std::unique_ptr<Model> debugModel_;
};
