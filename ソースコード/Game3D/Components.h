#pragma once
#include "Vec3.h"
#include <vector>

// ���W�A�g��A��]�𐧌䂷��
class Transform
{
public:
	Transform();
	~Transform();

	// ���W
	Vec3 Position;

	// �g��
	Vec3 Scale;

	// ��]
	float AngleY;

private:

};

// ���f���S�ʂ̐��������
class Model
{
public:
	Model();
	~Model();

	// 3D���f����������
	void InitModel(int modelHandle, int textureHandle);
	
	// 3D�X�V����
	void UpdateModel(Transform& transform);

	// 3D���f���`�揈��
	void DrawModel() const;

	// ���f���n���h���̃Q�b�^�[
	int GetModelHandle() const;

	// �e�N�X�`���̃Q�b�^�[
	int GetTextureHandle() const;

	// ���f���n���h��
	int ModelHandle = 0;

private:

	// ���f���̃e�N�X�`��
	int m_textureHandle = 0;

};

// �A�j���[�V�����̐��������
class Animation
{
public:
	Animation();
	~Animation();

	// �A�j���[�V������������
	void InitAnimation(Model& model, int tag);

	// �A�j���[�V�����X�V����
	void UpdateAnimation(Model& model);

	// �A�j���[�V�����ύX
	void ChangeAnimation(Model& model, int tag, bool loop);

	// �A���ŃA�j����؂�ւ������ꍇ�̃A�j���[�V�����ύX
	void ChangeAnimationConnect(Model& model, int tag1, int tag2);

	// �A�j���[�V�����I���t���O��Ԃ�
	bool GetEndAnimFlug();

; private:

	// �Đ�����
	float m_flameCount = 0.0f;

	// ���t���[����
	float m_maxFlame = 0.0f;

	// �A�j���[�V�����C���f�b�N�X
	int m_attachIndex1 = 0;
	int m_attachIndex2 = 0;

	// �Đ����̃A�j���[�V����
	int m_playAnimation = 0;

	// �A���ōĐ�����A�j���[�V����
	std::vector<int> m_connectAnimation;

	// �A���ōĐ�����A�j���[�V�����̐i�s��
	int m_animationState = 0;
	
	// ���s�̃A�j���[�V�����^�O
	int m_runTag = 0;

	// ���[�v�Đ��t���O
	bool m_loopFlug = false;

	// �f�t�H���g�A�j���[�V�����^�O
	int m_defaultTag = 0;

	// �A�j���[�V�����R�l�N�g�t���O
	bool m_connectFlug = false;

	// �A�j���[�V�����u�����h���[�g
	float m_blendRate = 0.0f;

	// �A�j���[�V�����I���t���O
	bool m_endAnimFlug = true;

};

class Capsule
{
public:
	Capsule();
	~Capsule();

	// ����������
	void Init(Vec3 pos, float radius, float height);

	// �L����
	void Aactivation();

	// ������
	void Invalidation();

	// �L���t���O�𓾂�
	bool IsActivation();

	// �R���W�����ɒl���Z�b�g����
	void Set(Vec3 pos);

	// �����Ԃ̋��������߂�
	float CapsuleDistance(const Vec3& p1, const Vec3& q1, const Vec3& p2, const Vec3& q2) const;

	// �e�X�g�\��
	void DrawCapsule() const;

	Vec3 PointA = 0;
	Vec3 PointB = 0;
	float Radius = 0;
private:
	float m_height = 0;
	bool m_valid = true;	// ��{�L��������Ă���
};
