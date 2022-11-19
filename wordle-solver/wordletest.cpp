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
bool play = false;
if (argc < 2){
    games = 1;
    play = true;
}
else{
    games = atoi(argv[1]);
}
char** checker =createWordList("english.txt");

char** slist = createWordList("slist.txt");
int slen = 2309;

char** words;
int len;

string failurewords = "";

srand(time(0));

int tg = 0;
int suc = 0;

if (!play){
for(int gi = 0; gi < games; gi++){
    len = getListLength("bestlist.txt");
    words = createWordList("bestlist.txt");
    string sol = slist[rand()%slen];
    string word;
    int g = 0;

    while(sol != word){
        int wi = 0;
        bool csol[5];
        word = words[wi];
        if (g >= 1){
            bool solu = false;
            for(int j = 0; j < slen && !solu; j++){
                if (word == slist[j]){
                    solu = true;
                }
                else if(!solu && j == slen-1){
                  if(wi == len){
                    solu = true;
                    wi = -1;
                  }
                    j = 0;
                    wi++;
                    word = words[wi];  
                }
            }
        }
        for(int i = 0; i<5 ; i++){
            if(word[i] == sol[i]){
                guess g;
                g.p = i;
                g.lt = word[i];
                checkGreen(words, &len, g);
                csol[i] = true;
            }
            else{
                csol[i] = false;
            }
        }
        for(int i = 0; i<5 ; i++){
            if(csol[i]){
                printf("\x1b[42m");
                cout << ' ' << word[i] << ' ';
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
else{
    len = getListLength("bestlist.txt");
    const int clen = len;
    words = createWordList("bestlist.txt");
    string sol = slist[rand()%slen];
    string word;
    string sug;
    int g = 0;

    while(sol != word){
        int wi = 0;
        sug = words[wi];
        if (g >= 2){
            bool solu = false;
            for(int j = 0; j < slen && !solu; j++){
                if (sug == slist[j]){
                    solu = true;
                }
                else if(!solu && j == slen-1){
                  if(wi == len){
                    solu = true;
                    wi = -1;
                  }
                    j = 0;
                    wi++;
                    sug = words[wi];  
                }
            }
        }
        cout << "Guess: ";
        cin >> word;
        bool good = false;
        while(!good){
            for (int p = 0; p < clen && !good && word.length() == 5; p++){
                if (word == checker[p]){
                    good = true;
                }
            }
            if (word == "h"){
                cout << "Best Guess: " << sug << ' ' << len << '\t' << '\t';
            }
            if (!good){
                cout << "Guess again: ";
                cin >> word;
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
        g++;
        cout << '\t';
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
    }
    deleteWordList(words, len);
}
}