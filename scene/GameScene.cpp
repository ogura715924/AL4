#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <ImGuiManager.h>

GameScene::GameScene() {}

GameScene::~GameScene() {
	// デストラクタ
	for (EnemyBullet* bullet : enemyBullets_) {
		delete bullet;
	}
	enemyBullets_.clear();
}

void GameScene::Initialize() {
//	debugModel_.reset(Model::CreateFromOBJ("ico", true));

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//衝突マネージャの生成
	collisionManager_ = std::make_unique<CollisionManager>();
	//デバッグ用モデル
	collisionManager_->Initilize();

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
	modelHammerAttack.reset(Model::CreateFromOBJ("ico", true));

	// 自キャラモデル
	std::vector<Model*> playerModels = {
		modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(), modelFighterR_arm_.get(),
	                                    modelHammer.get(),modelHammerAttack.get()};

	// 自キャラの生成
	player_ = std::make_unique<Player>();
	// 自キャラの初期化
	player_->Initialize(playerModels);
	//player_->Initialize(modelFighterBody_.get(), modelFighterHead_.get(),
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


	uint32_t fadeTexHandle = TextureManager::Load("tttl.png");
	uint32_t fadeTexHandlec = TextureManager::Load("gacl.png");
	uint32_t fadeTexHandleo = TextureManager::Load("gaov.png");
	sprite3_ = Sprite::Create(fadeTexHandle, {0, 0});
	fadeColor_ = {
	    1.0f,
	    1.0f,
	    1.0f,
	    1.0f,
	};
	spritec_ = Sprite::Create(fadeTexHandlec, {0, 0});
	fadeColorc_ = {
	    1.0f,
	    1.0f,
	    1.0f,
		0.0f
	};
	spriteo_ = Sprite::Create(fadeTexHandleo, {0, 0});
	fadeColoro_ = {
	    1.0f,
	    1.0f,
	    1.0f, 0.0f
	};
	// シーン
	isSceneEndO_ = false;
	isSceneEndC_ = false;

	atack = false;
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

	//でバック表示用にワールドトランスフォームを更新
	collisionManager_->UpdateTransform();

	//当たり判定
	CheckAllCollisions();

	

	/*if (enemy_->IsSceneEndCler() == true) {
		isSceneEndC_ = true;
	}*/

	fadeColor_.w -= 0.05f;
	sprite3_->SetColor(fadeColor_);
	
	
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
	//当たり判定の表示
	//collisionManager_->Draw(followCamera_->GetViewProjection());

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	sprite3_->Draw();

	if (player_->IsSceneEndOver() == true) {
		fadeColoro_.w += 0.05f;
		spriteo_->SetColor(fadeColoro_);
		if (fadeColoro_.w >= 0.05f) {
			spriteo_->Draw();
			if (fadeColoro_.w >= 0.95f) {
				isSceneEndO_ = true;
			}
		}
	}

	if (atack == true) {
		fadeColorc_.w += 0.05f;
		spritec_->SetColor(fadeColorc_);
	}
	if (fadeColorc_.w >= 0.05f) {
		spritec_->Draw();
		if (fadeColorc_.w >= 0.95f) {
			isSceneEndC_ = true;
		}
	}
	
	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}


void GameScene::CheckAllCollisions() {

	//衝突マネージャのリセット
	collisionManager_->Reset();

	//コライダーをリストの登録
	collisionManager_->AddCollider(player_.get());
	//敵単体について
	collisionManager_->AddCollider(enemy_.get());
	//衝突判定と応答
	collisionManager_->CheckAllCollisions();


	// 判定対象AとBの座標
	Vector3 PosA, PosB;
	Vector3 RadiusA, RadiusB;
	float PositionMeasure;
	float RadiusMeasure;


	#pragma region ハンマーと敵キャラの当たり判定

	if (player_->IsAttack() == true) {

		// 敵キャラの座標
		PosA = enemy_->GetCenterPosition();
		RadiusA = enemy_->GetRadius();
		// 敵キャラとハンマー全ての当たり判定
		// ハンマーの座標
		PosB = player_->GetHammerWorldPosition();
		RadiusB = player_->GetHammerRadius();
		// 座標AとBの距離を求める
		PositionMeasure = (PosB.x - PosA.x) * (PosB.x - PosA.x) +
		                  (PosB.y - PosA.y) * (PosB.y - PosA.y) +
		                  (PosB.z - PosA.z) * (PosB.z - PosA.z);
		RadiusMeasure =  (float)(Dot(RadiusA, RadiusB));
		// 弾と弾の交差判定
		if (PositionMeasure <= RadiusMeasure) {
			atack = true;
			Vector3 speed{0, 0, 0};
			enemy_->SetSpeed(speed);
			// フェード
		}
		
		
	}
	
#pragma endregion
}