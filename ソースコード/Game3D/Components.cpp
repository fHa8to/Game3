#include "Components.h"
#include "DxLib.h"
#include <cmath>
#include <algorithm>

// トランスフォーム

Transform::Transform() :
	AngleY(0.0f)
{
}

Transform::~Transform()
{
}

// モデル

Model::Model() :
	ModelHandle(0),
	m_textureHandle(0)
{
}

Model::~Model()
{
	MV1DeleteModel(ModelHandle);
	DeleteGraph(m_textureHandle);

}

void Model::InitModel(int modelHandle, int textureHandle)
{
	ModelHandle = modelHandle;
	m_textureHandle = textureHandle;

	// テクスチャで使用するグラフィックハンドルを変更する
	MV1SetTextureGraphHandle(ModelHandle, 0, textureHandle, FALSE);
}

void Model::UpdateModel(Transform& transform)
{
	// 変化させる行列
	MATRIX modelMtx;

	// モデルを拡大する
	MATRIX scaleMtx = MGetScale(transform.Scale.VGet());

	// モデルの回転を設定
	MATRIX rotMtx = MGetRotY(transform.AngleY);

	// 行列を乗算する
	modelMtx = MMult(scaleMtx, rotMtx);

	// モデルの座標を更新する
	MATRIX transMtx = MGetTranslate(transform.Position.VGet());

	// 行列を乗算する
	modelMtx = MMult(modelMtx, transMtx);

	// モデルハンドルに反映
	MV1SetMatrix(ModelHandle, modelMtx);
}

void Model::DrawModel() const
{
	// モデルの描画
	MV1DrawModel(ModelHandle);
}

int Model::GetModelHandle() const
{
	return ModelHandle;
}

int Model::GetTextureHandle() const
{
	return m_textureHandle;
}

// アニメーション

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::InitAnimation(Model& model, int tag)
{
	m_defaultTag = tag;

	m_loopFlug = true;

	m_endAnimFlug = false;

	m_attachIndex1 = MV1AttachAnim(model.ModelHandle, tag);
	m_attachIndex2 = MV1AttachAnim(model.ModelHandle, tag);
	m_maxFlame = MV1GetAttachAnimTotalTime(model.ModelHandle, m_attachIndex1);

	// 再生中のアニメーションのタグを保存する
	m_playAnimation = tag;
}

void Animation::UpdateAnimation(Model& model)
{
	// 前のフレームでアニメーションが終了していたらデフォルトに戻す
	if (m_endAnimFlug) {
		ChangeAnimation(model, m_defaultTag, true);
	}

	// 再生時間を進める
	m_flameCount += 0.5f;

	// ブレンドレートを加算していく
	if (m_blendRate >= 1.0f) {
		MV1SetAttachAnimBlendRate(model.ModelHandle, m_attachIndex1, 1.0f);
	}
	else {
		m_blendRate += 0.25f;

		MV1SetAttachAnimBlendRate(model.ModelHandle, m_attachIndex2, 1.0f - m_blendRate);

		MV1SetAttachAnimBlendRate(model.ModelHandle, m_attachIndex1, m_blendRate);
	}

	// 再生時間がアニメーションの総再生時間に達したとき
	if (m_flameCount >= m_maxFlame) {

		// コネクトフラグがtrueだったら次のアニメーションをスタートさせる
		if (m_connectFlug) {
			m_animationState++;
			m_connectFlug = false;
			ChangeAnimation(model, m_connectAnimation[m_animationState], true);
			m_connectAnimation.clear();
		}
		// ループフラグがtrueだったらループさせる
		else if (m_loopFlug) {
			m_flameCount = 0.0f;
		}
		// 完全に終了したらフラグを立てる
		else {
			m_endAnimFlug = true;
		}
	}

	// アニメーション更新
	MV1SetAttachAnimTime(model.ModelHandle, m_attachIndex1, m_flameCount);
}

// アニメーション変更
void Animation::ChangeAnimation(Model& model, int tag, bool loop)
{
	// 再生するアニメーションを変更する
	if (tag != m_playAnimation) {
		// 現行のアニメーションをデタッチする
		MV1DetachAnim(model.ModelHandle, m_attachIndex2);

		// ループフラグを保存
		m_loopFlug = loop;

		// 再生時間を最初に戻す
		m_flameCount = 0.0f;

		// 行っていたアニメーションを保存
		m_attachIndex2 = m_attachIndex1;

		// アニメーションを変更
		m_attachIndex1 = MV1AttachAnim(model.ModelHandle, tag);

		// アニメーションのフレーム数を保存
		m_maxFlame = MV1GetAttachAnimTotalTime(model.ModelHandle, m_attachIndex1);

		// 再生中のアニメーションのタグを保存する
		m_playAnimation = tag;

		// アニメーション終了フラグをfalseに
		m_endAnimFlug = false;

		// ブレンドレートを初期化する
		m_blendRate = 0.0f;
	}
}

// アニメーションを連続させたいときの変更関数
void Animation::ChangeAnimationConnect(Model& model, int tag1, int tag2)
{
	m_endAnimFlug = false;
	m_connectFlug = true;
	m_connectAnimation.push_back(tag1);
	m_connectAnimation.push_back(tag2);
	ChangeAnimation(model, m_connectAnimation[m_animationState], false);
}

bool Animation::GetEndAnimFlug()
{
	return m_endAnimFlug;
}

// カプセル

Capsule::Capsule()
{
}

Capsule::~Capsule()
{
}

void Capsule::Init(Vec3 pos, float radius, float height)
{
	Radius = radius;
	m_height = height;

	Vec3 vecA = Vec3{ pos.x,pos.y + Radius,pos.z };
	Vec3 vecB = Vec3{ pos.x,pos.y + Radius + m_height,pos.z };

	PointA = vecA;
	PointB = vecB;
}

void Capsule::Aactivation()
{
	m_valid = true;
}

void Capsule::Invalidation()
{
	m_valid = false;
}

bool Capsule::IsActivation()
{
	return m_valid;
}

void Capsule::Set(Vec3 pos)
{
	Vec3 vecA = Vec3{ pos.x,pos.y + Radius,pos.z };
	Vec3 vecB = Vec3{ pos.x,pos.y + Radius + m_height,pos.z };

	PointA = vecA;
	PointB = vecB;
}

float Capsule::CapsuleDistance(const Vec3& p1, const Vec3& q1, const Vec3& p2, const Vec3& q2) const
{
	Vec3 d1 = q1 - p1;
	Vec3 d2 = q2 - p2;
	Vec3 r = p1 - p2;
	float a = d1.dot(d1);
	float e = d2.dot(d2);
	float f = d2.dot(r);

	float s, t;
	const float epsilon = static_cast<float>(1e-6);
	float c = d1.dot(r);
	float b = d1.dot(d2);
	float denom = a * e - b * b;

	// マクロを無効化して競合を防ぐ
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

	if (denom != 0) {
		s = (b * f - c * e) / denom;
	}
	else {
		s = 0.0f;
	}
	s = std::max(0.0f, std::min(1.0f, s));
	t = (b * s + f) / e;

	if (t < 0.0f) {
		t = 0.0f;
		s = std::max(0.0f, std::min(1.0f, -c / a));
	}
	else if (t > 1.0f) {
		t = 1.0f;
		s = std::max(0.0f, std::min(1.0f, (b - c) / a));
	}

	Vec3 closestPoint1 = p1 + d1 * s;
	Vec3 closestPoint2 = p2 + d2 * t;
	return (closestPoint1 - closestPoint2).Length();
}

void Capsule::DrawCapsule() const
{
	if (m_valid) {
		DrawSphere3D(PointA.VGet(), Radius, 4, 0xff0000, 0xff0000, false);
		DrawSphere3D(PointB.VGet(), Radius, 4, 0xff0000, 0xff0000, false);

		Vec3 veca = Vec3{ PointA.x + Radius,PointA.y,PointA.z };
		Vec3 vecb = Vec3{ PointB.x + Radius,PointB.y,PointB.z };
		DrawLine3D(veca.VGet(), vecb.VGet(), 0xff0000);

		veca = Vec3{ PointA.x - Radius,PointA.y,PointA.z };
		vecb = Vec3{ PointB.x - Radius,PointB.y,PointB.z };
		DrawLine3D(veca.VGet(), vecb.VGet(), 0xff0000);

		veca = Vec3{ PointA.x ,PointA.y,PointA.z + Radius };
		vecb = Vec3{ PointB.x ,PointB.y,PointB.z + Radius };
		DrawLine3D(veca.VGet(), vecb.VGet(), 0xff0000);

		veca = Vec3{ PointA.x ,PointA.y,PointA.z - Radius };
		vecb = Vec3{ PointB.x ,PointB.y,PointB.z - Radius };
		DrawLine3D(veca.VGet(), vecb.VGet(), 0xff0000);
	}
}
