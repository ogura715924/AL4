#include "CollisionManager.h"

void CollisionManager::Initilize() {

	debugModel_.reset(Model::CreateFromOBJ("ico", true));

}

void CollisionManager::Reset() {
//���X�g������ۂɂ���
	colliders_.clear();
}

void CollisionManager::CheckCollisionPair(Collider* colliderA, Collider* colliderB) {
	Vector3 coordinateA = colliderA->GetCenterPosition();
	//�R���C�_�[B�̍��W���擾
	Vector3 coordinateB = colliderB->GetCenterPosition();
	//���W�̍����x�N�g��
	Vector3 subtract = SubtractionV3(coordinateB - coordinateA);
	//���WA��B�̋��������߂�
	float distance=
}
