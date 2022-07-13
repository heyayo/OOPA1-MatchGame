#ifdef _WIN32
#include "timer.hpp"

/*
OpenGL Framework Timer Class
The Windows Version is Written By Mr Stanley
Linux Version adapted by me
*/

StopWatch::StopWatch()
{    
    QueryPerformanceFrequency( &frequency ) ;

    #define TARGET_RESOLUTION 1         // 1-millisecond target resolution
    TIMECAPS tc;
    

    if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) 
    {
        // Error; application can't continue.
    }

    wTimerRes = min(max(tc.wPeriodMin, TARGET_RESOLUTION), tc.wPeriodMax);
    timeBeginPeriod(wTimerRes); 
}

StopWatch::~StopWatch()
{
    timeEndPeriod(wTimerRes);
}

double StopWatch::LIToSecs( LARGE_INTEGER & L) {
     return ((double)L.QuadPart /(double)frequency.QuadPart) ;
 }
 
void StopWatch::startTimer( )
{
    QueryPerformanceCounter(&prevTime) ;
}
 
double StopWatch::getElapsedTime() 
{
    LARGE_INTEGER time;
    QueryPerformanceCounter(&currTime) ;
    time.QuadPart = currTime.QuadPart - prevTime.QuadPart;
    prevTime = currTime;
    return LIToSecs( time) ;
}

void StopWatch::waitUntil(long long time)
{
    LARGE_INTEGER nowTime;
    LONGLONG timeElapsed;
    while (true)
    {
        QueryPerformanceCounter(&nowTime);
        timeElapsed = ((nowTime.QuadPart - prevTime.QuadPart) * 1000 / frequency.QuadPart);
        if (timeElapsed > time)
            return;
        else if (time - timeElapsed > 1)
            Sleep(1);
    }
}

#elif __linux__
#include "timer.h"

StopWatch::StopWatch()
{
    clock_getres(CLOCK_MONOTONIC, &res); // Get the Resolution of the Clock
}

StopWatch::~StopWatch() {}

void StopWatch::startTimer()
{
    clock_gettime(CLOCK_MONOTONIC, &last);
}

double StopWatch::getElapsedTime()
{
    clock_gettime(CLOCK_MONOTONIC, &now);
    double elapsed = CalculateTime(last,now);
    last = now;
    return elapsed * 1000;
}

void StopWatch::waitUntil(long long time)
{
    timespec NowTime;
    timespec LastTime;
    clock_gettime(CLOCK_MONOTONIC, &LastTime);
    long ElaspedTime;
    while (true)
    {
        clock_gettime(CLOCK_MONOTONIC, &NowTime);
        ElaspedTime = CalculateTime(LastTime,NowTime) * 1000;
        if (ElaspedTime > time)
            return;
    }
}

double StopWatch::CalculateTime(timespec old, timespec young)
{
    timespec elapse;
    elapse.tv_sec = young.tv_sec - old.tv_sec;
    elapse.tv_nsec = young.tv_nsec - old.tv_nsec;
    return (double)elapse.tv_sec + ((double)elapse.tv_nsec / 1000000000);
}

#endif