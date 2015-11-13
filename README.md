A collection of small algorithms and data structures problems.
==============================================================
- [Counting Inversions](#counting-inversions)
- [Quick Sort](#quick-sort) 
- [Minimum Cut](#minimum-cut) 
- [Strongly Connected Components](#SCC) 

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

# <a name="SCC"></a>Strongly Connected Component
[Strongly Connected Component](http://www.columbia.edu/~cs2035/courses/csor4231.F15/scc.pdf) is another classic graph problem. It is defined on a graph that, within each SCC, there is one or more paths between any two vertices.

## Kosaraju's Two-pass Algorithm
Although this seems a rather complicated problem. The algorithm to compute SCC is surprisingly simple and efficient. It takes only **O(m + n)** (n means number of vertices and m means number of edges), just like normal DFS. The algorithm takes 3 major steps.

1. Create another directed graph with all arcs reversed.
2. Run DFS-Loop on the reversed graph. The detail of DFS-Loop is shown below.
3. Run a second pass DFS-Loop on the original graph.

```
DFS-Loop:
    Global t = 0
    Global s = NULL
    Assume the node is from 1 to n
    For i from 1 to n
        if i not yet explored
            s = i
            run DFS on i
```
Here the DFS is just like a normal DFS. However, when there is no more children to explore for a node, we need to increment the finish time t and keep record of the finish time for every node.

## Problem
Given a fairly large graph, we are asked to compute the strongly connected components and output the number of nodes in the 5 largest SCCs. The input file consists of a LOT of lines where each line represents a edge (u, v). The total number of vertices in this graph is 875714. So while the algorithm does not seem complicated at all, the tricky part is the implementation.

In my implementation, I use a vector of vector<int> to represent a graph adjacent list. Some other data like finish time, explored array, visiting sequence are represented using arrays. My first trial is just to use the recursive DFS algorithm. However it runs out of memory given the graph is too large. So I change to an iterative implementation. But we need some minor modification on the original algorithm. For example, we cannot pop the vertex out of the stack only all of its children has been explored. We need to set the explored bit to be true when it is pushed into the stack, not when it is actually explored. This is to prevent that we add the same vertex more than once onto the stack before it has chance to be **actually** explored.

As usual, with the gcc -O3 compilation flags, my code takes about 6 seconds to run, where more than 5 seconds are spent on reading input. Maybe I should learn a way to speed up this process.
