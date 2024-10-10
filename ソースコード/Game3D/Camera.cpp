#include "Camera.h"
#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"
#include "Pad.h"
#include <cmath>
#define D2R(deg) ((deg)*DX_PI_F/180.0f)

namespace
{
	constexpr float kCameraDist = 66;
	constexpr float kCameraHeight = 5;

	constexpr float kAngleSpeed = 0.05f;	//���񑬓x
	constexpr float kCameraPlayerTargetHeight = 400.0f;	//�v���C���[���W����ǂꂾ�������ʒu�𒍎��_�Ƃ��邩
	constexpr float kToPlayerLength = 1600.0f;	//�v���C���[�Ƃ̋���
	constexpr float kCollisionSize = 50.0f;		//�J�����̓����蔻��T�C�Y

	//�A�i���O�X�e�B�b�N�ɂ��ړ��֘A
	constexpr float kMaxSpeed = 0.5f;		//�v���C���[�̍ő�ړ����x
	constexpr float kAnalogRangeMin = 0.1;	//�A�i���O�X�e�B�b�N�̓��͔���͈�
	constexpr float kAnalogRangeMax = 0.8;
	constexpr float kAnalogInputMax = 1000.0f;	//�A�i���O�X�e�B�b�N������͂����x�N�g���̍ő�l
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera() :
	m_pos(VGet(0, 10, 0)),
	m_targetPos(VGet(0, 0, 0)),
	m_cameraangle(VGet(0, 0, 0)),
	m_angle(-DX_PI_F / 2)
{
	SetCameraNearFar(20, 1600);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
}

/// <summary>
/// ������
/// </summary>
void Camera::Init()
{
	//m_cameraangle = VGet(D2R(-20.0f), 0.0f, 0.0f);

}

/// <summary>
/// �v���C�V�[���̃A�b�v�f�[�g
/// </summary>
void Camera::PlayCameraUpdate(Player& player)
{
	//�A�i���O�X�e�B�b�N���g���Ĉړ�
	int analogX = 0;
	int analogZ = 0;

	GetJoypadAnalogInputRight(&analogX, &analogZ, DX_INPUT_PAD1);

	Pad::Update();

#ifdef _DEBUG

	DrawGrid();
	DrawLine(320, 240, 320 + analogX / 10, 240 + analogZ / 10, 0xff0fff, 4);

	DrawFormatString(0, 120, 0xffffff, "ANALOG(X:%d,Y:%d)", analogX, analogZ);
#endif

	// �J�����Ɉʒu�𔽉f
	//�����_�̍��W
	VECTOR playerAimPos = VGet(player.GetPos().x, player.GetPos().y + 20.0f, player.GetPos().z);
	//�x�N�g���̕���(�����_-�J�����̃|�W�V����)
	VECTOR posToAim = VSub(playerAimPos, m_pos);




	if (analogX >= 10)
	{
		m_angle -= 0.05f;

	}

	if (analogX <= -10)
	{
		m_angle += 0.05f;

	}

	//�����_�̍��W���v���C���[�̍��W�ɑ��
	m_targetPos = player.GetPos();



	m_pos.x += cosf(m_angle) * kCameraDist;
	m_pos.y += kCameraHeight;
	m_pos.z += sinf(m_angle) * kCameraDist;

	//���݈ʒu�ɐݒ肵���|�W�V�����𑫂�
	m_pos = VAdd(m_pos, posToAim);
	//SetCameraPositionAndTarget_UpVecY(m_pos, m_targetPos);
	SetCameraPositionAndTarget_UpVecY(m_pos, player.GetPos());
	//DrawSphere3D(m_pos, 30, 6, 0xff0000, 0xff0000, true);

}

/// <summary>
/// �^�C�g���V�[���̃A�b�v�f�[�g
/// </summary>
void Camera::TitleCameraUpdate()
{
#ifdef _DEBUG

	DrawGrid();


#endif
	Pad::Update();


	if (Pad::IsPress PAD_INPUT_6)
	{
		m_angle += 0.05f;
	}
	if (Pad::IsPress PAD_INPUT_5)
	{
		m_angle -= 0.05f;
	}

	m_pos.x = cosf(m_angle) * kCameraDist;
	m_pos.y = kCameraHeight;
	m_pos.z = sinf(m_angle) * kCameraDist;
	SetCameraPositionAndTarget_UpVecY(m_pos, VGet(0, 0, 0));
}


void Camera::DrawGrid()
{
#ifdef _DEBUG
	for (int x = -200; x <= 200; x += 10)
	{
		DrawLine3D(VGet(static_cast<float>(x), 0, -200), VGet(static_cast<float>(x), 0, 200), 0xffff00);
	}
	for (int z = -200; z <= 200; z += 10)
	{
		DrawLine3D(VGet(-200, 0, static_cast<float>(z)), VGet(200, 0, static_cast<float>(z)), 0xff0000);
	}

	// X+-,Z+-�̕�����������₷���悤�ɕ\����ǉ�����
	VECTOR dispPos = ConvWorldPosToScreenPos(VGet(200, 0, 0));
	DrawStringF(dispPos.x, dispPos.y, "X+", 0xffffff);
	dispPos = ConvWorldPosToScreenPos(VGet(-200, 0, 0));
	DrawStringF(dispPos.x, dispPos.y, "X-", 0xffffff);
	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, 200));
	DrawStringF(dispPos.x, dispPos.y, "Z+", 0xffffff);
	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, -200));
	DrawStringF(dispPos.x, dispPos.y, "Z-", 0xffffff);

	DrawFormatString(0, 64, 0xffffff, "Camera(x:%f,y:%f,z:%f)", m_pos.x, m_pos.y, m_pos.z);

#endif


}

