A collection of small algorithms and data structures problems.
==============================================================
- [Counting Inversions](#counting-inversions)
- [Quick Sort](#quick-sort) 
- [Minimum Cut](#minimum-cut) 

# <a name="counting-inversions"></a>Counting Inversions
This problem asks us to compute the number of inversions in an large array. For example, array `{1, 3, 5, 2, 4, 6}` has exactly three inversions.

## Brute-force
Brute-force is a native way to solve the problem. However, it takes `O(n^2)` steps to get the answers.

## Divide and Conquer
This solution uses the Divide and Conquer paradiagm and the running time is `O(nlog(n))`. Actually, can consider it as a variation of merge sort.

Recall that in merge sort, we do something like this

--recursively sort 1st half of the input array 

--recursively sort 2nd half of the input array

--merge two sorted sublists into one

Now, we change the merge part to count inv for two subarrays. Then we have,

--recursively sort and count 1st half of the input array, output B

--recursively sort and count 2nd half of the input array, output C

--count inversions for B and C

--return the total number of inversions returned by the above three calls

Inside the function for counting inversions for B and C, if the number from B is smaller than number from C, we simply copy it to output array D. If the number from B is larger than the number from C, we know we have inversions here. Since each array B and C is in order, the number of inversion for this particular case is the length of B - the position of current number in B.


# <a name="quick-sort"></a>Quick Sort
This problem ask us to calculate the total number of comparisons used in quicksort. In particular, we use this statistics to compare different pivot selection strategy.

## Three pivot selection strategy
The three experiemental strategies are first-element, last-element and median-of-three. The first two just use the first or last element in each subarray as the pivot, while the last strategy takes the median of the first, last and middle element as pivot.

We use the file QuickSort.txt as testcase. It contains an array of unique numbers from 1 to 10000. As a result, median-of-three is clearly a better strategy. It tries harder to pivot closer to median, which will partition the array into two even halves.

The results are
* first-element: 162085 comparisons
* last-element: 164123 comparisons 
* median-of-three: 138382 comparisons 

# <a name="minimum-cut"></a>Minimum Cut
Minimum cut is a classic graph problem that ask us to divide a graph into two halves with minimum crossing edges between the two parts.

Consider a graph
```
1 -- 2 -- 5 -- 6
| \/ |    | \/ |
| /\ |    | /\ |
3 -- 4 -- 7 -- 8
```
the min-cut is (2, 5), (4, 7) with two crossing edges.

## Karger's algorithm
[Karger's algorithm](https://en.wikipedia.org/wiki/Karger%27s_algorithm) is a randomized algorithm to solve minimum cut problem. The algorithm can be described as follows:

While there are more than 2 vertices:
* pick a remaining edge (u,v) uniformly at random
* merge (or “contract” ) u and v into a single vertex
* remove self-loops
return cut represented by final 2 vertices. 

It is randomized, meaning that it does guarantee to give the correct solution each iteration. In fact, the probabilty that it gives the correct answer in one run is `only` 1 / (n ^ 2). This seems to be a small number, but with large number of iterations of this algorithm (n ^ 2), we have a pretty large probabilty to get the right answer `(n - 1) / n`

## Problem
In this problem, we are to calculate the number of crossing edges when we get a min-cuts on a graph with 200 vertices. In my implementation, I am too lazy to keep track of the union of vertices.
So in my program it can only output the number of minimum crossing edges without the actual edges.

To reduce the amount of memory used, I don't store the graph as adjacent lists but a list of edge, with each edge represented by a pair<int, int>. In each contraction step, I randomly choose an edge and merge the two vertices connected by that edge. Then I update the edge lists. After V - 2 contraction steps, where V is the number of vertices, we can just count the left edges to get the number of crossing edges in this cut. 

Above is not my first implementation, in my first implementation, I tried to use adjacent list to solve this problem. I generated two random connected vertices at a time and remove one of them. This is a valid solution for small test cases, but it is not feasible for solving the 200 vertices case. Then I realized that choosing a random vertex is a BAD strategy. We should choose a random edge instead. Consider this, if we choose a random vertex, it is likely that it is one of the vertex on the min cut. However, if we choose a random edge, given that we have many more edges than vertices, the probabilty that this edge is on the min cut is a lot smaller. This is the reason that in my previous attempt, even though I run my solver for over 10000 iterations, it is not possible to find the global minimum cut.

To summarize, this is definitely not a super efficient implementation. But I am able to get roughly 0.004 sec per iteration. With roughly 100 iterations, it can almost always find the correct answer. So I guess I'll just stop here.
