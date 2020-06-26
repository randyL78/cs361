
#include <algorithm>
#include <iostream>

using namespace  std;


/**
 * Finds the kth largest value in an array.
 */
int kthLargest (int* array,  int N, int k)
{
    int low = 0;
    int high = N-1;

    while( low < high )
    {
    	int start = low+1;
    	int stop = high;
    	// Find all dividing point (start) in the array such that
    	// all elements in low..start are larger than all
    	// elements in start+1..high
    	while (start < stop)
    	{
    		if (array[start] > array[low])
    			++start;
    		else if (array[stop] <= array[low])
    			--stop;
    		else
    		{
    			std::swap (array[start], array[stop]);
    		}
    	}
    	if (array[start] < array[low])
		    --start;
    	std::swap (array[low], array[start]);
    	// Check to see if the kth largest element is in [start], or
    	// in low..start-1 or in start+1..high.
    	if (start == k)
    		low = high = k;
    	else if (start > k)
    	{
    		// kth smallest must be somewhere in low..start-1
    		high = start - 1;
    	}
    	else
    	{
    		// kth smallest will be in start+1..high
    		low = start+1;
    	}
    }
    return array[low];
}
