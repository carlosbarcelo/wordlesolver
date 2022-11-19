#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>
#include "wordf.cpp"

using namespace std;

int main(int argc, char* argv[])
{
    string file;

    if (argc == 1){
      file = "bestlist.txt";
    }
    else{
      file = argv[1];
    }

    int len = getListLength(file);
    if (len == 0){
      return 0;
    }
    int* length = &len;

    int wordl = getWordLength(file);
    char** words = createWordList(file);

    srand(time(0));
    int goo = 1;

    printList(words, length, goo);

    while (true){
    //Green prompt
    cout << "Enter all Green letters and their position. End with a '/'" << endl << "example: y5 h1 a2 /" << endl;

    guess g[wordl];

    int i = 0;
    cin >> g[i].lt;

    while (g[i].lt != '/'){
        cin >> g[i].p;
        if (g[i].lt == '0' || g[i].p == 0){
            deleteWordList(words, len);
            return 1;
        }
        g[i].p--;
        checkGreen(words, length, g[i]);
        g[i].p++;
        i++;
        cin >> g[i].lt;
    }

    //Yellow prompt
    cout << endl << "Enter all Yellow letters and their position. End with a '/'" << endl << "example: m1 m2 y4 /" << endl;

    guess y[wordl];
    i = 0;
    cin >> y[i].lt;
    bool special;
    while (y[i].lt != '/'){
        cin >> y[i].p;
        special = false;
        for(int k = 0; k < wordl; k++){
          if(y[i].lt == g[k].lt){
            y[i].p--;
            checkYellow(words, length, y[i], g[k]);
            y[i].p++;
            special = true;
          }
        }
        if (y[i].lt == '0' || y[i].p == 0){
            deleteWordList(words, len);
            return 1;
        }
        else if (!special){
          y[i].p--;
          checkYellow(words, length, y[i]);
          y[i].p++;
        }
        i++;
        cin >> y[i].lt;
    }

    //Grey prompt
    cout << endl << "Enter all Grey letters. End with a '/'" << endl << "example: x q b /" << endl;

    char gr;
    cin >> gr;

    while (gr != '/'){
        if (gr == '0'){
            deleteWordList(words, len);
            return 1;
        }
        for(int c = 0; c < wordl; c++){
        }
        checkGrey(words, length, gr);
        cin >> gr;
    }
    goo++;
    printList(words, length, goo);
    }
}