#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>

using namespace std;

int getListLength();
char** createWordList();
void deleteWordList(char**, int);
void checkGreen(char**, int, char, int);
void checkYellow(char**, int, char, int);
void checkGrey(char**, int, char);
void printList(char**, int);

int main()
{
    int length = getListLength();
    char** words = createWordList();

    while (true){
    //Green prompt
    cout << "Enter all Green letters and their position. End with a '/'" << endl << "example: y5 h1 a2 /" << endl;

    char g;
    int gp;
    cin >> g;

    while (g != '/'){
        cin >> gp;
        if (g == '0' || gp == 0){
            deleteWordList(words, length);
            return 1;
        }
        checkGreen(words, length, g, gp-1);
        cin >> g;
    }

    //Yellow prompt
    cout << endl << "Enter all Yellow letters and their position. End with a '/'" << endl << "example: m1 m2 y4 /" << endl;

    cin >> g;
    while (g != '/'){
        cin >> gp;
        if (g == '0' || gp == 0){
            deleteWordList(words, length);
            return 1;
        }
        checkYellow(words, length, g, gp-1);
        cin >> g;
    }

    //Grey prompt
    cout << endl << "Enter all Grey letters. End with a '/'" << endl << "example: x q b /" << endl;

    cin >> g;
    while (g != '/'){
        if (g == '0'){
            deleteWordList(words, length);
            return 1;
        }
        checkGrey(words, length, g);
        cin >> g;
    }

    printList(words, length);
    }
}






int getListLength(){
    //Creating the word list from the file
    ifstream ifile("wordlist.txt");
    if (ifile.fail()){
        cout << "Couldn't open file" << endl;
    return 0;
    }

    int numwords;
    ifile >> numwords;
    ifile.close();
    return numwords;
}


char** createWordList(){
    //Creating the word list from the file
    ifstream ifile("wordlist.txt");
    if (ifile.fail()){
        cout << "Couldn't open file" << endl;
    return NULL;
    }

    int numwords;
    ifile >> numwords;
    
    char** words = new char*[numwords];


    for(int i = 0; i < numwords; i++){
        words[i] = new char[5];
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

void printList(char** words, int length){
    int valid = 0;
    for(int i = 0; i < length; i++){
        if (words[i][0] != '.'){
            cout << words[i] << "   ";
            valid ++;

            if (valid %10 == 0){
            cout << endl << endl;
            }
        }
    }
    cout << endl << endl << valid << " valid guesses" << endl << endl;
}

void checkGreen(char** words, int length, char g, int gp){
    for(int i = 0; i < length; i++){
        if (words[i][gp] != g){
            words[i][0] = '.';
        }
    }
}

void checkYellow(char** words, int length, char y, int yp){
    for(int i = 0; i < length; i++){
        if (words[i][yp] == y){
            words[i][0] = '.';
        }
        else if(words[i][0] != y && words[i][1] != y && words[i][2] != y && words[i][3] != y && words[i][4] != y){
                words[i][0] = '.';
        }
    }
}

void checkGrey(char** words, int length, char g){
    for(int i = 0; i < length; i++){
        if(words[i][0] == g || words[i][1] == g || words[i][2] == g || words[i][3] == g || words[i][4] == g){
            words[i][0] = '.';
        }        
    }
}