#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include<memory>
#include <Player.h>
#include <Skydome.h>
#include <Ground.h>
#include <DebugCamera.h>
#include <FollowCamera.h>
#include <Enemy.h>


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0;
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;

	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	//追従カメラ
	FollowCamera* followCamera_ = nullptr;

	//自キャラ
	std::unique_ptr<Model> modelFighterBody_;
	std::unique_ptr<Model> modelFighterHead_;
	std::unique_ptr<Model> modelFighterL_arm_;
	std::unique_ptr<Model> modelFighterR_arm_;
	//std::unique_ptr<Model> modelPlayer_;
	std::unique_ptr <Player> player_;

	//武器
	std::unique_ptr<Model> modelHammer;

	//敵キャラ
	std::unique_ptr<Model> modelEnemyBody_;
	std::unique_ptr<Model> modelEnemyL_arm_;
	std::unique_ptr<Model> modelEnemyR_arm_;
	std::unique_ptr<Enemy> enemy_;

	//天球
	std::unique_ptr<Model> modelSkydome_;
	std::unique_ptr<Skydome> skydome_;

	//床
	std::unique_ptr<Model> modelGround_;
	std::unique_ptr<Ground> ground_;
};
