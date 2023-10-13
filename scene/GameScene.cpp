#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	//デストラクタ
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//ファイル名を指定してテクスチャを読み込む
	//自機
	textureHandle_ = TextureManager::Load("kaeru.png");
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

	viewProjection_.translation_={0,0,0};
	viewProjection_.UpdateMatrix();
	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

#pragma region //モデルとクラスの実態生成、初期化
	// モデルをメンバ変数に持っているクラスはモデルとワンセットでGameSceneに書く
	//3Dモデルの生成
	modelPlayer_.reset(Model::CreateFromOBJ("player",true));
	//自キャラの生成
	player_ = std::make_unique<Player>();
   //自キャラの初期化
	player_->Initialize(modelPlayer_.get(), textureHandle_);

	//天球(モデル)の生成
	modelSkydome_.reset(Model::CreateFromOBJ("skydome", true));
	// 天球(クラス)の生成
	skydome_ = std::make_unique<Skydome>();
	//天球の初期化
	skydome_->Initialize(modelSkydome_.get() );

	// 床の(モデル)生成
	modelGround_.reset(Model::CreateFromOBJ("ground", true));
	//床の(クラス)生成
	ground_ = std::make_unique<Ground>();
	//床の初期化
	ground_->Initialize(modelGround_.get());


#pragma endregion

}

void GameScene::Update() { 
	//プレイヤーの更新
	player_->Update();
	//天球の更新
	skydome_->Update();
	//床の更新
	ground_->Update();

	// デバッグカメラの更新
	debugCamera_->Update();
}

void GameScene::Draw() {

	
	
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	 
	// 自キャラの描画
	player_->Draw(debugCamera_->GetViewProjection());

	//天球の描画
	skydome_->Draw(debugCamera_->GetViewProjection());
	//床の更新
	ground_->Draw(debugCamera_->GetViewProjection());


	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
