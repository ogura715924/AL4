#include "FollowCamera.h"
#include "MyMath.h"
#include <math.h>

void FollowCamera::Initialaze() {
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	viewProjection_.farZ = 1000.0f;
	viewProjection_.UpdateMatrix();
}

void FollowCamera::Update() { 
	//カメラ回転
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
	  
		// 回転速度をfloat型の定数で宣言しておく
		const float speed = 0.05f;

		viewProjection_.rotation_.y += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * speed;


	}
	if (target_) {
		// 追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 2.0f, -30.0f};

		// カメラの角度から回転行列を計算する
		Matrix4x4 matRotY = {0};
		matRotY.m[0][0] = cosf(viewProjection_.rotation_.y);
		matRotY.m[1][1] = 1;
		matRotY.m[0][2] = -sinf(viewProjection_.rotation_.y);
		matRotY.m[2][0] = sinf(viewProjection_.rotation_.y);
		matRotY.m[2][2] = cosf(viewProjection_.rotation_.y);
		matRotY.m[3][3] = 1;

		// オフセットをカメラの回転に合わせて回転させる
		offset = TransformNormal(offset, matRotY);

		// 座標をコピーしてオフセット分ずらす
		viewProjection_.translation_ = Add(target_->translation_, offset);

		// ビュー行列の更新と転送
		viewProjection_.UpdateMatrix();
	}
}
