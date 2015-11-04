/*
 * A simple graph representation specifically for solving
 * min-cut problem using Karger's algorthm.
 */

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <string>
#include <set>

class Graph
{
public:
    Graph(int v, bool  verbose);
    Graph(const char* filename, bool verbose);
    Graph(Graph& g);
    ~Graph();

    int getV(); // return number of vertices
    int getE(); // return number of edges
    void addEdge(int v, int w); // add an edge
    void printGraph();

    // perform contraction step from Karger's algorithm
    // note that this will corrupt the original graph
    void contract(); 

private:
    int V;
    int E; 
    std::multiset< std::pair<int, int> > edges;
    bool verbose;
    void exch(int& v, int& u);
    void changeEdge(int v, int w); // change edge with w to be with w 

};

#endif
