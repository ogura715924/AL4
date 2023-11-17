#pragma once
#include <ViewProjection.h>
#include<WorldTransform.h>
#include<Input.h>

class FollowCamera {
public:
	void Initialaze();
	void Update();
	void SetTarget(const WorldTransform* target) { target_ = target; }
	
	//ビュープロジェクションの取得
	const ViewProjection& GetViewProjection() { return viewProjection_;	}

	private:
//ビュープロジェクション
	    ViewProjection viewProjection_;
		//追従対象
	    const WorldTransform* target_ = nullptr;
	    // ゲームパッドの状態を得る変数
	    XINPUT_STATE joyState;
};
