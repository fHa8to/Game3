#pragma once
class Time
{
public:
	Time(int rimitTime);
	~Time();

	//�^�C��
	void Reset();

	bool Update();

private:
	int m_time;
	int m_rimitTime;
};

