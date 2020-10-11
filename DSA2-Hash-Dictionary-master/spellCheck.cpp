#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "hash.h"

using namespace std;
hashTable wordList;
int count;

void spellCheck(string FILE_NAME){
    string line;
    string currentWord;
    bool hasNumber;
    int lineNumber;
    lineNumber=1;
    ifstream file;
    ofstream outputFile;

    file.open(FILE_NAME);
    outputFile.open("output.txt");
    if (!outputFile.is_open())
        cout << "Output file opening error" << endl;
    if (!file.is_open())
        cout << "Input file opening error" << endl;
    
    while ( getline( file, line)){
        currentWord.clear(); // Fresh start
        hasNumber=false;
        for(int i=0; i<line.length()+1;i++){

            // a to z or - or ' CONVERT EVERYTHING TO LOWER HERE
            if((int(tolower(line[i])) >=97 && int(tolower(line[i])) <=122) || (int(tolower(line[i]))==39) || (int(tolower(line[i]))==45)){  
                currentWord.push_back(tolower(line[i]));
            }

            //0-9
            else if( int(line[i]) >=48 && int(line[i]) <=57){
            hasNumber=true;    //consider this automatically a valid word 
            currentWord.push_back(line[i]);
            }

            // Consider everything else as word end. Time to decide fate of word.
            else{
                if(hasNumber==true){ //VALID WORD, NO EXCEPTIONS
                    currentWord.clear();
                    hasNumber=false;
                }

                else if(currentWord.length()>20){//INVALID LENGTH, NO EXCEPTIONS
                    outputFile << "Long word at line " << lineNumber << ", starts: " << currentWord.substr(0,20) << endl;
                    currentWord.clear();
                }

                else if(currentWord.length()==0){//EMPTY LINE
                }

                else{ //Test for existence in hashTable
                    if(wordList.contains(currentWord)==true){
                    }
                    else{
                        outputFile << "Unknown word at line " << lineNumber <<": "<< currentWord << endl;
                    }
                    /* CODE FOR TESTING FOR EXISTENCE IN HASH TABLE GOES HERE*/
                    /* CODE FOR TESTING FOR EXISTENCE IN HASH TABLE GOES HERE*/
                    //outputFile << lineNumber << ": " << currentWord << endl;
                    currentWord.clear();
                }
            };
        };
        lineNumber++;
    };
    cout << "Done \n";
};

// Grab dictionary
void grabDictionary(string INPUT_DICTIONARY){
    cout << "Grabbing dictionary: " << INPUT_DICTIONARY << endl;
    int wordCount=0;
    string word;
    ifstream dicfile;
    dicfile.open(INPUT_DICTIONARY);

    while (getline( dicfile, word)){
        wordCount++;
    };
    
    hashTable hashedDictionary(wordCount);
    cout << "Word count: " << wordCount << endl;
    hashedDictionary.returnSize();

    dicfile.close(); //Gotta close it to restart at top :(  better way must exists
    dicfile.open(INPUT_DICTIONARY);

    while (getline( dicfile, word)){
        //because our input words dont end with \n GET RID OF THE NEW LINE CHAR!!! 
        hashedDictionary.insert(word); //hash and put everything in hashedDictionary
    };
    cout << "Dictionary set up" << endl;
    wordList = hashedDictionary;    //copy this to our global var
}

int main( int argc, char* argv[]){
    string INPUT_FILE;
    string INPUT_DICTIONARY;
    cout <<"Enter name of input file: ";
    cin >> INPUT_FILE;
    cout << "Enter name of dictionary: ";
    cin >> INPUT_DICTIONARY;
    grabDictionary(INPUT_DICTIONARY);
    spellCheck(INPUT_FILE);
}