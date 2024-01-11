#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	// デストラクタ
	for (EnemyBullet* bullet : enemyBullets_) {
		delete bullet;
	}
	enemyBullets_.clear();
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	// 自機
	// textureHandle_ = TextureManager::Load("kaeru.png");
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	viewProjection_.translation_ = {0, 0, 0};
	viewProjection_.UpdateMatrix();

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

#pragma region // モデルとクラスの実態生成、初期化
	// モデルをメンバ変数に持っているクラスはモデルとワンセットでGameSceneに書く
	// 自キャラの3Dモデルの生成
	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body",true));
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head", true));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("float_L_arm",true));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("float_R_arm",true));
	 //modelPlayer_.reset(Model::CreateFromOBJ("player",true));
	//武器
	modelHammer.reset(Model::CreateFromOBJ("Hammer",true));

	// 自キャラモデル
	std::vector<Model*> playerModels = {
		modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),
		modelFighterR_arm_.get(), modelHammer.get()};

	// 自キャラの生成
	player_ = std::make_unique<Player>();
	// 自キャラの初期化
	player_->Initialize(playerModels);
	// player_->Initialize(modelFighterBody_.get(), modelFighterHead_.get(),
	// modelFighterL_arm_.get(), modelFighterR_arm_.get(), textureHandle_);

	// 敵キャラの3Dモデルの生成
	modelEnemyBody_.reset(Model::CreateFromOBJ("needle_Body", true));
	modelEnemyL_arm_.reset(Model::CreateFromOBJ("needle_L_arm", true));
	modelEnemyR_arm_.reset(Model::CreateFromOBJ("needle_R_arm", true));

	// 敵キャラモデル
	std::vector<Model*> EnemyModels = {
	    modelEnemyBody_.get(), modelEnemyL_arm_.get(),
	    modelEnemyR_arm_.get()};

	// 敵キャラの生成
	enemy_ = std::make_unique<Enemy>();
	// 敵キャラの初期化
	enemy_->Initialize(EnemyModels);
	
	// 天球(モデル)の生成
	modelSkydome_.reset(Model::CreateFromOBJ("skydome", true));
	// 天球(クラス)の生成
	skydome_ = std::make_unique<Skydome>();
	// 天球の初期化
	skydome_->Initialize(modelSkydome_.get());

	// 床の(モデル)生成
	modelGround_.reset(Model::CreateFromOBJ("ground", true));
	// 床の(クラス)生成
	ground_ = std::make_unique<Ground>();
	// 床の初期化
	ground_->Initialize(modelGround_.get());

	// 追従カメラの生成
	followCamera_ = new FollowCamera;
	// 初期化関数呼び出し
	followCamera_->Initialaze();
	// 自キャラのワールドトランスフォームを追従カメラにセット
	followCamera_->SetTarget(&player_->GetWorldTransform());
#pragma endregion
}

void GameScene::Update() {
	// プレイヤーの更新
	player_->Update();
	//敵の更新
	enemy_->Update();
	// 天球の更新
	skydome_->Update();
	// 床の更新
	ground_->Update();

	// デバッグカメラの更新
	debugCamera_->Update();
	// 追従カメラの更新
	followCamera_->Update();
	viewProjection_.matView = followCamera_->GetViewProjection().matView;
	viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
	viewProjection_.TransferMatrix();
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
	// //デバックカメラ
	// player_->Draw(debugCamera_->GetViewProjection());デバッグカメラ
	// 追従カメラ
	player_->Draw(followCamera_->GetViewProjection());
	//敵キャラ
	enemy_->Draw(followCamera_->GetViewProjection());
	// 天球の描画
	// skydome_->Draw(debugCamera_->GetViewProjection());
	skydome_->Draw(followCamera_->GetViewProjection());
	// 床の更新
	// ground_->Draw(debugCamera_->GetViewProjection());
	ground_->Draw(followCamera_->GetViewProjection());
	// 敵弾
	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Draw(viewProjection_);
	}

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


void GameScene::CheckAllCollisions() {

	// 判定対象AとBの座標
	Vector3 PosA, PosB;
	Vector3 RadiusA, RadiusB;
	float PositionMeasure;
	int RadiusMeasure;

#pragma region ハンマーと敵キャラの当たり判定

	// 敵キャラの座標
	PosA = enemy_->GetWorldPosition();
	RadiusA = enemy_->GetRadius();
	// 敵キャラとハンマー全ての当たり判定
		// ハンマーの座標
		PosB = player_->GetHummerWorldPosition();
		RadiusB = player_->GetHummerRadius();
		// 座標AとBの距離を求める
		PositionMeasure = (PosB.x - PosA.x) * (PosB.x - PosA.x) +
		                  (PosB.y - PosA.y) * (PosB.y - PosA.y) +
		                  (PosB.z - PosA.z) * (PosB.z - PosA.z);
		RadiusMeasure = (int)(Dot(RadiusA, RadiusB)) * (int)(Dot(RadiusA, RadiusB));
		// 弾と弾の交差判定
		if (PositionMeasure <= RadiusMeasure) {
			
		ClearScene();
		}

#pragma endregion


#pragma region 自キャラと敵キャラの当たり判定

	// 自キャラの座標
	PosA = player_->GetWorldPosition();
	RadiusA = player_->GetRadius();
	// 自キャラと敵キャラ全ての当たり判定
	// 敵キャラの座標
	PosB = enemy_->GetWorldPosition();
	RadiusB = enemy_->GetRadius();
	// 座標AとBの距離を求める
	PositionMeasure = (PosB.x - PosA.x) * (PosB.x - PosA.x) +
	                  (PosB.y - PosA.y) * (PosB.y - PosA.y) + (PosB.z - PosA.z) * (PosB.z - PosA.z);
	RadiusMeasure = (int)(Dot(RadiusA, RadiusB)) * (int)(Dot(RadiusA, RadiusB));
	// 弾と弾の交差判定
	if (PositionMeasure <= RadiusMeasure) {
		// 自キャラの衝突時コールバックを呼び出す
		//player_->OnCollision();
		// 敵キャラの衝突時コールバックを呼び出す
		//enemy_->OnCollision();
		OverScene();
	}
#pragma endregion
}