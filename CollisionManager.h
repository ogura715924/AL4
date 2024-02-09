#pragma once
#include"Model.h"
#include"Collider.h"
#include"MyMath.h"
#include <Player.h>

class CollisionManager {
public:

	//初期化
	void Initilize();

	//リセット
	void Reset();

	//
	void AddCollider(Collider* collider);

	//ワールドトランスフォームの更新
	void UpdateTransform();
	// 描画
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// コライダー2つの衝突判定と応答
	/// </summary>
	/// <param name="colliderA"></param>
	/// <param name="colliderB"></param>
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);

	//全ての当たり判定のチェック
	void CheckAllCollisions();

private:
	//コライダー
	std::list<Collider*> colliders_;

	// デバック表示用モデル
	std::unique_ptr<Model> debugModel_;

};
