#pragma once
#include"Model.h"
#include"Collider.h"
#include"MyMath.h"

class CollisionManager {
public:

	//������
	void Initilize();

	//���Z�b�g
	void Reset();

	/// <summary>
	/// �R���C�_�[2�̏Փ˔���Ɖ���
	/// </summary>
	/// <param name="colliderA"></param>
	/// <param name="colliderB"></param>
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);

private:
	//�R���C�_�[
	std::list<Collider*> colliders_;

	// �f�o�b�N�\���p���f��
	std::unique_ptr<Model> debugModel_;
};
