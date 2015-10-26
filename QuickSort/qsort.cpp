#include <iostream>

class QuickSort 
{
public:
    void sort(int* A, int n, int (*choose_pivot)(int*, int))
    {
        if (n == 1)
            return;
        int p = *choose_pivot(A, n);
    }

private:

}
