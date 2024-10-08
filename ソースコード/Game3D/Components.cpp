#include "Components.h"
#include "DxLib.h"
#include <cmath>
#include <algorithm>

// �g�����X�t�H�[��

Transform::Transform() :
	AngleY(0.0f)
{
}

Transform::~Transform()
{
}

// ���f��

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

	// �e�N�X�`���Ŏg�p����O���t�B�b�N�n���h����ύX����
	MV1SetTextureGraphHandle(ModelHandle, 0, textureHandle, FALSE);
}

void Model::UpdateModel(Transform& transform)
{
	// �ω�������s��
	MATRIX modelMtx;

	// ���f�����g�傷��
	MATRIX scaleMtx = MGetScale(transform.Scale.VGet());

	// ���f���̉�]��ݒ�
	MATRIX rotMtx = MGetRotY(transform.AngleY);

	// �s�����Z����
	modelMtx = MMult(scaleMtx, rotMtx);

	// ���f���̍��W���X�V����
	MATRIX transMtx = MGetTranslate(transform.Position.VGet());

	// �s�����Z����
	modelMtx = MMult(modelMtx, transMtx);

	// ���f���n���h���ɔ��f
	MV1SetMatrix(ModelHandle, modelMtx);
}

void Model::DrawModel() const
{
	// ���f���̕`��
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

// �A�j���[�V����

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

	// �Đ����̃A�j���[�V�����̃^�O��ۑ�����
	m_playAnimation = tag;
}

void Animation::UpdateAnimation(Model& model)
{
	// �O�̃t���[���ŃA�j���[�V�������I�����Ă�����f�t�H���g�ɖ߂�
	if (m_endAnimFlug) {
		ChangeAnimation(model, m_defaultTag, true);
	}

	// �Đ����Ԃ�i�߂�
	m_flameCount += 0.5f;

	// �u�����h���[�g�����Z���Ă���
	if (m_blendRate >= 1.0f) {
		MV1SetAttachAnimBlendRate(model.ModelHandle, m_attachIndex1, 1.0f);
	}
	else {
		m_blendRate += 0.25f;

		MV1SetAttachAnimBlendRate(model.ModelHandle, m_attachIndex2, 1.0f - m_blendRate);

		MV1SetAttachAnimBlendRate(model.ModelHandle, m_attachIndex1, m_blendRate);
	}

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB�����Ƃ�
	if (m_flameCount >= m_maxFlame) {

		// �R�l�N�g�t���O��true�������玟�̃A�j���[�V�������X�^�[�g������
		if (m_connectFlug) {
			m_animationState++;
			m_connectFlug = false;
			ChangeAnimation(model, m_connectAnimation[m_animationState], true);
			m_connectAnimation.clear();
		}
		// ���[�v�t���O��true�������烋�[�v������
		else if (m_loopFlug) {
			m_flameCount = 0.0f;
		}
		// ���S�ɏI��������t���O�𗧂Ă�
		else {
			m_endAnimFlug = true;
		}
	}

	// �A�j���[�V�����X�V
	MV1SetAttachAnimTime(model.ModelHandle, m_attachIndex1, m_flameCount);
}

// �A�j���[�V�����ύX
void Animation::ChangeAnimation(Model& model, int tag, bool loop)
{
	// �Đ�����A�j���[�V������ύX����
	if (tag != m_playAnimation) {
		// ���s�̃A�j���[�V�������f�^�b�`����
		MV1DetachAnim(model.ModelHandle, m_attachIndex2);

		// ���[�v�t���O��ۑ�
		m_loopFlug = loop;

		// �Đ����Ԃ��ŏ��ɖ߂�
		m_flameCount = 0.0f;

		// �s���Ă����A�j���[�V������ۑ�
		m_attachIndex2 = m_attachIndex1;

		// �A�j���[�V������ύX
		m_attachIndex1 = MV1AttachAnim(model.ModelHandle, tag);

		// �A�j���[�V�����̃t���[������ۑ�
		m_maxFlame = MV1GetAttachAnimTotalTime(model.ModelHandle, m_attachIndex1);

		// �Đ����̃A�j���[�V�����̃^�O��ۑ�����
		m_playAnimation = tag;

		// �A�j���[�V�����I���t���O��false��
		m_endAnimFlug = false;

		// �u�����h���[�g������������
		m_blendRate = 0.0f;
	}
}

// �A�j���[�V������A�����������Ƃ��̕ύX�֐�
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

// �J�v�Z��

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

	// �}�N���𖳌������ċ�����h��
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
