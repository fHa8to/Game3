#include "SceneGame.h"
#include "DxLib.h"
#include "Camera.h"
#include "SceneClear.h"
#include "SceneOver.h"
#include "Game.h"
#include "Pad.h"

namespace
{

	//フェードイン、フェードアウトの数値
	constexpr int kFadeValue = 255;

	//フェード値の増減
	constexpr int kFadeUpDown = 8;

	//モデルのファイル名
	const char* const kModelFilename = "data/model/tileHigh_forest.mv1";

	//モデルのサイズ変更
	constexpr float kExpansion = 150.0f;
}

void DrawGrid()
{
	for (int x = -80; x <= 80; x += 10)
	{
		DrawLine3D(VGet(static_cast<float>(x), 0, -80), VGet(static_cast<float>(x), 0, 80), 0xffff00);
	}
	for (int z = -80; z <= 80; z += 10)
	{
		DrawLine3D(VGet(-80, 0, static_cast<float>(z)), VGet(80, 0, static_cast<float>(z)), 0xff0000);
	}

	// X+-,Z+-の方向が分かりやすいように表示を追加する
	VECTOR dispPos = ConvWorldPosToScreenPos(VGet(500, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(-500, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X-", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, 500));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, -500));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z-", 0xffffff);
	}
}


SceneGame::SceneGame():
	m_isPlayerHit(false),
	m_isEnemyHit(false),
	m_isAttackHit(false),
	m_pos(VGet(0.0f, -300.0f, 0.0f))
{
	m_pEnemy = std::make_shared<Enemy>();
	m_pPlayer = std::make_shared<Player>();
	m_pCamera = std::make_shared<Camera>();
	//3Dモデルの読み込み
	modelHandle = MV1LoadModel(kModelFilename);



}

SceneGame::~SceneGame()
{

}

void SceneGame::Init()
{
	MV1SetScale(modelHandle, VGet(kExpansion, kExpansion, kExpansion));
	m_pPlayer->Init();
	m_pEnemy->Init();
	m_pCamera->Init();



	playerHp = P_HP_MAX;
	playerDrawValue = playerHp * P_DRAW_SIZE;

	enemyHp = E_HP_MAX;
	enemyDrawValue = enemyHp * E_DRAW_SIZE;

}

std::shared_ptr<SceneBase> SceneGame::Update()
{
	

	int pTargetValut = playerHp * P_DRAW_SIZE;

	if (playerDrawValue > pTargetValut)
	{
		playerDrawValue--;
	}
	int eTargetValut = enemyHp * E_DRAW_SIZE;

	if (enemyDrawValue > eTargetValut)
	{
		enemyDrawValue--;
	}

	m_cameraPos = m_pCamera->GetCameraPos();

	m_pPlayer->Update(m_cameraPos);

	m_playerPos = m_pPlayer->GetPos();

	m_isPlayerHit = m_pEnemy->SphereHitFlag(m_pPlayer);

	m_isEnemyHit = m_pPlayer->SphereHitFlag(m_pEnemy);


	m_pEnemy->Update(m_playerPos);
	m_pCamera->Update(m_playerPos);

	MV1SetPosition(modelHandle, m_pos);



	VECTOR toEnemy = VSub(m_pEnemy->GetPos(), m_pPlayer->GetPos());


	float length = VSize(toEnemy);

	//プレイヤーとエネミーが当たった場合
	if (m_isPlayerHit)
	{

		VECTOR posVec;
		VECTOR moveVec;


		//エネミーのベクトル座標からプレイヤーのベクトル座標を引いたベクトル
		posVec = VSub(m_pEnemy->GetPos(), m_pPlayer->GetPos());

		moveVec = VScale(posVec, length - (m_pPlayer->GetRadius() + m_pEnemy->GetRadius()));
		m_pPlayer->SetPos(VAdd(m_pPlayer->GetPos(), moveVec));

		playerHp -= 1;

	}

	//プレイヤー攻撃が当たった場合
	if (Pad::IsTrigger(PAD_INPUT_1) &&m_isEnemyHit)
	{
		VECTOR posVec2;
		VECTOR moveVec2;

		//プレイヤーのベクトル座標からエネミーのベクトル座標を引いたベクトル
		posVec2 = VSub(m_pPlayer->GetPos(),m_pEnemy->GetPos());

		moveVec2 = VScale(posVec2, - (m_pPlayer->GetRadius() + m_pEnemy->GetRadius()));
		m_pEnemy->SetPos(VAdd(m_pEnemy->GetPos(), moveVec2));

		enemyHp -= 1;
	}


	//プレイヤーのHPがゼロになったら
	if (playerHp <= 0)
	{
		//SceneOverに遷移
		return std::make_shared<SceneOver>();

	}

	//エネミーのHPがゼロになったら
	if (enemyHp <= 0)
	{
		//SceneClearに遷移
		return std::make_shared<SceneClear>();

	}
	return shared_from_this();	//自身のshared_ptrを返す




}

void SceneGame::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(modelHandle);


#ifdef _DEBUG

	DrawGrid();
	
#endif

	m_pPlayer->Draw();
	m_pEnemy->Draw();
	m_pCamera->Draw();

	//プレイヤーのHPバー
	int playerColor = GetColor(0, 255, 0);
	DrawFormatString(15, 600, GetColor(0, 255, 255), "HP ", playerDrawValue);
	DrawFillBox(48, 598, 352, 618, GetColor(255, 255, 255));
	DrawFillBox(50, 600, 100 + playerHp * P_DRAW_SIZE, 616, playerColor);
	
	//エネミーのHPバー
	int enemyColor = GetColor(255, 0, 0);
	DrawFormatString(15, 50, GetColor(0, 255, 255), "HP ", enemyDrawValue);
	DrawFillBox(48, 48, 352, 68, GetColor(255, 255, 255));
	DrawFillBox(50, 50, 100 + enemyHp * E_DRAW_SIZE, 66, enemyColor);


#ifdef _DEBUG

	
	DrawString(8, 8, "SceneGame", GetColor(255, 255, 255));

#endif




}

void SceneGame::End()
{
}

