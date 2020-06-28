# Timing Assignment

## Analysis

### Worst Case

```c++
int kthLargest (int* array,  int N, int k)
{
    int low = 0;              // O(1)
    int high = N-1;           // O(1)

    while( low < high )       // cond: O(1) 
    {
    	int start = low+1;      // O(1)
    	int stop = high;        // O(1)
    	while (start < stop)
    	{
    		if (array[start] > array[low])  // cond: O(1)
    			++start;            // O(1)
    		else if (array[stop] <= array[low]) // cond: O(1)
    			--stop;             // O(1)
    		else
    		{
    			std::swap (array[start], array[stop]); // O(1)
    		}
    	}
    	if (array[start] < array[low])  					 // cond: O(1)
		    --start;              // O(1)
    	std::swap (array[low], array[start]);      // O(1)
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
    return array[low];				// O(1)
}
```



Evaluate condition block from lines 14-19 and then 12-19:
$$
\begin{align*}
t_{if} &=  O(1) + max(O(1), O(1)) \\
&= O(1 + 1) \\
&= O(1) \\
\end{align*}
$$


```c+
    		...
    		if (array[start] > array[low])  // cond: O(1)
    			++start;            // O(1)
    		else if (array[stop] <= array[low]) // cond: O(1) total: O(1)
    			--stop;             // O(1)
    		else
    		{
    			std::swap (array[start], array[stop]); // O(1)
    		}
    		...
```

Collapse 

```c++
    		...
    		if (array[start] > array[low])  // cond: O(1)
    			++start;            // O(1)
    		else 
          // O(1)
    		...
```

Evaluate
$$
\begin{align*}
t_{if} &=  O(1) + max(O(1), O(1)) \\
&= O(1 + 1) \\
&= O(1) \\
\end{align*}
$$
Collapse

```c++
int kthLargest (int* array,  int N, int k)
{
    int low = 0;              // O(1)
    int high = N-1;           // O(1)

    while( low < high )				// cond: O(1) 
    {
    	int start = low+1;      // init: O(1)
    	int stop = high;        // init: O(1)
    	while (start < stop)		// cond: O(1) body: O(1) #: distance(start, stop) 
    	{
    		if (array[start] > array[low])  		// cond: O(1) total: O(1)
    	}
    	if (array[start] < array[low])  			// cond: O(1)
		    --start;              // O(1)
    	std::swap (array[low], array[start]); // O(1)
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
    return array[low];				// O(1)
}
```



Evaluate `while` loop from lines 10-13
$$
\begin{align*}
t_{while} &= O(1) + \sum_{i = start}^{stop} (O(1) + O(1) + O(1)) \\
&= O(1) + O(distance(start, stop) * (O(1) + O(1) + O(1)) \\
&= O(1) + O(distance(start, stop)) \\
&= O(distance(start, stop)
\end{align*}
$$

```c++
int kthLargest (int* array,  int N, int k)
{
    int low = 0;              // O(1)
    int high = N-1;           // O(1)

    while( low < high )				// cond: O(1)
    {
    	int start = low+1;      // init: O(1)
    	int stop = high;        // init: O(1)
    	while (start < stop)		// cond: O(1) body: O(1) #: distance(start, stop) total: O(distance(start, stop)

    	if (array[start] < array[low])  			// cond: O(1)
		    --start;              // O(1)
    	std::swap (array[low], array[start]); // O(1)
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
    return array[low];				// O(1)
```

Collapsing loop:

```c++
int kthLargest (int* array,  int N, int k)
{
    int low = 0;              // O(1)
    int high = N-1;           // O(1)

    while( low < high )
    {
    	int start = low+1;      // init: O(1)
    	int stop = high;        // init: O(1)
    	// O(distance(start, stop)

    	if (array[start] < array[low])  			// cond: O(1)
		    --start;              // O(1)
    	std::swap (array[low], array[start]); // O(1)
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
    return array[low];				// O(1)
```

Evaluate condition block from lines 12-13:
$$
\begin{align*}
t_{if} &=  O(1) + max(O(1), O(1)) \\
&= O(1 + 1) \\
&= O(1) \\
\end{align*}
$$
And collapsing



```c++
int kthLargest (int* array,  int N, int k)
{
    int low = 0;              // O(1)
    int high = N-1;           // O(1)

    while( low < high )
    {
    	int start = low+1;      // init: O(1)
    	int stop = high;        // init: O(1)
    	// O(distance(start, stop)

    	if (array[start] < array[low])  			// cond: O(1) total: O(1)
    	
      std::swap (array[low], array[start]); // O(1)
    	if (start == k)
    		low = high = k;       // O(1)
    	else if (start > k)     // cond: O(1)
    	{
    		high = start - 1;     // O(1)
    	}
    	else
    	{
    		low = start+1;        // O(1)
    	}
    }
    return array[low];				// O(1)
```

Evaluate condition block from lines 17-24 and then 15-24:
$$
\begin{align*}
t_{if} &= O(1) + max(O(1), O(1)) \\
&= O(1) + O(1)   \\
&= O(1)
\end{align*}
$$

```c++
...
			if (start == k)
    		low = high = k;       // O(1)
    	else if (start > k)     // cond: O(1) total: O(1)
    	{
    		high = start - 1;     // O(1)
    	}
    	else
    	{
    		low = start+1;        // O(1)
    	}
...
```



Collapse 17-24

```c++
...    	
			if (start == k)
    		low = high = k;       // O(1)
    	else
        // O(1)
...
```

Evaluate
$$
\begin{align*}
t_{if} &= O(1) + max(O(1), O(1)) \\
&= O(1) + O(1)   \\
&= O(1)
\end{align*}
$$
Collapse

```c++
int kthLargest (int* array,  int N, int k)
{
    int low = 0;              // O(1)
    int high = N-1;           // O(1)

    while( low < high )
    {
    	int start = low+1;      // init: O(1)
    	int stop = high;        // init: O(1)
    	// O(distance(start, stop)

    	if (array[start] < array[low])  			// total: O(1)
		    --start;              // O(1)
    	std::swap (array[low], array[start]); // O(1)
    	if (start == k) 				// total: O(1)
    }
    return array[low];				// O(1)
```

Sum `while` body and replace start/stop on line 10 with low+1 and high respectively.
$$
\begin{align}
t_{body} &= O(1 + 1 + distance(low + 1, high) + 1 + 1 + 1) \\
&= O(distance(low, high))
\end{align}
$$


```c++
int kthLargest (int* array,  int N, int k)
{
    int low = 0;              // init: O(1)
    int high = N-1;           // init: O(1)
    while( low < high )
   	// body: O(distance(low, high))
    return array[low];				// O(1)
```

Evaluate `while` loop
$$
\begin{align}
t_{while} &= O(1) + O(1) + \sum_{i = 0}^{N-1} (O(distance(0, N-1))) \\
&=O(1 + 1 + N^2) \\
&=O(N^2) \\
\end{align}
$$

```c++
int kthLargest (int* array,  int N, int k)
  total: O(N^2)
```

**Worst case complexity of `kthLargest`$= O(N^2)$**



### Average Case



```c++
int kthLargest (int* array,  int N, int k)
{
    int low = 0;              // O(1)
    int high = N-1;           // O(1)

    while( low < high )       // cond: O(1) #: N-1
    {
    	int start = low+1;      // O(1)
    	int stop = high;        // O(1)
    	while (start < stop)
    	{
    		if (array[start] > array[low])  // cond: O(1)
    			++start;            // O(1)
    		else if (array[stop] <= array[low]) // cond: O(1)
    			--stop;             // O(1)
    		else
    		{
    			std::swap (array[start], array[stop]); // O(1)
    		}
    	}
    	if (array[start] < array[low])  					 // cond: O(1)
		    --start;              // O(1)
    	std::swap (array[low], array[start]);      // O(1)
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
    return array[low];				// O(1)
}
```

Evaluate condition block from lines 14-19 and then 12-19:

Since both the `if` and `else` portions are $O(1)$ we don't need to figure the average here.


```c+
    		...
    		if (array[start] > array[low])  // cond: O(1)
    			++start;            // O(1)
    		else if (array[stop] <= array[low]) // cond: O(1) total: O(1)
    			--stop;             // O(1)
    		else
    		{
    			std::swap (array[start], array[stop]); // O(1)
    		}
    		...
```

Collapse 

```c++
    		...
    		if (array[start] > array[low])  // cond: O(1)
    			++start;            // O(1)
    		else 
          // O(1)
    		...
```

Evaluate

Since both the `if` and `else` portions are $O(1)$ we don't need to figure the average here.

Collapse

```c++
int kthLargest (int* array,  int N, int k)
{
    int low = 0;              // O(1)
    int high = N-1;           // O(1)

    while( low < high )
    {
    	int start = low+1;      // init: O(1)
    	int stop = high;        // init: O(1)
    	while (start < stop)		// cond: O(1) body: O(1)
    	{
    		if (array[start] > array[low])  		// cond: O(1) total: O(1)
    	}
    	if (array[start] < array[low])  			// cond: O(1)
		    --start;              // O(1)
    	std::swap (array[low], array[start]); // O(1)
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
    return array[low];				// O(1)
}
```



The inner while loop will still have to iterate over each item regardless of the data distribution just like it did for the worst case scenario, so:
$$
\begin{align*}
t_{while} &= O(1) + \sum_{i = start}^{stop} (O(1) + O(1) + O(1)) \\
&= O(1) + O(distance(start, stop) * (O(1) + O(1) + O(1)) \\
&= O(1) + O(distance(start, stop)) \\
&= O(distance(start, stop)
\end{align*}
$$
**Important Note** before collapsing:

* Assuming that an average array will be unsorted
*  There will be on average an even mix of numbers that are greater than and less than the first number in the array
* Therefore, on average, `start` will finish the loop roughly halfway through the array.

Collapsing: 

```c++
int kthLargest (int* array,  int N, int k)
{
    int low = 0;              // O(1)
    int high = N-1;           // O(1)

    while( low < high )
    {
    	int start = low+1;      // init: O(1)
    	int stop = high;        // init: O(1)
    	while (start < stop)		// cond: O(1) body: O(1) #: distance(start, stop) total: O(distance(start, stop))
    	if (array[start] < array[low])  			// cond: O(1)
		    --start;              // O(1)
    	std::swap (array[low], array[start]); // O(1)
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
    return array[low];				// O(1)
}
```

 The conditionals from 11-12, 16-23, and 14-23 still run in constant time as well, so for each of those:
$$
\begin{align*}
t_{if} &=  O(1) + max(O(1), O(1)) \\
&= O(1 + 1) \\
&= O(1) \\
\end{align*}
$$
**Another Note** before collapsing:

* As stated previously, `start` on average will be at roughly the midpoint in the array when reaching these conditionals.
* This means that whether `start > k` or `start < k`, we will end up with roughly half of the elements in the array for the next iteration of the outer loop.

Collapsing:

```c++
int kthLargest (int* array,  int N, int k)
{
    int low = 0;              // O(1)
    int high = N-1;           // O(1)

    while( low < high )
    {
    	int start = low+1;      // init: O(1)
    	int stop = high;        // init: O(1)
    	// total: O(distance(start, stop))
 			// total: O(1)
    	std::swap (array[low], array[start]); // O(1)
			// total: O(1)
    }
    return array[low];				// O(1)
}
```

For lines 7-14 we can collapse and replace the `start` and `stop` values of the inner while assesment with `low + 1` and `high`.
$$
\begin{align*}
O(distance(start, stop)) &= O(distance(low+1, high)) \\
&= O(distance(low, high))
\end{align*}
$$

```c++
int kthLargest (int* array,  int N, int k)
{
    int low = 0;              // O(1)
    int high = N-1;           // O(1)

    while( low < high ) // cond: O(1)
   	// body: O(distance(low, high))
    return array[low];				// O(1)
}
```

As noted earlier, the array in each iteration on average will be half the size of the previous iteration. This leads to the conclusion that it will be logarithmic in nature. Since `low` and `high` are initialled as `0` and `N - 1` immediately before the loop, we can go ahead and make the substitutions in and declare that the loop will repeat `log N ` times.
$$
\begin{align*}
\# of iterations &= O(log(distance(low, high))) \\
&= O(log(distance(0, N - 1))) \\
&= O(log(distance(0, N))) \\
&= O(log N)
\end{align*}
$$
Similarly we can substitute in `N` for the body of the loop as well:
$$
\begin{align*}
body &= O(distance(low, high)) \\
&= O(distance(0, N - 1)) \\
&= O(distance(0, N)) \\
&= O(N)
\end{align*}
$$


```c++
int kthLargest (int* array,  int N, int k)
{
    int low = 0;              // O(1)
    int high = N-1;           // O(1)

    while( low < high ) // cond: O(1) body: O(N) #: log N total: N log N
    return array[low];				// O(1)
}
```

Summing up the remaining sequential statements:
$$
\begin{align*}
total &= O(1 + 1 + N log N + 1) \\
&= O(N log N)
\end{align*}
$$
**Therefore, the average case complexity of kthLargest is O(N log N)**

## Conclusions

After performing time tests on the algorithm, the actual run times fell in between the worst case analysis and the best case analysis; however, it did tend to run much closer to the worst case. Because of this, I do feel that the actual performance does support the predicted complexity overall. To be sure I had properly bracketed the function, even though the worst case did have a slightly downward trending slope, I chose a slightly larger function of $N^2 log N$ to ensure that it's slope was a true downward slope ratio with time.

I do think that the average case should have been the one that ran closer to actual times. I feel part of the reason for the discrepancy is that the average case treats a random array as being balanced between lower and higher numbers than the first being evenly dispersed between both half of the array. While this may hold more or less true on average, I think that anything outside of perfectly balanced has a great effect on the runtime.