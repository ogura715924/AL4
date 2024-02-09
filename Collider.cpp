#include "Collider.h"

void Collider::Initilize() { worldTransform_.Initialize(); }

void Collider::UpdateWorldTransform() {
	// ワールド座標をワールドトランスフォームに適用
	worldTransform_.translation_ = GetCenterPosition();
	worldTransform_.UpdateMatrix();
}

//void Collider::Draw(Model* model, const ViewProjection& viewProjection) {
//	model->Draw(worldTransform_, viewProjection);
//}
