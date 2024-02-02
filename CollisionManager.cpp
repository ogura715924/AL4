#include "CollisionManager.h"

void CollisionManager::Initilize() {

	debugModel_.reset(Model::CreateFromOBJ("ico", true));

}

void CollisionManager::Reset() {
//リストを空っぽにする
	colliders_.clear();
}

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
	float radius = radiusA * radiusB;
	//弾と弾の考査判定
	if (distance <= radius) {
	//コライダーAの衝突時コールバックを呼び出す
		colliderA->OnCollision();
		//コライダーBの衝突時コールバックを呼び出す
		colliderB->OnCollision();
	}
}

void CollisionManager::CheckAllCollisions() {}
