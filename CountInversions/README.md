# Counting Inversion Problem
This problem asks us to compute the number of inversions in an large array. For example, array `{1, 3, 5, 2, 4, 6}` has exactly three inversions.

# Solutions
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

