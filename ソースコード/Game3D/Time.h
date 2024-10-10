#pragma once
class Time
{
public:
	Time(int rimitTime);
	~Time();

	//ƒ^ƒCƒ€
	void Reset();

	bool Update();

private:
	int m_time;
	int m_rimitTime;
};

