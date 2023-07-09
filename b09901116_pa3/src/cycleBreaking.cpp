#include "cycleBreaking.h"
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

Edge::Edge(int u, int v, int w){
    this->u = u;
    this->v = v;
    this->w = w;
}

Vertex::Vertex(): parent(0), rank(0), color(0){}

Graph::Graph(char t, unsigned v, unsigned e):type(t), v_num(v), e_num(e){
    adj.reserve(v);// reserve space for v elements or else segmentation error
}

void Graph::addEdge(Edge edge){
    adj[edge.u].push_back(edge); //store edge e into adj vector(adjacency to vector u) 
    E.push_back(edge);//store edge e into vector
}

void Graph::delEdge(Edge edge){
    for (int j = 0; j<e_num;j++){
        if(edge.u==E[j].u){
            if(edge.v==E[j].v){
                if(edge.w == E[j].w){
                    E.erase(E.begin()+j);
                    break;
                }
            }
        }
    }
    for (int i = 0; i < adj[edge.u].size(); i++){
        if (edge.u == adj[edge.u][i].u){
            if(edge.v == adj[edge.u][i].v){
                if(edge.w == adj[edge.u][i].w){
                    adj[edge.u].erase(adj[edge.u].begin() + i);
                    break;
                }
            }
        }
    e_num -= 1;
    }
}

void Graph::initdirectededge(vector<Edge> all_edge){
    for(int i = all_edge.size()-1; i >=0; i--){
        delEdge(all_edge[i]);
    }
}

bool Graph::DFS(Edge& edge){
    Vertex *vert = new Vertex[v_num];
    return DFS_visit(edge.u, edge.v, vert);
}

bool Graph::DFS_visit(int start, int visiting, Vertex* vert){
    vert[visiting].color = 1;//set to grey
    for(int i = 0; i < adj[visiting].size(); i++){
        while (start == adj[visiting][i].v){//creates a cycle
            return true;// created a cycle
        }
        while(vert[adj[visiting][i].v].color == 0){//continue searching through white path
            while (DFS_visit(start, adj[visiting][i].v, vert)){
                return true;
            }
        }
    }
    return false;
}

void Graph::sortEdges(){
    MergeSort(E);
}
//Reference: Copied from PA1 "Merge Sort" and change some part
void Graph::MergeSort(vector<Edge>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

void Graph::MergeSortSubVector(vector<Edge>& data, int low, int high) {
    while(low<high){
        int mid = floor((low + high)/2);
        MergeSortSubVector(data, low, mid);
        MergeSortSubVector(data, mid+1, high);
        Merge(data, low, mid, mid+1, high);
        break;
    } 
}

void Graph::Merge(vector<Edge>& data, int low, int middle1, int middle2, int high){
    int n = low;
    vector<Edge> Left;
    vector<Edge> Right;
    for(int i = 0; i < middle1 - low + 1; i++){
        Left.push_back(data[low+i]);
    }
    for(int i = 0; i < high - middle2 + 1; i++){
        Right.push_back(data[middle2+i]);
    }
    int l = 0;
    int r = 0;

    while( (r < Right.size())&& (l < Left.size())){
        if( Right[r].w<Left[l].w  ){
            data[n] = Left[l];
            l++;
        }
        else{
            data[n] = Right[r];
            r++;
        }
        n++;
    }
    if(l!=Left.size()){
        while(l < Left.size()){
            data[n] = Left[l];
            l++;
            n++;
        }
    }
    else{
        while(r < Right.size()){
            data[n] = Right[r];
            r++;
            n++;
        }
    }
}
//Disjoint set pseudo code from textbook
DS::DS(int v_num){
    S = new Vertex[v_num];
    for (int i = 0; i < v_num; i++){
        S[i].parent = i;
        S[i].rank = 1;
    }
}

void DS::Union(int u, int v){
    Link(FindSet(u), FindSet(v));
}

int DS::FindSet(int x){
    while (x!= S[x].parent){
        S[x].parent = FindSet(S[x].parent);
        break;
    }
    return S[x].parent;
}

void DS::Link(int x, int y){
    while (S[x].rank < S[y].rank){
        S[y].parent = x;
        break;
    }
    while(S[x].rank >= S[y].rank){
        S[x].parent = y;
        if (S[x].rank == S[y].rank){
            S[y].rank += 1;
        }
        break;
    }
}

vector<Edge> Kruskal(Graph& G){
    DS S(G.v_num);
    vector<Edge> rmvedEdges;
    
    for (int i = 0; i < G.E.size(); i++){
        if (S.FindSet(G.E[i].u) == S.FindSet(G.E[i].v)){
            rmvedEdges.push_back(G.E[i]);
        }
        else{
            S.Union(G.E[i].u, G.E[i].v);
        }
    }
    return rmvedEdges;
}
/*void Graph::printEdges(){
    cout << "----------------- print edges -------------------\n";
    for(int i = 0; i < e_num; i++)
        cout << E[i].u << " " << E[i].v << " " << E[i].w << endl;
}*/
