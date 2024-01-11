#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Scene.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
class OverScene {

public:
	OverScene();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~OverScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	///< summary>
	/// 描画
	/// </summary>
	void Draw();

	bool IsSceneEnd() { return isSceneEnd_; }
	Scene::SceneType NextScene() { return Scene::SceneType::kGamePlay; }

private: // メンバ変数
	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	bool isSceneEnd_ = false;

	uint32_t soundDataHandle_ = 0;

	// 画像
	uint32_t textureHandle_ = 0;
	Sprite* sprite_ = nullptr;
};