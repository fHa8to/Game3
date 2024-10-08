#pragma once
#include<cmath>
#include "DxLib.h"

class Vec3
{
public:
	float x;
	float y;
	float z;
public:
	Vec3() :
		x(0.0f),
		y(0.0f),
		z(0.0f)
	{
	}

	Vec3(float X, float Y, float Z) :
		x(X),
		y(Y),
		z(Z)
	{
	}

	Vec3(int X, int Y, int Z) :
		x(static_cast<float>(X)),
		y(static_cast<float>(Y)),
		z(static_cast<float>(Z))
	{

	}

	Vec3(int num) :
		x(static_cast<float>(num)),
		y(static_cast<float>(num)),
		z(static_cast<float>(num))
	{

	}

	Vec3(VECTOR vec) :
		x(vec.x),
		y(vec.y),
		z(vec.z) 
	{
	}

	//int�^�ɃL���X�g���ĕԂ�
	int intX() const {
		return static_cast<int>(x);
	}
	int intY() const {
		return static_cast<int>(y);
	}

	int intZ() const {
		return static_cast<int>(z);
	}

	////*���Z�q�̃I�[�o�[���[�h*////
	Vec3 operator =(float num) {
		x = num;
		y = num;
		z = num;
		return *this;
	}

	Vec3 operator =(int num) {
		x = static_cast<float>(num);
		y = static_cast<float>(num);
		z = static_cast<float>(num);
		return *this;
	}

	Vec3 operator = (VECTOR vec) {
		x = vec.x;
		y = vec.y;
		z = vec.z;
		return *this;
	}

	Vec3 operator +() const {
		return *this;
	}

	Vec3 operator -() const {
		return Vec3{ -x,-y,-z };
	}

	//�����Z
	Vec3 operator +(Vec3 vec) const {
		return Vec3{ x + vec.x,y + vec.y,z + vec.z };
	}

	Vec3 operator +=(Vec3 vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	Vec3 operator +(float num) const {
		return Vec3{ x + num,y + num,z + num };
	}

	Vec3 operator +(int num) const {
		return Vec3{ x + static_cast<float>(num),y + static_cast<float>(num),z + static_cast<float>(num) };
	}

	Vec3 operator +=(float num) {
		x += num;
		y += num;
		z += num;
		return *this;
	}

	Vec3 operator +=(int num) {
		x += static_cast<float>(num);
		y += static_cast<float>(num);
		z += static_cast<float>(num);
		return *this;
	}

	//�����Z
	Vec3 operator -(Vec3 vec) const {
		return Vec3{ x - vec.x,y - vec.y,z - vec.z };
	}

	Vec3 operator -=(Vec3 vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}

	Vec3 operator -(float num) const {
		return Vec3{ x - num,y - num,z - num };
	}

	Vec3 operator -(int num) const {
		return Vec3{ x - static_cast<float>(num),y - static_cast<float>(num),z - static_cast<float>(num) };
	}

	Vec3 operator -=(float num) {
		x -= num;
		y -= num;
		z -= num;
		return *this;
	}

	Vec3 operator -=(int num) {
		x -= static_cast<float>(num);
		y -= static_cast<float>(num);
		z -= static_cast<float>(num);
		return *this;
	}

	//�|���Z
	Vec3 operator *(float num) const {
		return Vec3{ x * num,y * num,z * num };
	}

	Vec3 operator *(int num) const {
		return Vec3{ x * static_cast<float>(num),y * static_cast<float>(num),z * static_cast<float>(num) };
	}

	Vec3 operator *=(float num) {
		x *= num;
		y *= num;
		z *= num;
		return *this;
	}

	Vec3 operator *=(int num) {
		x *= static_cast<float>(num);
		y *= static_cast<float>(num);
		z *= static_cast<float>(num);
		return *this;
	}

	//����Z
	Vec3 operator /(float num) const {
		return Vec3{ x / num,y / num,z / num };
	}

	Vec3 operator /(int num) const {
		return Vec3{ x / static_cast<float>(num),y / static_cast<float>(num),z / static_cast<float>(num) };
	}

	Vec3 operator /=(float num) {
		x /= num;
		y /= num;
		z /= num;
		return *this;
	}

	Vec3 operator /=(int num) {
		x /= static_cast<float>(num);
		y /= static_cast<float>(num);
		z /= static_cast<float>(num);
		return *this;
	}

	//�x�N�g���̒����̓������߂�
	float SqLength() const {
		return x * x + y * y + z * z;
	}

	//�x�N�g���̒��������߂�
	float Length() const {
		return sqrtf(SqLength());
	}

	//���g�̐��K�����s��
	void Normalize() {
		float len = Length();

		//����0�ȉ��Ȃ珈�����s��Ȃ�
		if (len <= 0.0f) return;

		x /= len;
		y /= len;
		z /= len;
	}

	//���M�𐳋K�������x�N�g�����擾����
	Vec3 GetNormalized() const {
		float len = Length();

		//����0�ȉ��Ȃ�(0,0)��Ԃ�
		//��������ɂ��Ă��闝�R
		//�����Ȃ��R���X�g���N�^�̏C���ɋ������邽��
		if (len <= 0.0f) return Vec3{ 0.0f,0.0f,0.0f };

		return Vec3{ x / len,y / len,z / len };
	}

	// ���M��dxlib��VECTOR�ɂ��ĕԂ�
	VECTOR VGet() const {
		return DxLib::VGet(x, y, z);
	}

	// ���g�⑼�̃x�N�g���Ƃ̓��ς��Ƃ�
	float dot(const Vec3& other) const {
		return x * other.x + y * other.y + z * other.z;
	}
};

