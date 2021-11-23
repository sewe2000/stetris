#include "../include/functions.hpp"

void shift_bits(std::bitset<160>& bits, int deleted_row)
{
	if(deleted_row == 15)
	{
		bits <<= 10;
		return;
	}
	for(int i = deleted_row * 10 - 1; i >= 0; i--)	
	{
		
		bits[i + 10] = static_cast<bool>(bits[i]);
		bits[i] = false;
	}

}
