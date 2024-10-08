#pragma once
#include "Vec3.h"
#include <vector>

// 座標、拡大、回転を制御する
class Transform
{
public:
	Transform();
	~Transform();

	// 座標
	Vec3 Position;

	// 拡大
	Vec3 Scale;

	// 回転
	float AngleY;

private:

};

// モデル全般の制御をする
class Model
{
public:
	Model();
	~Model();

	// 3Dモデル初期処理
	void InitModel(int modelHandle, int textureHandle);
	
	// 3D更新処理
	void UpdateModel(Transform& transform);

	// 3Dモデル描画処理
	void DrawModel() const;

	// モデルハンドルのゲッター
	int GetModelHandle() const;

	// テクスチャのゲッター
	int GetTextureHandle() const;

	// モデルハンドル
	int ModelHandle = 0;

private:

	// モデルのテクスチャ
	int m_textureHandle = 0;

};

// アニメーションの制御をする
class Animation
{
public:
	Animation();
	~Animation();

	// アニメーション初期処理
	void InitAnimation(Model& model, int tag);

	// アニメーション更新処理
	void UpdateAnimation(Model& model);

	// アニメーション変更
	void ChangeAnimation(Model& model, int tag, bool loop);

	// 連続でアニメを切り替えたい場合のアニメーション変更
	void ChangeAnimationConnect(Model& model, int tag1, int tag2);

	// アニメーション終了フラグを返す
	bool GetEndAnimFlug();

; private:

	// 再生時間
	float m_flameCount = 0.0f;

	// 総フレーム数
	float m_maxFlame = 0.0f;

	// アニメーションインデックス
	int m_attachIndex1 = 0;
	int m_attachIndex2 = 0;

	// 再生中のアニメーション
	int m_playAnimation = 0;

	// 連続で再生するアニメーション
	std::vector<int> m_connectAnimation;

	// 連続で再生するアニメーションの進行状況
	int m_animationState = 0;
	
	// 現行のアニメーションタグ
	int m_runTag = 0;

	// ループ再生フラグ
	bool m_loopFlug = false;

	// デフォルトアニメーションタグ
	int m_defaultTag = 0;

	// アニメーションコネクトフラグ
	bool m_connectFlug = false;

	// アニメーションブレンドレート
	float m_blendRate = 0.0f;

	// アニメーション終了フラグ
	bool m_endAnimFlug = true;

};

class Capsule
{
public:
	Capsule();
	~Capsule();

	// 初期化処理
	void Init(Vec3 pos, float radius, float height);

	// 有効化
	void Aactivation();

	// 無効化
	void Invalidation();

	// 有効フラグを得る
	bool IsActivation();

	// コリジョンに値をセットする
	void Set(Vec3 pos);

	// 線分間の距離を求める
	float CapsuleDistance(const Vec3& p1, const Vec3& q1, const Vec3& p2, const Vec3& q2) const;

	// テスト表示
	void DrawCapsule() const;

	Vec3 PointA = 0;
	Vec3 PointB = 0;
	float Radius = 0;
private:
	float m_height = 0;
	bool m_valid = true;	// 基本有効化されている
};
