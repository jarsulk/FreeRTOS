#include <iostream>
#include <cstring>
#include "FreeRTOS/include/FreeRTOS.h"
#include "FreeRTOS/include/task.h"
#include "common.h"
using namespace std;

#define TASK1_PRIORITY (tskIDLE_PRIORITY + 2)
#define TASK2_PRIORITY (tskIDLE_PRIORITY + 2)
#define TASK3_PRIORITY (tskIDLE_PRIORITY + 2)

static void task1_task1(void* pvParameters);
static void task1_task2(void* pvParameters);
static void task1_task3(void* pvParameters);

void task_1(void)
{
	cout << "task1" << endl << endl;
	xTaskCreate(task1_task1, "task1", configMINIMAL_STACK_SIZE, NULL, TASK1_PRIORITY, NULL);
	xTaskCreate(task1_task2, "task2", configMINIMAL_STACK_SIZE, NULL, TASK2_PRIORITY, NULL);
	xTaskCreate(task1_task3, "task3", configMINIMAL_STACK_SIZE, NULL, TASK3_PRIORITY, NULL);
}

static void task1_task1(void* pvParameters)
{
	while (true)
	{
		cout << "1";
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

static void task1_task2(void* pvParameters)
{
	while (true)
	{
		cout << ".";
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

static void task1_task3(void* pvParameters)
{
	while (true)
	{
		cout << ",";
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}
