#include "Camera.h"
#include "DxLib.h"
#include "Player.h"
#include "Pad.h"
#define _USE_MATH_DEFINES

#include <math.h>

namespace
{
	//�J�����̕`��͈�
	constexpr float kMinimumDrawingrange = 100.0f;
	constexpr float kMaximumDrawingrange =5000.0f;

	//�J�����̍��W
	constexpr float kCameraPosY = 500.0f;
	constexpr float kCameraPosZ = -800.0f;

	// ���񑬓x
	constexpr float kAngleSpeed = 0.05f;	

	//�����_�̍��W
	constexpr float kCameraTargetY = 100.0f;

	//�J�����̋���
	constexpr float kCameraDist = 1000.0f;
	//constexpr float kCameraHeight = 100;

	// ����p
	constexpr float kFov = (DX_PI_F / 180.0f) * 60.0f;
	// ��O�N���b�v����
	constexpr float kNear = 0.1f;
	// ���N���b�v����
	constexpr float kFar = 1000.0f;
	// �J�����̏��������_
	constexpr float kTargetX = 100.0f;        // X��
	constexpr float kTargetY = 400.0f;    // Y��
	constexpr float kTargetZ = -870.0f;    // Z��
	// �J�����̒��S���W
	constexpr float kScreenCenterX = 50.0f;    // X���W
	constexpr float kScreenCenterY = 1000.0f;    // Y���W

	constexpr float AngleSpeed = 0.05f;	// ���񑬓x
}


Camera::Camera()
{
		

}


Camera::~Camera()
{
	// �����Ȃ�.
}

void Camera::Init()
{
	//���s100�`5000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(kMinimumDrawingrange, kMaximumDrawingrange);


	//������
	m_cameraPos = VGet(0.0f, 0.0f, 0.0f);
	
	m_cameraTarget = VGet(0.0f, 0.0f, 0.0f);

	m_cameraAngle = 0.0f;

	m_angleH = 0.0f;

	m_pad = 0;
}


void Camera::Update(VECTOR mplayerPos)
{

#if _DEBUG

	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_5))
	{
		m_cameraPos.x += 500.0f;
		m_cameraPos.z += 600.0f;
	}

#endif

	Pad::Update();


	if (Pad::isPress PAD_INPUT_6)
	{
		m_angleH += AngleSpeed;

		// �P�W�O�x�ȏ�ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x������
		if (m_angleH > DX_PI_F)
		{
			m_angleH -= DX_TWO_PI_F;
		}
	}
	if (Pad::isPress PAD_INPUT_5)
	{
		m_angleH -= kAngleSpeed;

		// �|�P�W�O�x�ȉ��ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x�𑫂�
		if (m_angleH < -DX_PI_F)
		{
			m_angleH += DX_TWO_PI_F;
		}
	}

	
	m_cameraPos.x = cosf(m_angleH) * kCameraDist;
	m_cameraPos.y = kCameraPosY;
	m_cameraPos.z = sinf(m_angleH) * kCameraDist;

	// �J�������W
	m_cameraPos = VAdd(mplayerPos, m_cameraPos);

	// �����_
	m_cameraTarget = VAdd(mplayerPos, VGet(0.0f, kCameraTargetY, 0.0f));

	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_cameraTarget);

}

void Camera::Draw()
{

#ifdef _DEBUG
	DrawFormatString(160, 200, GetColor(255, 255, 255), "�J�����̍��W(%.2f,%.2f,%.2f)", m_cameraPos.x, m_cameraPos.y, m_cameraPos.z);

	DrawFormatString(250, 250, GetColor(255, 255, 255), "%d", m_input.Rx);
#endif
}

//Camera::Camera():
//	fov		(60.0f),
//	pos		(VGet(0,0,0))
//{
//	SetCameraNearFar(0.1f, 1000.0f);
//}
//
//void Camera::Update()
//{
//	//�p�b�h�A�i���O���擾
//	DINPUT_JOYSTATE input;
//
//	//���͏�ԏ�����
//	input.Rx = 0;
//	input.Ry = 0;
//
//	// ���͏�Ԃ��擾
//	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);
//
//
//	//float cameraAngle = -DX_PI_F / 2;
//
//	//if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_5))
//	//{
//	//	cameraAngle += 0.05f;
//	//}
//	//if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_6))
//	//{
//	//	cameraAngle -= 0.05f;
//	//}
//
//	SetupCamera_Perspective(fov * (static_cast<float>(M_PI) / 180.0f));
//	pos = VGet(0, 3.0f, -8.0f);
//	SetCameraPositionAndTarget_UpVecY(pos, VGet(0, pos.y, 4.0f));
//
//}
