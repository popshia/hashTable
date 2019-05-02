// 10627130 林冠良 & 10627131 李峻瑋 // Visual Studio Community 2019
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <time.h>

using namespace std;

typedef struct DataStruct {
    char id[10];
    char name[10];
    unsigned char score[6];
    float average;
    int hValue = 0;
} DataStruct;

static string FileNumber = "0";
static int Count = 1;
static int Command = 0;
static fstream openTxt;
static fstream openBin;

class function1 {
    DataStruct temp;
public:
    vector<DataStruct> dataBase;
    
    void ReadTxt() {
        ;
    }
};
                   
class function2 : public function1 {
public:
    int FindPrimeNumber( int dataSize ) {
        for ( bool findprime = false ; findprime != true ; dataSize++ ) {
            for ( int i = 2 ; i <= dataSize ; i++ ) {
                if ( dataSize % i == 0 ) {
                    if ( dataSize == i ) findprime = true;
                    else break;
                }  // if
            } // for
        } // for
        
        return dataSize;
    } //FindPrimeNumber()
    
    int getHValue( char id[10] ) {
        int hValue = 0 ;
        for ( int i = 0 ; i < 7 ; i++ ) hValue = hValue * (int)id[i] ;
        return hValue ;
    } //getHvalue
    
    void BuildHashTableX() {
        float size = dataBase.size() * 1.2;
        DataStruct X[FindPrimeNumber((int)size)];
        
        for ( int i = 0 ; i < dataBase.size() ; i++ ) {
            int tempHValue = getHValue( dataBase[i].id ) % (int)size ;
            dataBase[i].hValue = tempHValue ;
            X[tempHValue] = dataBase[i] ;
        } // put into hashTable
        
    } // BuildHashTableX()
    
};
                   
class function3 : public function2 {
                       
};
                   
int main() {
    bool continueOrNot = false;
                       
    do {
        function1 One;
        function2 Two;
        function3 Three;
        cout << "**********************************************" << endl; // welcome message
        cout << "*****               DS2ex03              *****" << endl;
        cout << "***** 0 : Quit                           *****" << endl;
        cout << "***** 1 : Read and convert data          *****" << endl;
        cout << "***** 2 : Linear probing                 *****" << endl;
        cout << "***** 3 : Double hash                    *****" << endl;
        cout << "**********************************************" << endl;
        cout << endl << "Please enter your choice:" << endl;
                           
        cin >> Command; // read in user command
        cout << endl;
        
        if ( Command == 0 ) { // bye :(((
            cout << "Bye :(((" << endl;
            return 0;
        } // quit
        
        else if ( Command > 3 || Command < 0 ) {
            cout << "Error command! please enter an acceptable command:" << endl << endl;
            continueOrNot = true;
        } // wrong command
        
        else if ( Command == 1 ) { // read, count and build
            bool function1Confirm = false;
                               
            do {
                cout << "Please enter the file number you want to convert to binary file or [0] to quit:" << endl;
                cin >> FileNumber;
                                   
                if ( FileNumber == "0" ) {
                    function1Confirm = true;
                    continueOrNot = true;
                    cout << endl;
                } // quit
                
                else {
                    string txtFileName = "input" + FileNumber + ".txt";
                    string binFileName = "input" + FileNumber + ".bin";
                    //openBin = fopen( binFileName.c_str(), "rb" );
                                       
                    if ( openBin ) {
                        //One.ReadBin();
                        function1Confirm = true;
                        continueOrNot = true;
                    } // binary file open successfully
                    
                    else {
                        //openTxt = fopen( txtFileName.c_str(), "r" );
                        if ( openTxt ) {
                            One.ReadTxt();
                            function1Confirm = true;
                            continueOrNot = true;
                        } // txt file open sucessfully
                        else {
                            cout << "*****  file does not exist!  *****" << endl;
                            function1Confirm = false;
                        } // no such file
                    } // open successfully
                } // continue
            } while ( !function1Confirm );
                               
            Count = 1;
            FileNumber = "0";
            if ( openBin ) fclose( openBin );
            if ( openTxt ) fclose( openTxt );
        } // function 1
                           
        else if ( Command == 2 ) {
            bool function2Confirm = false;
            
            do {
                cout << "Please enter the file you want to build a AVL Tree or [0] to quit:" << endl;
                cin >> FileNumber;
                                   
                if ( FileNumber == "0" ) {
                    function2Confirm = true;
                    continueOrNot = true;
                } // quit
                                   
                else {
                    string fileName = "input" + FileNumber + ".txt";
                    if (1) {
                        function2Confirm = true;
                        continueOrNot = true;
                    } // open successfully
                    else cout << "*****  " << fileName << " does not exist!  *****" << endl;
                } // open file and input data to BST
            } while ( !function2Confirm );
                               
            Count = 0;
            FileNumber = "0";
        } // AVL Tree
                           
        else if ( Command == 3 ) {
            ;
        }
    } while ( continueOrNot );
} // main()
