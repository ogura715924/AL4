#pragma once
#include <Model.h>
#include<Collider.h>

class BaseCharacter :public Collider {
protected:
	//モデルデータ配列
	std::vector<Model*> models_;
	//ワールド返還データ
	WorldTransform worldTransform_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
	//WorldTransform worldTransformHammer_;

	public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="models">モデルデータ配列</param>
	virtual void Initialize(const std::vector<Model*>& models);

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection"></param>
	virtual void Draw(const ViewProjection& viewProjection);

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

	//中心座標を取得
	virtual Vector3 GetCenterPosition() const override;

};
