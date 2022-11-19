#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include "wordf.cpp"

using namespace std;

int main(int argc, char* argv[]){

int games;

games = atoi(argv[1]);

char** slist = createWordList("slist.txt");
int slen = 2309;

char** words;
int len;

string failurewords = "";

srand(time(0));

int tg = 0;
int suc = 0;

for(int gi = 0; gi < games; gi++){
    len = getListLength("worstlist.txt");
    words = createWordList("worstlist.txt");
    string sol = slist[rand()%slen];
    string word;
    int g = 0;

    while(sol != word){
        int wi = 0;
        word = words[wi];
            bool solu = false;
            for(int j = 0; j < slen && !solu; j++){
                if (word == slist[j]){
                    j = 0;
                    wi++;
                }
                if (wi < len){
                    word = words[wi];
                }
                else{
                    solu = true;
                    word = words[0];
                }
            }
        for(int i = 0; i<5 ; i++){
            if(word[i] == sol[i]){
                guess g;
                g.p = i;
                g.lt = word[i];
                checkGreen(words, &len, g);
                printf("\x1b[42m");
                cout << ' ' << g.lt << ' ';
                printf("\033[0m"); 

            }
            else if(word[i] == sol[0] || word[i] == sol[1] || word[i] == sol[2] || word[i] == sol[3] ||word[i] == sol[4]){
                guess g;
                g.p = i;
                g.lt = word[i];
                checkYellow(words, &len, g);
                printf("\x1b[43m");
                cout << ' ' << g.lt << ' ';
                printf("\033[0m"); 
            }
            else{
                checkGrey(words, &len, word[i]);
                printf("\x1b[47m");
                cout << ' ' << word[i] << ' ';
                printf("\033[0m"); 

            }
        }
        cout << "     " << len << endl;
        g++;
        tg++;
    }
    if(g >= 7){
        printf("\x1b[41m");
        cout << "FAILURE " << g << endl << endl;
        printf("\033[0m"); 
        failurewords += " ";
        failurewords += sol;
        failurewords += " ";
    }
    else{
        cout << g << endl << endl;
        suc++;
    }
    deleteWordList(words, len);
}
cout << "Avg. Guesses: " << 1.0*tg/games << "   Success rate: " << suc << '/' << games << "  (" << 100.0*suc/games << "%)" << endl;
cout << endl << "Failure Words: " << failurewords << endl << endl;
}