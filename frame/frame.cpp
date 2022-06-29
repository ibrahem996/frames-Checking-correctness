

#include "frame.h"
#include <chrono>

#include <thread>
#include <ctime>
#include <iostream>	
#include <stdlib.h>		//for using the function sleep
using namespace std;
using namespace std::chrono;

int frame::current_id = 0;

frame::frame()
{
	this->id = this->current_id;
	auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	this->frame_TimeStamp = millisec_since_epoch;
	this->current_id++;
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

int frame::getid()
{
	return this->id;
}

long long frame::getframe_TimeStamp()
{
	return this->frame_TimeStamp;
}

void frame::setid(int id)
{
	this->id = id;
}

void frame::setframe_TimeStamp(long long frame_TimeStamp)
{
	this->frame_TimeStamp = frame_TimeStamp;
}
;


