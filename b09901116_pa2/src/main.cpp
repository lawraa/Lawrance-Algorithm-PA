#include <cstring>
#include <iostream>
#include <fstream>
#include "compute.h"
#include "../lib/tm_usage.h"
// alg22f125 & VuecMuc7

using namespace std;

void help_message() {
    cout << "please enter: ./bin/mps <input_file> <output_file>" << endl;
}
/*
int *readinput(char const *filename){
    int *input; 
    //we want to save the inputs 
}

int *calcSize(char const *filename){
    int size = 0;

    return size;
}
*/

int main(int argc, char* argv[]){
    if(argc != 3) {
       help_message();
       return 0;
    }
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;
        //////////// read the input file /////////////
    Computation Compute; 
    Compute.ReadFile(argv[1]);
    tmusg.periodStart();

    //run the code for the main
    
    Compute.calcMPS();
    //////////// write the output file ///////////
    
    
    tmusg.getPeriodUsage(stat);
    
    cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout <<"memory: " << stat.vmPeak << "KB" << endl; // print peak memory
    
    
    Compute.WriteFile(argv[2]);
    return 0;
}


