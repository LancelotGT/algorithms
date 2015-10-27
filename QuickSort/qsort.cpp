#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;
class QuickSort 
{
public:
    QuickSort() : count(0)
    {
    }

    void sort(int* A, int start, int end, int (*choose_pivot)(int*, int, int))
    {
        int len = end - start + 1;
        if (len <= 1)
            return;
        int p = (*choose_pivot)(A, start, end);
        int p_after = partition(A, start, end, p);
        sort(A, start, p_after - 1, choose_pivot);
        sort(A, p_after + 1, end, choose_pivot); 
    }

    int getCount() { return count; }

private:
    int count;
    int partition(int* A, int start, int end, int p)
    {
        int len = end - start + 1;
        this->count += (len - 1);
        int pivot = A[p];
        swap(A, start, p);
        int i = start + 1;
        for (int j = start + 1; j <= end; j++)
        {
            if (A[j] < pivot)
            {
                swap(A, j, i);
                i++;
            }
        }
        swap(A, start, i - 1);
        return i - 1;
    }

    void swap(int* A, int i, int j)
    {
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }
};

inline int firstElement(int*, int start, int)
{
    return start;
}

inline int lastElement(int*, int, int end)
{
    return end;
} 

inline int medianOfThree(int* A, int start, int end)
{
    int middle = (start + end) / 2;
    if (A[start] > A[end])
    {
        if (A[start] < A[middle])
            return start;
        else if (A[middle] > A[end])
            return middle;
        else
            return end;
    } 
    else
    {
       if (A[end] < A[middle]) 
           return end;
       else if (A[middle] > A[start])
           return middle;
       else
           return start;
    }
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        cout << "Usage: ./qsort num filename" << endl; 
        exit(1);
    }

    int len = atoi(argv[1]);
    int* A = new int[len];
    int* B = new int[len];
    int* C = new int[len];

    ifstream file(argv[2]); 
    int i = 0;
    string str;
    while (getline(file, str))
    {
        int tmp = atoi(str.c_str());
        A[i] = tmp;
        B[i] = tmp;
        C[i] = tmp; 
        i++;
    }
 
    QuickSort q1;
    q1.sort(A, 0, len - 1, firstElement);
    cout << "The total number of comparisons using first element partition is " 
        << q1.getCount() << endl;
    delete[] A;
    
    QuickSort q2;
    q2.sort(B, 0, len - 1, lastElement);
    cout << "The total number of comparisons using last element partition is " 
        << q2.getCount() << endl; 
    delete[] B;

    QuickSort q3;
    q3.sort(C, 0, len - 1, medianOfThree);
    cout << "The total number of comparisons using median-of-three partition is " 
        << q3.getCount() << endl; 
    delete[] C;
}
