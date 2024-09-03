#pragma once
#include "DxLib.h"

class Rect
{
public:
	Rect();
	virtual ~Rect();

	//�l�p�̕`��
	void Draw(unsigned int Color, bool isFill);

	//���S���W�ƕ��������w��
	void SetCenter(float x, float y, float z, float width, float height, float depth);

	//��`�̓��m�̓����蔻��
	bool IsCollsion(const Rect& rect);

	//����̍��W
	VECTOR pos1;
	//�����̍��W
	VECTOR pos2;
	//�E��̍��W
	VECTOR pos3;
	//�E���̍��W
	VECTOR pos4;
	//���̍���
	VECTOR pos5;
	//���̍���
	VECTOR pos6;
	//���̉E��
	VECTOR pos7;
	//���̉E��
	VECTOR pos8;

private:
	//������邽�߂̕ϐ�
	float m_x;
	float m_y;
	float m_z;
	float m_xWidth;
	float m_yHeight;
	float m_zDepth;

};

