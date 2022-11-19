#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>
#include "wordl.h"

using namespace std;

int getListLength(string wlist){
    //Creating the word list from the file
    ifstream ifile(wlist);
    if (ifile.fail()){
        cout << "Couldn't open file" << endl;
    return 0;
    }

    int numwords;
    ifile >> numwords;
    ifile.close();
    return numwords;
}

int getWordLength(string wlist){
    //Creating the word list from the file
    ifstream ifile(wlist);
    if (ifile.fail()){
        cout << "Couldn't open file" << endl;
    return 0;
    }

    int numwords;
    int wordl;
    ifile >> numwords;
    ifile >> wordl;
    ifile.close();
    return wordl;
}


char** createWordList(string wlist){
    //Creating the word list from the file
    ifstream ifile(wlist);
    if (ifile.fail()){
        cout << "Couldn't open file" << endl;
    return NULL;
    }

    int numwords;
    int wordlength;

    ifile >> numwords;
    ifile >> wordlength;

    char** words = new char*[numwords];

    for(int i = 0; i < numwords; i++){
        words[i] = new char[wordlength];
        ifile >> words[i];
    }
    ifile.close();
    return words;
}

void deleteWordList(char** words, int length){
    for(int i = 0; i < length; i++){
        delete[] words[i];
    }
    delete[] words;
}

void printList(char** words, int *length, int g){
    cout << endl;
    for(int i = 0; i < *length; i++){
      cout << words[i] << "   ";
      if (i %10 == 9){
        cout << endl << endl;
      }
    }
    cout << endl << endl << *length << " valid guesses" << endl;
    if (*length > 0) {
      int wi = 0;
      string word = words[wi];
      char** slist = createWordList("slist.txt");
      int slen = 2309;
      if (g > 1){
            bool solu = false;
            for(int j = 0; j < slen && !solu; j++){
                if (word == slist[j]){
                    solu = true;
                }
                else if(!solu && j == slen-1){
                  if(wi == *length){
                    solu = true;
                    wi = -1;
                  }
                    j = 0;
                    wi++;
                    word = words[wi];   
                }
            }
        }
      cout << endl << "Best suggestion: " << words[wi] << endl << endl;
    }
}

void checkGreen(char** words, int* length, guess g){
    for(int i = 0; i < *length; i++){
        if (words[i][g.p] != g.lt){
          eraseWord(words, length, i);
          i--;
        }
    }
}

void checkYellow(char** words, int* length, guess y){
    for(int i = 0; i < *length; i++){
        if (words[i][y.p] == y.lt){
          eraseWord(words, length, i);
          i--;
        }
        else{
        bool same = false;
          for(int j = 0; words[i][j] != '\0' && !same; j++){
            if(words[i][j] == y.lt){
              same = true;
            }
          }
          if (!same){
          eraseWord(words, length, i);
          i--;
          }
        }
    }
}

void checkYellow(char** words, int* length, guess y, guess g){
    for(int i = 0; i < *length; i++){
      bool same = false;
      if (words[i][y.p] == y.lt){
        eraseWord(words, length, i);
        i--;
      }
      else{
        for(int j = 0; words[i][j] != '\0' && !same; j++){
          if(words[i][j] == y.lt && j != g.p-1){
            same = true;
          }
        }
        if (!same){
          eraseWord(words, length, i);
          i--;
        }
      }
    }
}

void checkGrey(char** words, int* length, char g){
    bool same = false;
    for(int i = 0; i < *length; i++){
      same = false;
      for(int j = 0; !same && words[i][j] != '\0'; j++){
        if(words[i][j] == g){
          eraseWord(words, length, i);
          i--;
          same = true;
        }
      }        
    }
}

void eraseWord(char** words, int* length, int in){
    for(int i = in; i < *length-1; i++){
      words[i] = words[i+1];
    }
     *length-=1;
}

void newCheckGreen(char** words, int* valid, int length, guess g){
    for(int i = 0; i < length; i++){
        if(words[i][0] == '.'){

        }
        else if (words[i][g.p] != g.lt){
          words[i][0] = '.';
          *valid -=1;
        }
    }
}

void newCheckYellow(char** words, int* valid, int length, guess y){
    for(int i = 0; i < length; i++){
      bool same = false;
      if(words[i][0] == '.'){

      }
      else if (words[i][y.p] == y.lt){
          words[i][0] = '.';
          *valid -=1;
      }
      else{
        for(int j = 0; words[i][j] != '\0' && !same; j++){
          if(words[i][j] == y.lt){
            same = true;
          }
        }
        if (!same){
          words[i][0] = '.';
          *valid -=1;
        }
      }
    }
}

void newCheckGrey(char** words, int* valid, int length, char g){
    bool same = false;
    for(int i = 0; i < length; i++){
      same = false;
      if (words[i][0] != '.'){
      for(int j = 0; !same && words[i][j] != '\0'; j++){
        if(words[i][j] == g){
          words[i][0] = '.';
          *valid -=1;
          same = true;
        }
      }
      }        
    }
}