//
//  SCC.cpp
//  SCC
//
//  Created by Ning Wang on 11/11/15.
//  Copyright (c) 2015 Ning Wang. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;
typedef vector<int> AjacentList;
typedef vector<AjacentList> Graph;

class SCC
{
public:
    SCC(char* filename, int V0) : V(V0)
    {
        ifstream file(filename);
        if (!file)
        {
            cout << "Cannot open file" << endl;
            exit(1);
        }
        
        // initialize graph
        for (int i = 0; i < V; i++)
        {
            AjacentList a;
            g.push_back(a);
            grev.push_back(a);
        }
       
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string tail, head;
            iss >> tail;
            iss >> head;
            g[stoi(tail) - 1].push_back(stoi(head) - 1);
            grev[stoi(head) - 1].push_back(stoi(tail) - 1);
        }
        explored = new bool[V];
        leader = new int[V];
        finish = new int[V];
        labels = new int[V]; // init DFS sequence and SCCs
        for (int i = 0; i < V; i++)
            labels[i] = i;
        
        // first round DFS on reverse graph
        DFS_Loop(grev);
        
        // rearrange the sequence array according to their finish time
        for (int i = 0; i < V; i++)
            labels[finish[i] - 1] = i;
        
        // second round DFS on original graph
        DFS_Loop(g);
    }
    
    void getLargestSCCs(int n)
    {
        if (n > V)
            return;
        sort(sccs.begin(), sccs.end());
        cout << "The element count of 5 largest SCCs are: " << endl;
        for (int i = 0; i < 5; i++)
            cout << sccs[V - 1 - i] << " ";
        cout << endl;
    }
    
    ~SCC()
    {
        delete[] explored;
        delete[] leader;
        delete[] finish;
        delete[] labels;
    }
    
private:
    int V;
    bool* explored;
    int* labels;
    int* leader;
    Graph g;
    Graph grev;
    int t;
    int s;
    int* finish;
    vector<int> sccs;

    
    void DFS_Loop(Graph& g)
    {
        t = 0; // number of nodes processed
        s = 0; // current source vertex
        sccs.clear();
        for (int i = 0; i < V; i++)
        {
            explored[i] = false;
            sccs.push_back(0);
            leader[i] = -1;
        }
        
        for (int i = V - 1; i >= 0; i--)
        {
            int node = labels[i];
            if (!explored[node])
            {
                s = node;
                DFS(g, node);
            }
        }
    }
    
    void DFS(Graph& g, int i)
    {
        stack<int> frontier;
        frontier.push(i);
        explored[i] = true;
        
        while (!frontier.empty()) {
            int j = frontier.top();

            if (leader[j] != s)
            {   // use whether leader is set to distinguish a node
                // not yet truly explored and a node return from its child
                leader[j] = s;
                sccs[s]++;
            }
            
            bool haveChild = false;
            for (int k = 0; k < g[j].size(); k++)
            {
                if (!explored[g[j][k]]) {
                    frontier.push(g[j][k]);
                    haveChild = true;
                    explored[g[j][k]] = true;
                }
            }
            if (!haveChild)
            {
                t++;
                finish[j] = t;
                frontier.pop();
            }
        }
    }
};


int main(int argc, char * argv[]) {
    
    if (argc != 3)
    {
        cout << "Usage: SCC filename V" << endl;
        exit(1);
    }
    SCC scc(argv[1], atoi(argv[2]));
    scc.getLargestSCCs(5);
    return 0;
}
