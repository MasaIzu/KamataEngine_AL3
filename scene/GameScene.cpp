#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <random>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {
	// delete sprite_;
	delete model_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");
	//スプライトの生成
	// sprite_ = Sprite::Create(textureHandle_, {100, 50});
	// 3Dモデル生成
	model_ = Model::Create();
	//ワールドトランスフォームの初期化
	/*worldTransform_.Initialize();*/
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	//サウンドデータの読み込み
	/*soundDataHandle_ = audio_->LoadWave("se_sad03.wav");*/
	//音声再生
	// audio_->PlayWave(soundDataHandle_);
	// voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);

	//乱数シード生成器
	std::random_device seed_gen;
	//メルセンヌ・ツイスター
	std::mt19937_64 engine(seed_gen());
	//乱数範囲(回転角用)
	std::uniform_real_distribution<float> rotDist(0.0f, XM_2PI);
	//乱数範囲(座標用)
	std::uniform_real_distribution<float> posDist(-10.0f, 10.0f);

	//キャラクターの大元
	worldTransform_[PartId::Root].Initialize();
	//子(脊椎)
	worldTransform_[PartId::Spine].translation_ = {0, 4.5f, 0};
	worldTransform_[PartId::Spine].parent_ = &worldTransform_[PartId::Root];
	worldTransform_[PartId::Spine].Initialize();

	//キャラクターの脊椎
	worldTransform_[PartId::Spine].Initialize();
	//子(胸)
	worldTransform_[PartId::Chest].translation_ = {0, -4.5f, 0};
	worldTransform_[PartId::Chest].parent_ = &worldTransform_[PartId::Spine];
	worldTransform_[PartId::Chest].Initialize();

	//キャラクターの胸
	worldTransform_[PartId::Chest].Initialize();
	//子(頭)
	worldTransform_[PartId::Head].translation_ = {0, -4.5f, 0};
	worldTransform_[PartId::Head].parent_ = &worldTransform_[PartId::Chest];
	worldTransform_[PartId::Head].Initialize();

	//キャラクターの胸
	worldTransform_[PartId::Chest].Initialize();
	//子(左腕)
	worldTransform_[PartId::ArmL].translation_ = {-5, -4.5f, 0};
	worldTransform_[PartId::ArmL].parent_ = &worldTransform_[PartId::Chest];
	worldTransform_[PartId::ArmL].Initialize();

	//キャラクターの胸
	worldTransform_[PartId::Chest].Initialize();
	//子(右腕)
	worldTransform_[PartId::ArmR].translation_ = {5, -4.5f, 0};
	worldTransform_[PartId::ArmR].parent_ = &worldTransform_[PartId::Chest];
	worldTransform_[PartId::ArmR].Initialize();

	//下半身

	//キャラクターの脊椎
	worldTransform_[PartId::Spine].Initialize();
	//子(ケツ)
	worldTransform_[PartId::Hip].translation_ = {0, -14.5f, 0};
	worldTransform_[PartId::Hip].parent_ = &worldTransform_[PartId::Spine];
	worldTransform_[PartId::Hip].Initialize();

	//キャラクターのケツ
	worldTransform_[PartId::Hip].Initialize();
	//子(左足)
	worldTransform_[PartId::Legl].translation_ = {-5, -4.5f, 0};
	worldTransform_[PartId::Legl].parent_ = &worldTransform_[PartId::Hip];
	worldTransform_[PartId::Legl].Initialize();

	//キャラクターの脊椎
	worldTransform_[PartId::Hip].Initialize();
	//子(右足)
	worldTransform_[PartId::LegR].translation_ = {5, -4.5f, 0};
	worldTransform_[PartId::LegR].parent_ = &worldTransform_[PartId::Hip];
	worldTransform_[PartId::LegR].Initialize();

	//カメラ垂直方向視野角を設定
	viewProjection_.fovAngleY = XMConvertToRadians(10.0f);
	//アスペクト比を設定
	viewProjection_.aspectRatio = 1.0f;

	//ニアクリップ距離を設定
	/*viewProjection_.nearZ = 52.0f;*/
	//ファークリップ距離を設定
	/*viewProjection_.farZ = 53.0f;*/

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();


}

void GameScene::Update() {
	//スプライトの今の座標を取得
	// XMFLOAT2 position = sprite_->GetPosition();
	//座標を{2,0}移動
	// position.x += 2.0f;
	// position.y += 1.0f;
	//移動した座標をスプライトに反映
	// sprite_->SetPosition(position);

	//スペースキーを押した瞬間
	// if (input_->TriggerKey(DIK_SPACE)) {
	//音声停止
	// audio_->StopWave(voiceHandle_);
	//}

	//デバッグテキストの表示
	// debugText_->Print("Kaizokuou ni oreha naru.", 50, 50, 1.0f);
	//書式指定付き表示
	// debugText_->SetPos(50, 70);
	// debugText_->Printf("year:%d", 2001);

	//変数の値をインクリメント
	// value_++;
	//値を含んだ文字
	// std::string strDebug = std::string("value:") +
	// std::to_string(value_);
	//デバッグテキストの表示
	// debugText_->Print(strDebug, 50, 30, 1.0f);

	/*debugText_->SetPos(50, 70);
	debugText_->Printf(
	  "translation:(%f,%f,%f)", worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z);

	debugText_->SetPos(50, 100);
	debugText_->Printf(
	  "rotation:(%f,%f,%f)", worldTransform_.rotation_.x, worldTransform_.rotation_.y,
	  worldTransform_.rotation_.z);

	debugText_->SetPos(50, 130);
	debugText_->Printf(
	  "scale:(%f,%f,%f)", worldTransform_.scale_.x, worldTransform_.scale_.y,
	  worldTransform_.scale_.z);*/

	//視点移動処理
	//視点の移動ベクトル
	// XMFLOAT3 move = {0, 0, 0};

	//視点の移動の速さ
	const float kEyeSpeed = 0.2f;

	////押した方向で移送ベクトルを変更
	// if (input_->PushKey(DIK_W)) {
	//	move = {0, 0, kEyeSpeed};
	// } else if (input_->PushKey(DIK_S)) {
	//	move = {0, 0, -kEyeSpeed};
	// }
	////視点移動(ベクトルの加算)
	// viewProjection_.eye.x += move.x;
	// viewProjection_.eye.y += move.y;
	// viewProjection_.eye.z += move.z;

	////行列の再計算
	// viewProjection_.UpdateMatrix();
	////デバッグ用表示
	// debugText_->SetPos(50, 50);
	// debugText_->Printf(
	//   "eye:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);

	// move = {0, 0, 0};
	////注視視点の移動の速さ
	// const float kTargetSpeed = 0.2f;

	////押した方向で移送ベクトルを変更
	// if (input_->PushKey(DIK_LEFT)) {
	//	move = {-kTargetSpeed, 0, 0};
	// } else if (input_->PushKey(DIK_RIGHT)) {
	//	move = {kTargetSpeed, 0, 0};
	// }
	////視点移動(ベクトルの加算)
	// viewProjection_.target.x += move.x;
	// viewProjection_.target.y += move.y;
	// viewProjection_.target.z += move.z;

	////行列の再計算
	// viewProjection_.UpdateMatrix();
	////デバッグ用表示
	// debugText_->SetPos(50, 70);
	// debugText_->Printf(
	//   "target:(%f,%f,%f)", viewProjection_.target.x, viewProjection_.target.y,
	//   viewProjection_.target.z);

	////上方向回転処理
	////上方向の回転速さ[ラジアン/frame]
	// const float kUpRotSpeed = 0.05f;

	////押した方向で移動ベクトルを変更
	// if (input_->PushKey(DIK_SPACE)) {
	//	viewAngle += kUpRotSpeed;
	//	// 2πを超えたら0に戻す
	//	viewAngle = fmodf(viewAngle, XM_2PI);
	// }
	////上方向ベクトルを計算(半径1の円周上の座標)
	// viewProjection_.up = {cosf(viewAngle), sinf(viewAngle), 0.0f};

	////行列の再計算
	// viewProjection_.UpdateMatrix();

	////デバッグ用表示
	// debugText_->SetPos(50, 90);
	// debugText_->Printf(
	//   "up:(%f,%f,%f)", viewProjection_.up.x, viewProjection_.up.y, viewProjection_.up.z);

	worldTransform_[PartId::Root].UpdateMatrix();
	worldTransform_[PartId::Spine].UpdateMatrix();
	worldTransform_[PartId::Chest].UpdateMatrix();
	worldTransform_[PartId::Head].UpdateMatrix();
	worldTransform_[PartId::ArmL].UpdateMatrix();
	worldTransform_[PartId::ArmR].UpdateMatrix();
	worldTransform_[PartId::Hip].UpdateMatrix();
	worldTransform_[PartId::Legl].UpdateMatrix();
	worldTransform_[PartId::LegR].UpdateMatrix();

	// Fov変更処理
	//上キーで視野角が広がる
	if (input_->PushKey(DIK_W)) {
		viewProjection_.fovAngleY += 0.01f;
		viewProjection_.fovAngleY = min(viewProjection_.fovAngleY, XM_PI);
		//上キーで視野角が広がる
	} else if (input_->PushKey(DIK_S)) {
		viewProjection_.fovAngleY -= 0.01f;
		viewProjection_.fovAngleY = max(viewProjection_.fovAngleY, 0.01f);
	}
	//行列の再計算
	viewProjection_.UpdateMatrix();

	////クリップ距離変更処理
	////上下キーでニアクリップ距離を増減
	//if (input_->PushKey(DIK_UP)) {
	//	viewProjection_.nearZ += 0.1f;
	//} else if (input_->PushKey(DIK_DOWN)) {
	//	viewProjection_.nearZ -= 0.1f;
	//}

	//行列の再計算
	viewProjection_.UpdateMatrix();

	//デバッグ用表示
	//debugText_->SetPos(50, 110);
	//debugText_->Printf("fovAngleY(Degree):%f", XMConvertToDegrees(viewProjection_.fovAngleY));

	////デバッグ用表示
	//debugText_->SetPos(50, 130);
	//debugText_->Printf("nearZ:%f", viewProjection_.nearZ);

	//キャラクター移動処理
	//キャラクターの移動ベクトル
	XMFLOAT3 move = {0, 0, 0};

	//キャラクターの移動の速さ
	const float kCharacterSpeed = 0.2f;

	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_LEFT)) {
		move = {-kCharacterSpeed, 0, 0};
	} else if (input_->PushKey(DIK_RIGHT)) {
		move = {kCharacterSpeed, 0, 0};
	}

	//注視点(ベクトルの加算)
	worldTransform_[PartId::Root].translation_.x += move.x;
	worldTransform_[PartId::Root].translation_.y += move.y;

	//デバッグ用表示
	debugText_->SetPos(50, 150);
	debugText_->Printf(
	  "Root:(%f,%f,%f)", worldTransform_[PartId::Root].translation_.x,
	  worldTransform_[PartId::Root].translation_.y, worldTransform_[PartId::Root].translation_.z);


//上半身の回転処理
	//上半身の回転の速さ[ラジアン/frame]
	const float kChestRotSpeed = 0.05f;

	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_U)) {
		worldTransform_[PartId::Chest].rotation_.y -= kChestRotSpeed;
	} else if (input_->PushKey(DIK_I)) {
		worldTransform_[PartId::Chest].rotation_.y += kChestRotSpeed;
	}

	//下半身の回転処理
	//下半身の回転の速さ[ラジアン/frame]
	const float kHipRotSpeed = 0.05f;

	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_J)) {
		worldTransform_[PartId::Hip].rotation_.y -= kHipRotSpeed;
	} else if (input_->PushKey(DIK_K)) {
		worldTransform_[PartId::Hip].rotation_.y += kHipRotSpeed;
	}



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
	// 3Dモデル描画

	//model_->Draw(worldTransform_[PartId::Root ], viewProjection_, textureHandle_);
	//model_->Draw(worldTransform_[PartId::Spine], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartId::Chest], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartId::Head ], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartId::ArmL ], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartId::ArmR ], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartId::Hip  ], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartId::Legl ], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartId::LegR ], viewProjection_, textureHandle_);
	

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	// sprite_->Draw();

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
