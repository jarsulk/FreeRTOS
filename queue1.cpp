#include <iostream>
#include <cstring>
#include "FreeRTOS/include/FreeRTOS.h"
#include "FreeRTOS/include/task.h"
#include "FreeRTOS/include/queue.h"
#include "common.h"
using namespace std;

#define TASK1_PRIORITY (tskIDLE_PRIORITY + 2)
#define TASK2_PRIORITY (tskIDLE_PRIORITY + 2)
#define TASK3_PRIORITY (tskIDLE_PRIORITY + 2)

static QueueHandle_t queue1 = NULL;
static QueueHandle_t queue2 = NULL;

static void queue1_task1(void* pvParameters);
static void queue1_task2(void* pvParameters);
static void queue1_task3(void* pvParameters);

void queue_1(void)
{
	cout << "queue1" << endl << endl;

	const auto QueeSize = 3;
	queue1 = xQueueCreate(QueeSize, sizeof(char));
	queue2 = xQueueCreate(QueeSize, sizeof(char));

	xTaskCreate(queue1_task1, "task1", configMINIMAL_STACK_SIZE, NULL, TASK1_PRIORITY, NULL);
	xTaskCreate(queue1_task2, "task2", configMINIMAL_STACK_SIZE, NULL, TASK2_PRIORITY, NULL);
	xTaskCreate(queue1_task3, "task3", configMINIMAL_STACK_SIZE, NULL, TASK3_PRIORITY, NULL);
}

static void queue1_task1(void* pvParameters)
{
	char a = 0;
	char b = 0;
	while (true)
	{
		//a = rand() % 256;
		xQueueSend(queue1, &a, portMAX_DELAY);
		cout << "s1 " << (int)a << endl;
		a++;

		//b = rand() % 256;
		xQueueSend(queue2, &b, portMAX_DELAY);
		cout << "s2 " << (int)b << endl;
		b++;

		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

static void queue1_task2(void* pvParameters)
{
	while (true)
	{
		char a;
		xQueueReceive(queue1, &a, portMAX_DELAY);
		cout << "  r1 " << (int)a << endl;
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

static void queue1_task3(void* pvParameters)
{
	while (true)
	{
		char a;
		xQueueReceive(queue2, &a, portMAX_DELAY);
		cout << "  r2 " << (int)a << endl;
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}
