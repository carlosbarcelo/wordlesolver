#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>
#include "wordf.cpp"

using namespace std;

int reducer(char** words, char** sol, char* w, char* s, int valid, int length);

int main(){

char input[] = "bestlist.txt";
char slist[] = "slist.txt";

int len = 12947;
char** words = createWordList(input);

int speed;

cin >> speed;

int slen = 2309;
char** solutions = createWordList(slist);

double clarity;

ofstream ofile("output.txt");

int reduced;

int total = 0;
for (int wi = 0; wi < len; wi++){
    total = 0;
for (int i = 0; i < slen/speed; i++){
    reduced = reducer(words, solutions, words[wi], solutions[speed*i], len, len);
    total += reduced;
    words = createWordList(input);
    //cout << words[wi] << solutions[i] << endl;
    //cout << reduced << endl;
}
if (wi < 2309){
    ofile << "0 ";
}
else{
    ofile << "1 ";
}
clarity = 100-((100.0*total/(slen/speed)/len));
ofile << words[wi] << ' ' << clarity << endl;
cout << wi << words[wi] << ' ' << clarity << endl;
}

ofile.close();

deleteWordList(words, len);
deleteWordList(solutions, slen);
}

int reducer(char** words, char** sol, char* w, char* s, int valid, int length){
    for(int j = 0; j < 5; j++){
        guess g;
        if(w[j] == s[j]){
            g.p = j;
            g.lt = w[j];
            newCheckGreen(words, &valid, length, g);
        }
        else if(w[j] == s[0] || w[j] == s[1] || w[j] == s[2] || w[j] == s[3] || w[j] == s[4]){
            g.p = j;
            g.lt = w[j];
            newCheckYellow(words, &valid, length, g);
        }
        else{
            newCheckGrey(words, &valid, length, w[j]);
        }
    }
    deleteWordList(words, length);
    return valid;
}
