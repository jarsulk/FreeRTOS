#include <iostream>
#include <cstring>
#include "FreeRTOS/include/FreeRTOS.h"
#include "FreeRTOS/include/task.h"
#include "FreeRTOS/include/semphr.h"
#include "common.h"
using namespace std;

#define TASK1_PRIORITY (tskIDLE_PRIORITY + 2)
#define TASK2_PRIORITY (tskIDLE_PRIORITY + 2)
#define TASK3_PRIORITY (tskIDLE_PRIORITY + 2)

static SemaphoreHandle_t semaphore1 = NULL;

static void semaphore1_task1(void* pvParameters);
static void semaphore1_task2(void* pvParameters);
static void semaphore1_task3(void* pvParameters);

void semaphore_1(void)
{
	cout << "semaphore1" << endl << endl;

	semaphore1 = xSemaphoreCreateBinary();
	xSemaphoreGive(semaphore1);
	
	xTaskCreate(semaphore1_task1, "task1", configMINIMAL_STACK_SIZE, NULL, TASK1_PRIORITY, NULL);
	xTaskCreate(semaphore1_task2, "task2", configMINIMAL_STACK_SIZE, NULL, TASK2_PRIORITY, NULL);
	xTaskCreate(semaphore1_task3, "task3", configMINIMAL_STACK_SIZE, NULL, TASK3_PRIORITY, NULL);
}

static void semaphore1_task1(void* pvParameters)
{
	while (true)
	{
		cout << "+";
		if (xSemaphoreTake(semaphore1, portMAX_DELAY) == pdTRUE)
		{
			//vTaskDelay(pdMS_TO_TICKS(500));
			blocked_wait(500);
			xSemaphoreGive(semaphore1);
			cout << "-";
		}
		//vTaskDelay(pdMS_TO_TICKS(500));
		blocked_wait(500);
	}
}

static void semaphore1_task2(void* pvParameters)
{
	while (true)
	{
		vTaskDelay(pdMS_TO_TICKS(100));
		if (xSemaphoreTake(semaphore1, portMAX_DELAY) == pdTRUE)
		{
			cout << ".";
			xSemaphoreGive(semaphore1);
		}
	}
}

static void semaphore1_task3(void* pvParameters)
{
	while (true)
	{
		vTaskDelay(pdMS_TO_TICKS(100));
		if (xSemaphoreTake(semaphore1, portMAX_DELAY) == pdTRUE)
		{
			cout << ",";
			xSemaphoreGive(semaphore1);
		}
	}
}
