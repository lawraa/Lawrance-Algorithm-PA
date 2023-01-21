#ifndef _MPS_H
#define _MPS_H

using namespace std;

class Computation {
    public:
                    Computation(); // constructor
                    ~Computation();//destructor
        void        calcMPS(); 
        void        getResult(int i, int j);
        void        ReadFile(const char *);
        void        WriteFile(const char *);

    private:
        int         sampleSize;
        int         **mps;
        int         *recordChord;
        int         *chords; 
        
};

#endif
