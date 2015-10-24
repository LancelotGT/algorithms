#include <iostream>
#include <fstream>
#include <string>
#include <sys/time.h>

using namespace std;

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        cout << "Usage: ./bruteforce num filename" << endl; 
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

    long count = 0;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < len; i++)
        for (int j = i + 1; j < len; j++)
        {
            if (A[i] > A[j])
                count++;
        }
    gettimeofday(&end, NULL); 
    delete[] A;
    long totaltime = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
    cout << "The total number of inversions: " << count << endl;
    cout << "Time elapsed: " << totaltime << " us" << endl;
}
