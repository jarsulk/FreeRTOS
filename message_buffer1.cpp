#include <iostream>
#include <cstring>
#include "FreeRTOS/include/FreeRTOS.h"
#include "FreeRTOS/include/task.h"
#include "FreeRTOS/include/message_buffer.h"
#include "common.h"
using namespace std;

#define TASK1_PRIORITY (tskIDLE_PRIORITY + 2)
#define TASK2_PRIORITY (tskIDLE_PRIORITY + 2)

static const size_t MessageBufferSizeBytes = 64;

static MessageBufferHandle_t messageBuffer = NULL;

static void message_buffer1_task1(void* pvParameters);
static void message_buffer1_task2(void* pvParameters);

void message_buffer_1(void)
{
	cout << "message_buffer1" << endl << endl;

	messageBuffer = xMessageBufferCreate(MessageBufferSizeBytes + 8);
	cout << "spacees available " << xMessageBufferSpacesAvailable(messageBuffer) << endl;

	xTaskCreate(message_buffer1_task1, "task1", configMINIMAL_STACK_SIZE, NULL, TASK1_PRIORITY, NULL);
	xTaskCreate(message_buffer1_task2, "task2", configMINIMAL_STACK_SIZE, NULL, TASK2_PRIORITY, NULL);
}

static void message_buffer1_task1(void* pvParameters)
{
	uint8_t i = 1;
	uint8_t tx[MessageBufferSizeBytes];
	memset(tx, sizeof(tx), 0);
	while (true)
	{
		tx[0] = i++;
		size_t sent = xMessageBufferSend(messageBuffer, tx, sizeof(tx), portMAX_DELAY);
		cout << "S " << sent << ": " << (int)tx[0] << endl;
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

static void message_buffer1_task2(void* pvParameters)
{
	uint8_t rx[MessageBufferSizeBytes];
	memset(rx, sizeof(rx), 0);
	while (true)
	{
		size_t received = xMessageBufferReceive(messageBuffer, rx, sizeof(rx), portMAX_DELAY);
		cout << "R " << received << ": " << (int)rx[0] << endl;
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}
