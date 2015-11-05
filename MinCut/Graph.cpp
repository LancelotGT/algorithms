#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <assert.h>
#include "Graph.h"

using namespace std;

Graph::Graph(int v, bool verbose) : V(v)
{
    E = 0;
    this->verbose = verbose;
}

Graph::Graph(const char* filename, bool verbose)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Cannot open file" << endl;
    }
    
    this->verbose = verbose;
    string temp;
    getline(file, temp);
    V = atoi(temp.c_str());
    E = 0;

    for (int i = 1; i <= V; i++)
    {
        string str;
        getline(file, str);
        istringstream iss(str);
        string tail;
        iss >> tail;
        while (iss >> tail)
        {
            if (verbose)
                cout << tail << " ";
            int v = atoi(tail.c_str());
            if (i < v)
                addEdge(i, atoi(tail.c_str()));
        }
        if (verbose)
            cout << endl;
    }
    if (verbose)
    {
        cout << "New graph populated." << endl;
        cout << "V: " << V << endl;
        cout << "E: " << E << endl; 
    }
}

Graph::Graph(Graph& g) : V(g.getV()), E(g.getE())
{
    this->verbose = g.verbose;
    this->edges = g.edges;
    if (verbose)
    {
        cout << "Check copy content:" << endl;
        printGraph(); 
    }
}

Graph::~Graph()
{
}

int Graph::getV()
{
    return V;
}

int Graph::getE()
{
    return edges.size();
}

void Graph::addEdge(int v, int w)
{
    edges.push_back(pair<int, int>(v, w));
    E++;
}

void Graph::changeEdge(int v, int w)
{
    vector< pair<int, int> > t;
    for (list< pair<int, int> >::iterator it = edges.begin(); it != edges.end(); )
    {
        if (it->first == w)
        {
            if (it->second != v)
                t.push_back(pair<int, int>(v, it->second));
            it = edges.erase(it);
        }
        else if (it->second == w)
        {
            if (it->first != v)
                t.push_back(pair<int, int>(it->first, v));
            it = edges.erase(it); 
        }
        else
            it++;
    }

    for (vector< pair<int, int> >::iterator it = t.begin(); it != t.end(); it++)
        edges.push_back(*it);
}

void Graph::printGraph()
{
    cout << "V: " << V << endl;
    cout << "E: " << E << endl; 
    for (list< pair<int, int> >::iterator it = edges.begin(); it != edges.end(); ++it)
        cout << "(" << it->first << ", "  << it->second << ")" << endl;
}

void Graph::contract()
{
    int size = edges.size();
    list< pair<int, int> >::iterator it = edges.begin();
    int s = rand() % size;
    for (int i = 0; i < s; i++)
        it++;
    
    int v = it->first;
    int w = it->second;

    if (verbose)
        cout << "contract: " << v << " " << w << endl;
    changeEdge(v, w);
    if (verbose)
        printGraph();
}
