

#pragma once
#include <chrono>
#include <ctime>
#include <iostream>
using namespace std::chrono;

class frame
{
private:
	int id;
	long long frame_TimeStamp;

public:
	frame();
	int getid();
	long long getframe_TimeStamp();
	void setid(int id);
	void setframe_TimeStamp(long long frame_TimeStamp);

	static int current_id;
	


};

