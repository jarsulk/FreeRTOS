#include <iostream>
#include <cstring>
#include "FreeRTOS/include/FreeRTOS.h"
#include "FreeRTOS/include/task.h"
#include "common.h"
using namespace std;

#define mainREGION_1_SIZE                     8201
#define mainREGION_2_SIZE                     23905
#define mainREGION_3_SIZE                     16807

static void prvInitialiseHeap(void);

int main()
{
	prvInitialiseHeap();

	//semaphore_1();
	//task_1();
	//queue_1();
	//timer_1();
	message_buffer_1();

	vTaskStartScheduler();
}

static void prvInitialiseHeap(void)
{
	/* The Windows demo could create one large heap region, in which case it would
	 * be appropriate to use heap_4.  However, purely for demonstration purposes,
	 * heap_5 is used instead, so start by defining some heap regions.  No
	 * initialisation is required when any other heap implementation is used.  See
	 * http://www.freertos.org/a00111.html for more information.
	 *
	 * The xHeapRegions structure requires the regions to be defined in start address
	 * order, so this just creates one big array, then populates the structure with
	 * offsets into the array - with gaps in between and messy alignment just for test
	 * purposes. */
	static uint8_t ucHeap[configTOTAL_HEAP_SIZE];
	volatile uint32_t ulAdditionalOffset = 19; /* Just to prevent 'condition is always true' warnings in configASSERT(). */
	const HeapRegion_t xHeapRegions[] =
	{
		/* Start address with dummy offsets						Size */
		{ ucHeap + 1,                                          mainREGION_1_SIZE },
		{ ucHeap + 15 + mainREGION_1_SIZE,                     mainREGION_2_SIZE },
		{ ucHeap + 19 + mainREGION_1_SIZE + mainREGION_2_SIZE, mainREGION_3_SIZE },
		{ NULL,                                                0                 }
	};

	/* Sanity check that the sizes and offsets defined actually fit into the array. */
	configASSERT((ulAdditionalOffset + mainREGION_1_SIZE + mainREGION_2_SIZE + mainREGION_3_SIZE) < configTOTAL_HEAP_SIZE);

	/* Prevent compiler warnings when configASSERT() is not defined. */
	(void)ulAdditionalOffset;

	vPortDefineHeapRegions(xHeapRegions);
}

void vApplicationMallocFailedHook(void)
{
	cout << "Malloc failed hook\n";
}

/*
	Projekt > Właściwości:
		C/C++ > Ogólne > Dodatkowe katalogi plików nagłówkowych: FREERTOS\Include;.
		C/C++ > Preprocesor > Definicje preprocesora: _CRT_SECURE_NO_WARNINGS
	CTRL+C exception: https://stackoverflow.com/a/1320721
*/
