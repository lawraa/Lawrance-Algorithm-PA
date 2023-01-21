#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "cycleBreaking.h"
#include "../lib/tm_usage.h"
using namespace std;
// alg22f125 & VuecMuc7
//Written by Lawrance B09901116
//References listed in Report PDF

void help_message() {
    cout << "please enter: ./bin/cb <input_file> <output_file>" << endl;
}

int main(int argc, char* argv[]){
    if(argc != 3) {
       help_message();
       return 0;
    }
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;
        //////////// read the input file /////////////
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
    char type;
    int v_num, e_num;
    fin>>type;
    fin>>v_num;
    fin>>e_num;
    Graph g(type, v_num, e_num);

    for(int i = 0; i < e_num; i++){
        int edgeinfo[3];
        fin>>edgeinfo[0]>>edgeinfo[1]>>edgeinfo[2];
        g.addEdge(Edge(edgeinfo[0], edgeinfo[1], edgeinfo[2]));
    }
    fin.close();
    vector<Edge> removedEdges;
    
    g.sortEdges();
    //g.printEdges();
    removedEdges = Kruskal(g);
    //Reference - listed in report.pdf
    if (g.type == 'd'){
        g.initdirectededge(removedEdges);
        vector<int> temporary_removed;
        g.MergeSort(removedEdges);
        for(int i = 0; i < removedEdges.size(); i++){
            if(removedEdges[i].w > 0){
                if(!g.DFS(removedEdges[i])){
                    g.addEdge(removedEdges[i]);
                    temporary_removed.push_back(i);
                }
            }   
        }
        for(int i = temporary_removed.size()-1; i >= 0; i--){
            removedEdges.erase(removedEdges.begin()+temporary_removed[i]);
        }
    }
    int answer = 0;
    for (int i = 0; i < removedEdges.size(); i++)
        answer += removedEdges[i].w;
    fout << answer << endl;
    
    for (int i = 0; i < removedEdges.size(); i++)
        fout << removedEdges[i].u << " " << removedEdges[i].v << " " << removedEdges[i].w << endl;
    fout.close();
    
}