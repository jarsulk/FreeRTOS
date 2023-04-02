#include <iostream>
#include <cstring>
#include "FreeRTOS/include/FreeRTOS.h"
#include "FreeRTOS/include/timers.h"
#include "common.h"
using namespace std;

static TimerHandle_t timer1 = NULL;
static TimerHandle_t timer2 = NULL;
static TimerHandle_t timer3 = NULL;
static int timerid1 = 1;
static int timerid2 = 2;
static int timerid3 = 3;

static void timer1_timer1Callback(TimerHandle_t xTimer);
static void timer1_timer2Callback(TimerHandle_t xTimer);
static void timer1_timer3Callback(TimerHandle_t xTimer);

void timer_1(void)
{
	cout << "timer1" << endl << endl;
	timer1 = xTimerCreate("timer1", pdMS_TO_TICKS(1000), pdTRUE, (void*)(&timerid1), timer1_timer1Callback);
	timer2 = xTimerCreate("timer2", pdMS_TO_TICKS(1000), pdTRUE, (void*)(&timerid2), timer1_timer2Callback);
	timer3 = xTimerCreate("timer3", pdMS_TO_TICKS(1000), pdTRUE, (void*)(&timerid3), timer1_timer3Callback);
	xTimerStart(timer1, portMAX_DELAY);
	xTimerStart(timer2, portMAX_DELAY);
	xTimerStart(timer3, portMAX_DELAY);
}

static void timer1_timer1Callback(TimerHandle_t xTimer)
{
	int* timerid;
	timerid = (int*)pvTimerGetTimerID(xTimer);
	cout << *timerid;
}

static void timer1_timer2Callback(TimerHandle_t xTimer)
{
	int* timerid;
	timerid = (int*)pvTimerGetTimerID(xTimer);
	cout << *timerid;
}

static void timer1_timer3Callback(TimerHandle_t xTimer)
{
	int* timerid;
	timerid = (int*)pvTimerGetTimerID(xTimer);
	cout << *timerid;
}
