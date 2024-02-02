#pragma once
#include "WorldTransform.h"

class Collider {
public:
	// ������
	void Initilize();

	//���a���擾
	float GetRadius() { return radius; };
	//���a��ݒ�
	float SetRadius(int value) { radius = value; };

	public:
	//�Փˎ��ɌĂ΂��֐�
	    virtual void OnCollisiom() {}
		//���S���W���擾
	    virtual Vector3 GetCenterPosition() const = 0;
	    virtual ~Collider() = default;

	private:
	// ���[���h�g�����X�t�H�[��
	WorldTransform worldTransform_;

	//�Փ˔��a
	float radius = 1.5f;
};