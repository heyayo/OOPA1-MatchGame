#ifdef _WIN32
#ifndef _TIMER_H
#define _TIMER_H

#include <windows.h>
#pragma comment(lib, "winmm.lib")

class StopWatch
{
 
 private:
     
    LARGE_INTEGER frequency;
    LARGE_INTEGER prevTime, currTime;
    double LIToSecs( LARGE_INTEGER & L) ;
    UINT     wTimerRes;

 public:
     StopWatch() ;
     ~StopWatch();
     void startTimer();
     double getElapsedTime(); // get time in seconds since the last call to this function
     void waitUntil(long long time);  // wait until this time in milliseconds has passed
 };


#endif // _TIMER_H
#elif __linux__

#include <time.h>

class StopWatch
{
    private:
    timespec last, now, elapsed;
    timespec res;
    double CalculateTime(timespec old, timespec young); // Function to handle calculating past'd time in seconds

    public:
    StopWatch();
    ~StopWatch();
    void startTimer();
    double getElapsedTime(); // Returns a variable of type timespec containing the nanoseconds as a long and seconds in int since the start of the timer
    void waitUntil(long long time);
};

#endif