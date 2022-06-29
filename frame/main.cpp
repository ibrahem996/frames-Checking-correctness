// frame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "frame.h"
#include <ctime>
#include <iostream>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;
using namespace std::chrono;
using namespace std;
static int id_drops;


frame* GenerateFramesArray(int sizeOfArray, long long frameTime)
{
	frame* Generated_frames = new frame[sizeOfArray];
	for (int i = 1; i < sizeOfArray+1 ; i++)
	{
		Generated_frames[i].setframe_TimeStamp(Generated_frames[i - 1].getframe_TimeStamp() + frameTime);
	}
	return Generated_frames;
}


void printFramesArray(frame* frames, int sizeOfArray)
{
	for (int i = 0; i < sizeOfArray; i++)
	{
		cout << " frame id : " << frames[i].getid() << "\t\t";
		cout << " milliseconds since the Epoch: " << frames[i].getframe_TimeStamp() << "\n";
	}
	return;
}


bool FramesId_check(frame* frames, int sizeOfArray)
{
	id_drops = 0;
	for (int i = 1; i < sizeOfArray; i++)
	{
		if (frames[i].getid() <= frames[i - 1].getid())
		{
			return false;
		}
		
		if ((frames[i].getid() - frames[i - 1].getid()) > 1)
		{
			id_drops++;
		}
	}
	return true;
};



int FrameDrops(frame* frames, int sizeOfArray, int frame_time)
{
	int drops = 0;
	long long differences = 0;
	long long expected_differences = (sizeOfArray - 1) * frame_time;

	for (int i = 1; i < sizeOfArray; i++)
	{
		auto tmp_diff = frames[i].getframe_TimeStamp() - frames[i - 1].getframe_TimeStamp();
		if (tmp_diff >= frame_time)
		{
			differences += tmp_diff;
		}
		else
		{
			cout << "***The time difference between the frames is not acceptable (less than the minimum)***\n";
			return -1;
		}
	}
	drops = ((differences - expected_differences) / frame_time);
	cout << "***expected_differences: " << expected_differences << "\n";
	cout << "***differences: " << differences << "\n";
	return drops;
};


void add_drops(frame* frames, int sizeOfArray,int index, int NumOfDrops, int frame_time)
{
	long long DelayTime = NumOfDrops * frame_time;
	for (int i = index; i < sizeOfArray + 1; i++)
	{
		frames[i].setframe_TimeStamp(frames[i].getframe_TimeStamp() + DelayTime);
	}
	return;
}





int main()
{
	int NumOfFrames = 10;					// the tottal number of the frames in the array  
	long long frame_time = 10;				// the frame time (per frame)
	int NumOfDrops = 3;						// the number of the drops that we want to add for check	
	int DropIndex = 5;						// The place we want Drop to be

	// Hello message
    std::cout << "frames Checking correctness program! \n(you can change the frame time, the num of frames,num of drops and the index in the main func)\n\n";

	// TEST the array in the correct form
    frame* my_frames= GenerateFramesArray(NumOfFrames, frame_time);
	std::cout << "***This is the Generated array in the correct form:\n";
	printFramesArray(my_frames , NumOfFrames);
	int drops = FrameDrops(my_frames, NumOfFrames, frame_time);
    bool tmp = FramesId_check(my_frames, NumOfFrames);
	cout << "***Num of id Drops: " << drops << "\n";
	cout << "***Num of Frame Drops: " << drops << "\n\n\n";


	// TEST the array that include drop 
	// the add drop function for check :
	add_drops(my_frames, NumOfFrames, DropIndex, NumOfDrops, frame_time);
	std::cout << "This is the Generated array with "<< NumOfDrops<<" drops: "<< "\n";
	printFramesArray(my_frames, NumOfFrames);
	drops = FrameDrops(my_frames, NumOfFrames, frame_time);
	cout << "***Num of Frame Drops: " << drops << "\n\n\n";



	

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
