#include <stdlib.h>
#include <inttypes.h>
#include <math.h>

//generates a random 64 bit number
uint64_t zurand(void)
{
	const int rand_size = __builtin_popcount(RAND_MAX);
	const int chunks = (64 + rand_size - 1) / rand_size;
	uint64_t ret = 0;

	for (short i = 0; i < chunks; i++)
		ret |= ((uint64_t)rand()<< (i * rand_size));
	return ret;
}

uint32_t urand(void)
{
	const int rand_size = __builtin_popcount(RAND_MAX);
	const int chunks = (32 + rand_size - 1) / rand_size;
	uint32_t ret = 0;

	for (short i = 0; i < chunks; i++)
		ret |= ((uint32_t)rand()<< (i * rand_size));
	return ret;
}
