#include <iostream>
#include <fstream>
#include <string>
#include <sys/time.h> 

using namespace std;

class Counter
{
public:
    long sort_and_count(int* A, int start, int end)
    {   
        int len = end - start + 1;
        int mid = (end + start) / 2;
        long x, y, z;
        if (len == 0 || len == 1)
            return 0;
        else
        {
            x = sort_and_count(A, start, mid);
            y = sort_and_count(A, mid + 1, end); 
            z = count_split_inv(A, start, end);
        }
        return x + y + z;
    }

private:
    long count_split_inv(int* A, int start, int end)
    {
        int len = end - start + 1;

        if (len <= 1) // base case
            return 0;

        int mid = (end + start) / 2;
        int* D = new int[len];
        int i = start, j = mid + 1;
        long count = 0;

        if (A[mid] < A[mid + 1])
        {
            delete[] D;
            return 0; 
        }
 
        for (int k = 0; k < len; k++)
        {
            // if largest element in left half smaller than smallest element in
            // right half, simply no inversions

            if (i > mid)
                D[k] = A[j++];
            else if (j > end)
                D[k] = A[i++];
            else if (A[i] < A[j])
                D[k] = A[i++];
            else if (A[j] < A[i])
            {
                D[k] = A[j++];
                count += (mid - i + 1);
            }
        }

        // copy sorted array back to A
        for (int k = 0; k < len; k++)
            A[start + k] = D[k];
        delete[] D;
        return count;
    }
};

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        cout << "Usage: ./count num filename" << endl; 
        exit(1);
    }

    int len = atoi(argv[1]);
    int* A = new int[len];

    ifstream file(argv[2]); 
    int i = 0;
    string str;
    while (getline(file, str))
    {
        int tmp = atoi(str.c_str());
        A[i++] = tmp;
    }

    Counter c;
    struct timeval start, end;
    gettimeofday(&start, NULL); 
    long count = c.sort_and_count(A, 0, len - 1); 
    gettimeofday(&end, NULL);  
    delete[] A;
    long totaltime = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
    cout << "The total number of inversions: " << count << endl;
    cout << "Time elapsed: " << totaltime << " us" << endl; 
}
