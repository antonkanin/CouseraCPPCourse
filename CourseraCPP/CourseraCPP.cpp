//#include "pch.h"
#include <iostream>

using namespace std;

int main()
{
	unsigned int numberOfBlocks, density;

	cin >> numberOfBlocks >> density;

	uint64_t sum = 0;

	for (unsigned i = 0; i < numberOfBlocks; ++i)
	{
		uint64_t W, H, D;
		cin >> W >> H >> D;

		sum += W * H * D * density;
	}


	cout << sum << endl;
	
	return 0;
}
