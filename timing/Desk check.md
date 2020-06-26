Outer loop

`array: [4,3,7,9,2]  // original array`

`iteration: 1`

`k = 1`

`N= 5`

`low = 0`

`high = 4`

```c++
int start = low+1;   // start: 1
int stop = high;     // stop: 4
while( low < high )	 // 0 < 4
```



Inner loop

`array = [4,9,7,3,2]`

`start = 3`

`stop = 3​`



```c++
while (start < stop) 						  // start: 3 stop: 3 iteration #: 5 -- stop loop
{
  if (array[start] > array[low])  // 7 > 4
    ++start;         							// start: 3
  else if (array[stop] <= array[low]) //
    --stop; 											// stop:
  else
  {
    std::swap (array[start], array[stop]); // array[1] = 9 array[3] = 3 array[] = [4,9,7,3,2]
  }
}
```



`array =[4,9,7,3,2]`

`low = 0`

`high = 4`

`start = 3`

`stop = 3​`

`k = 1`

```c++
    	if (array[start] < array[low]) // 3 < 4   			
		    --start;	// start: 2														
    	std::swap (array[low], array[start]);   // array[0] = 7, array[2] = 4, array = [7,9,4,3,2]
    	// Check to see if the kth largest element is in [start], or
    	// in low..start-1 or in start+1..high.
    	if (start == k)    											// 2 == 1
    		low = high = k;												// low:, high:
    	else if (start > k)											// 2 > 1
    	{
    		// kth smallest must be somewhere in low..start-1
    		high = start - 1;											// high: 1
    	}
    	else
    	{
    		// kth smallest will be in start+1..high
    		low = start+1;												// low: 
    	}
```



`return = 3` -- wrong answer