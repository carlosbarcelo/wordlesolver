#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>
#include "wordf.cpp"

using namespace std;

struct gword{
    bool solu;
    char wo[5];
    double cl;
};

int main(){

int len = 13186;


ifstream ifile("output.txt");

if (ifile.fail()){
    cout << "Couldn't open file" << endl;
return 0;
}

gword words[len];

int sl;

for(int i = 0; i < len; i++){
    ifile >> sl;
    if (sl == 0){
        words[i].solu = true;
    }
    else{
        words[i].solu = false;
    }
    ifile >> words[i].wo;
    ifile >> words[i].cl;


}

ifile.close();

for (int i = 0; i < len; i++)
{
    double highest = 0;
    int hin;
    for (int j = i; j < len; j++){
        if (words[j].cl >= highest){
            highest = words[j].cl;
            hin = j;
        }
    }
    bool tso;
    double tcl;
    char two[5];

    tso = words[i].solu;
    tcl = words[i].cl;
    for(int t = 0; t < 5; t++){
        two[t] = words[i].wo[t];
    }
        
    words[i].solu = words[hin].solu;
    words[i].cl = words[hin].cl;
    for(int t = 0; t < 5; t++){
        words[i].wo[t] = words[hin].wo[t];
    }

    words[hin].solu = tso;
    words[hin].cl = tcl;
    for(int t = 0; t < 5; t++){
        words[hin].wo[t] = two[t];
    }
}

ofstream ofile("bestlist.txt");

for(int i = 0; i < len; i++){
    //ofile << words[i].solu << ' ' << words[i].wo << ' ' << words[i].cl << endl;
    ofile << words[i].wo << endl;
}

}