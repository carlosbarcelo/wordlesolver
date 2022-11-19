#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>

using namespace std;

struct guess{
  char lt;
  int p;
};

int getListLength(string);
int getWordLength(string);
char** createWordList(string);
void deleteWordList(char**, int);
void checkGreen(char**, int*, guess);
void checkYellow(char**, int*, guess);
void checkYellow(char**, int*, guess, guess);
void checkGrey(char**, int*, char);
void printList(char**, int*, int g);
void eraseWord(char**, int*, int);
void newCheckGreen(char** words, int* valid, guess g);
void newCheckYellow(char** words, int* valid, guess y);
void newCheckGrey(char** words, int* valid, char g);