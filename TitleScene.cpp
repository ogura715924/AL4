#include "TitleScene.h"


TitleScene::TitleScene() {}

TitleScene::~TitleScene() {
	delete sprite_;
	delete sprite2_;
	delete sprite3_;
};

void TitleScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 画像
	textureHandle_ = TextureManager::Load("tttl.png");
	sprite_ = Sprite::Create(textureHandle_, {0, 0});
	
	textureHandle2_ = TextureManager::Load("tttl2.png");
	sprite2_ = Sprite::Create(textureHandle2_, {0, 0});

	uint32_t fadeTexHandle = TextureManager::Load("tttl.png");
	sprite3_ = Sprite::Create(fadeTexHandle, {0, 0});

	// 音
	soundDataHandle_ = audio_->LoadWave("bgm.wav");
	audio_->PlayWave(soundDataHandle_, true);

	anitime = 0;

	fadeColor_ = {
	    0.0f,
	    0.0f,
	    0.0f,
	    0.0f,
	};
}

void TitleScene::Update() {

	/*fadeColor_.w += 0.05f;
	sprite_->SetColor(fadeColor_);
	sprite2_->SetColor(fadeColor_);
	sprite3_->SetColor(fadeColor_);*/

	isSceneEnd_ = false;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (Input::GetInstance()->GetJoystickStatePrevious(0, prevjoyState)) {
			// Aボタンの判定
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A &&
			    !(prevjoyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
				isSceneEnd_ = true;
			}
		}
	}

	anitime++;
}

void TitleScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	// 画像
	sprite3_->Draw();

	if (anitime >= 0&&anitime<=60) {
		sprite_->Draw();
	}
	if (anitime >= 61 ) {
		sprite2_->Draw();
		if (anitime >= 120) {
			anitime = 0;
		}
	}
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