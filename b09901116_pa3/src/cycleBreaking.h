#ifndef _CYCLEBREAK_H
#define _CYCLEBREAK_H

#include <algorithm>
#include <vector>
using namespace std;

class Edge{
public:
    int u, v, w;
    Edge(int u, int v, int w);
};

class Vertex{
public:
    int parent;
    int rank;
    int color; // 0 for white, 1 for gray, 2 for black
    Vertex();
};

class Graph{
public:
    char type;                                            
    unsigned v_num;                                            
    unsigned e_num;                                                                                   
    vector<vector<Edge> > adj;                         
    vector<Edge> E;                                

    Graph();                    
    Graph(char, unsigned, unsigned);
    void addEdge(Edge);                                    
    void delEdge(Edge);
    bool DFS(Edge& );     
    bool DFS_visit(int, int, Vertex* );         
    void sortEdges();                                     
    void MergeSort(vector<Edge>&); 
    void MergeSortSubVector(vector<Edge>&, int, int);
    void Merge(vector<Edge>&, int, int, int, int);
    void initdirectededge(vector<Edge>);  
   //void printEdges();                        
};

class DS{
public:
    Vertex *S;
    void Union(int u, int v);
    int FindSet(int u);
    void Link(int u, int v);
    DS(int num_v);
};
vector<Edge> Kruskal(Graph&);

#endif