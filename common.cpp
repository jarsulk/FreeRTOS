#include <iostream>
#include "common.h"

void blocked_wait(int ms)
{
	clock_t t1 = clock();
	while (clock() - t1 < ms) ; // CLOCKS_PER_SEC
}
