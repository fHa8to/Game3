#include "Rect.h"
#include "DxLib.h"

Rect::Rect():
	m_x(0.0f),
	m_y(0.0f),
	m_z(0.0f),
	m_xWidth(0.0f),
	m_yHeight(0.0f),
	m_zDepth(0.0f)
{
	//����
	pos1 = VGet(0.0f, 0.0f, 0.0f);
	//����
	pos2 = VGet(0.0f, 0.0f, 0.0f);
	//�E��
	pos3 = VGet(0.0f, 0.0f, 0.0f);
	//�E��
	pos4 = VGet(0.0f, 0.0f, 0.0f);
	//���̍���
	pos5 = VGet(0.0f, 0.0f, 0.0f);
	//���̍���
	pos6 = VGet(0.0f, 0.0f, 0.0f);
	//���̉E��
	pos7 = VGet(0.0f, 0.0f, 0.0f);
	//���̉E��
	pos8 = VGet(0.0f, 0.0f, 0.0f);
}

Rect::~Rect()
{
}

void Rect::Draw(unsigned int Color, bool isFill)
{
	//���ォ��E��
	DrawLine3D(pos1, pos3, Color);
	//���ォ�獶��
	DrawLine3D(pos1, pos2, Color);
	//���ォ����̍���
	DrawLine3D(pos1, pos5, Color);
	//�E�ォ��E����
	DrawLine3D(pos3, pos4, Color);
	//�E�ォ����̉E��
	DrawLine3D(pos3, pos7, Color);
	//����������̍���
	DrawLine3D(pos2, pos6, Color);
	//��������E��
	DrawLine3D(pos2, pos4, Color);
	//�E��������̉E��
	DrawLine3D(pos4, pos8, Color);
	//���̍��ォ����̉E��
	DrawLine3D(pos5, pos7, Color);
	//���̍��ォ����̍���
	DrawLine3D(pos5, pos6, Color);
	//���̉E��������̉E��
	DrawLine3D(pos8, pos7, Color);
	//���̉E��������̍���
	DrawLine3D(pos8, pos6, Color);

}

void Rect::SetCenter(float x, float y, float z, float width, float height, float depth)
{
	//�������
	m_x = x;
	m_y = y;
	m_z = z;
	m_xWidth = x + width;
	m_yHeight = y + height;
	m_zDepth = z + depth;

	//������W
	pos1 = VGet(m_x, m_y, m_z);
	//�������W
	pos2 = VGet(m_x, m_yHeight, m_z);
	//�E����W
	pos3 = VGet(m_xWidth, m_y, m_z);
	//�E�����W
	pos4 = VGet(m_xWidth, m_yHeight, m_z);
	//���̍�����W
	pos5 = VGet(m_x, m_y, m_zDepth);
	//���̍������W
	pos6 = VGet(m_x, m_yHeight, m_zDepth);
	//���̉E����W
	pos7 = VGet(m_xWidth, m_y, m_zDepth);
	//���̉E�����W
	pos8 = VGet(m_xWidth, m_yHeight, m_zDepth);

}

bool Rect::IsCollsion(const Rect& rect)
{
	//��Γ�����Ȃ��p�^�[���ȊO�͓������Ă���
	if (m_x > rect.m_xWidth) return false;
	if (m_y > rect.m_yHeight) return false;
	if (m_xWidth < rect.m_x) return false;
	if (m_yHeight < rect.m_y) return false;
	if (m_z > rect.m_zDepth) return false;
	if (m_zDepth < rect.m_z) return false;

	//������Ȃ��p�^�[���ȊO�͓������Ă���
	return true;
}
