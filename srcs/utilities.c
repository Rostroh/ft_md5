#include "ft_ssl.h"

uint32_t		left_rot(uint32_t byte, int n)
{
	return ((byte << n) | (byte >> (BYTE_SIZE - n)));
}

uint32_t		right_rot(uint32_t byte, int n)
{
	return ((byte >> n) | (byte << (BYTE_SIZE - n)));
}
