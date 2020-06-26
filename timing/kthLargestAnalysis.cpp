int kthLargest (int* array,  int N, int k)
{
    int low = 0;              // O(1)
    int high = N-1;           // O(1)

    while( low < high )
    {
    	int start = low+1;      // O(1)
    	int stop = high;        // O(1)
    	while (start < stop)
    	{
    		if (array[start] > array[low])
    			++start;            // O(1)
    		else if (array[stop] <= array[low])
    			--stop;             // O(1)
    		else
    		{
    			std::swap (array[start], array[stop]); // O(distance(start, stop))
    		}
    	}
    	if (array[start] < array[low])
		    --start;              // O(1)
    	std::swap (array[low], array[start]);      // O(distance(low, stop))
    	if (start == k)
    		low = high = k;       // O(1)
    	else if (start > k)
    	{
    		high = start - 1;     // O(1)
    	}
    	else
    	{
    		low = start+1;        // O(1)
    	}
    }
    return array[low];
}