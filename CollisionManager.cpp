#include "CollisionManager.h"

void CollisionManager::Initilize() {

	//debugModel_.reset(Model::CreateFromOBJ("ico", true));

}

void CollisionManager::Reset() {
//リストを空っぽにする
	colliders_.clear();
}

void CollisionManager::AddCollider(Collider* collider) {
	colliders_.push_back(collider); }

void CollisionManager::UpdateTransform() {
//全てのコライダーについて
	for (Collider* collider : colliders_) {
	//更新
		collider->UpdateWorldTransform();
	}
}
//
//void CollisionManager::Draw(const ViewProjection& viewProjection) {
//	// 全てのコライダーについて
//	for (Collider* collider : colliders_) {
//		//描画
//		//collider->Draw(debugModel_.get(), viewProjection);
//	}
//}

void CollisionManager::CheckCollisionPair(Collider* colliderA, Collider* colliderB) {
	Vector3 coordinateA = colliderA->GetCenterPosition();
	//コライダーBの座標を取得
	Vector3 coordinateB = colliderB->GetCenterPosition();
	//座標の差分ベクトル
	Vector3 subtract = SubtractionV3(coordinateB , coordinateA);
	//座標AとBの距離を求める
	float distance = Length(subtract);
	//半径
	float radiusA = colliderA->GetRadius();
	float radiusB = colliderB->GetRadius();
	float radius = radiusA + radiusB;
	//弾と弾の交差判定
	if (distance <= radius) {
	//コライダーAの衝突時コールバックを呼び出す
		colliderA->OnCollision();
		//コライダーBの衝突時コールバックを呼び出す
		colliderB->OnCollision();
	}
}

void CollisionManager::CheckAllCollisions() {
	// リスト内のペアを総当たり
	std::list<Collider*>::iterator itrA = colliders_.begin();
	for (;itrA != colliders_.end(); ++itrA) {
		Collider* colliderA = *itrA;

		//イテレーターBはイテレーターAの次の要素から回す(重複判定を回避)
		std::list<Collider*>::iterator itrB = itrA;
		itrB++;

		for (; itrB != colliders_.end(); ++itrB) {
			Collider* colliderB = *itrB;

			//ペアの当たり判定
			CheckCollisionPair(colliderA, colliderB);
		}
	}
}