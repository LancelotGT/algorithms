/*
 * Implement the Karger's algorithm to solve min-cut problem
 */

#include <iostream>
#include <cstdlib>
#include <sys/time.h>
#include "Graph.h"

using namespace std;

int cut(Graph g);

void configure_seed ()
{
    FILE * dev_urandom = NULL;
    unsigned int seed;

    dev_urandom = fopen("/dev/urandom", "rb");
    if (dev_urandom == NULL)
        cout << "Error on opening /dev/urandom" << endl;

    setvbuf (dev_urandom, NULL, _IONBF, 0);
    if (fread (&seed, sizeof (seed), 1, dev_urandom) != 1)
        cout << "Error on reading /dev/urandom" << endl;

    fclose (dev_urandom);

    srandom(seed);
}

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        cout << "usage: Karger filename round verbose" << endl;       
        exit(1);
    }

    configure_seed();
    int verbose = atoi(argv[3]);
    Graph g(argv[1], verbose);

    int round = atoi(argv[2]);
    int* times = new int[round];

    timeval start, end;
    gettimeofday(&start, NULL);
    int min = cut(g);
    gettimeofday(&end, NULL); 
    times[0] = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);

    for (int i = 0; i < round - 1; i++)
    {
        gettimeofday(&start, NULL); 
        int result = cut(g);
        gettimeofday(&end, NULL);  
        times[i + 1] = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec); 
        min = min > result ? result : min;
    }
    cout << "min-cut is " << min << endl;

    long sum = 0;
    for (int i = 0; i < round; i++)
        sum += times[i];
    cout << "Total time used: " << sum / (double) 1000000 << "s" << endl;
    cout << "Average time per iteration: " << sum / (double) round / 1000000 << "s" << endl;
}

int cut(Graph g)
{
    int V = g.getV();
    for (int k = 0; k < V - 2; k++)
        g.contract(); 
    return g.getE();
}
