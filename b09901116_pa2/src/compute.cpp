#include "compute.h"
#include<iostream>
#include<cmath>
#include <cstring>
#include <fstream>

// Constructor
Computation::Computation(){}

Computation::~Computation(){
    delete[] recordChord;
    delete[] chords; 
    for (int i = 0; i<sampleSize; i++){
        delete [] mps[i];
    }
    delete[] mps;
    mps = 0;
}

void Computation::ReadFile(const char *filename){
//    char buffer[200];
    fstream fin(filename);
    int num1,num2;
    fin>>sampleSize;
    chords = new int[sampleSize];
    recordChord = new int[sampleSize];

    for (int i = 0; i<sampleSize;i++){//initialize result table
        recordChord[i] = 0;
    }

    for (int i = 0; i < (sampleSize/2);i++){//create a chord that connects each value
        int num1,num2;
        fin>>num1>>num2;
        chords[num1]=num2;
        chords[num2]=num1;
    }
    fin.close();
}

void Computation::calcMPS() {
    //psuedocode given by TA in HW2 Sol
    /*
    Maximum-Planar-Subset(C,n)
    for j = 0 to 2N-1
        k = number s.t. kj is in C or jk is in C
        for i = 0 to j-1
            if i<=k<=j-1 and |M(i,k-1)|+1+|M(k+1,j-1)|>M(i,j-1)
                M(i,j) = M(i,k-1)+1+M(k+1,j-1)
            else M(i,j) = M(i,j-1)

    Three cases 
    1. M[i,j] = M(i+1,j-1) +1 if ij is a chord
    2. M[i,j] = M(i, k-1) + M(k+1, j-1) +1 if jk is a chord and k is in [i,j]
    3. M(i,j) = M(i, j-1) if jk is a chord and k is not in [i,j]
    */

    mps = new int*[sampleSize];
    
    for (int i = 0; i< sampleSize; i++){ //initialize 2d array
        //int temp = sampleSize;
        mps[i] = new int [sampleSize];
        //temp--;
    }

    for (int i = 0; i <sampleSize; i++){ // initialize 2d array value
        //int temp = sampleSize;
        for(int j = 0; j<sampleSize; j++){
            mps[i][j] = 0;
            //temp--;
        }
    }

    for (int j=0; j<sampleSize; j++){ //record the max chords at each array
        for (int i=j-1; i>=0;i--){
            int k = chords[j];
            
            //case1 when ij is a chord
            if(k==i){ 
                mps[i][j] = mps[i+1][j-1]+1;
            }
            //case2 (jk chord is inside ij chord)
            else if (k>=i and k<=j-1 and ((mps[i][k-1]+1+mps[k+1][j-1])>(mps[i][j-1]))){
                mps[i][j] = mps[i][k-1]+1+mps[k+1][j-1];
            }
            //case3 jk chord is outside 
            else{
                mps[i][j] = mps[i][j-1];
            }
        }
    }
}


void Computation::getResult(int i, int j){ //save in result 
    int k = chords[j];
    //result table from 0 to sampleSize (in order)
    if (i<j){
        if (mps[i][j]==mps[i][j-1]){//when k is not in ij or all the other unchanged results
            getResult(i, j-1);//move back in table if same number
        }
        else if(k>= i and k<j){ //when k is in ij
            recordChord[k] ++; //save result
            getResult(i, k-1);  //check if there are inner chords remaining
            getResult(k+1,j-1); //check if there are inner chords remaining
        }
        else if (k==i){ //when ij is the chord
            recordChord[k] ++; //save result
            getResult(i+1,j-1); //check if there are inner chords between i,j
        }
    }
}

void Computation::WriteFile(const char *filename){
    fstream fout;
    getResult(0,sampleSize-1);
    fout.open(filename,ios::out);
    fout<<mps[0][sampleSize-1]<<endl;
    for (int i = 0; i<sampleSize; i++){//print out result (inorder)
        if(recordChord[i] != 0){
            fout<<i<<" "<<chords[i]<<endl;
        }
    } 
    fout.close();
}

    

   

   
