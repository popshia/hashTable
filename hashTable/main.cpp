// 10627130 林冠良 & 10627131 李峻瑋 // CodeBlocks 17.12
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

using namespace std ;

typedef struct DataStruct {
    unsigned char id ;
    unsigned char name ;
    unsigned char score ;
    float average ;
    
} DataStruct ;

static ifstream input ;
static ofstream output ;
static string FileNumber = "0" ;
static int Count = 1 ;
static int Command = 0 ;

class function0 {
    
} ;

class function1 {
    
} ;

class function2 {
    
} ;

int main() {
    bool continueOrNot = false ;
    
    do {
        function0 Zero ;
        function1 One ;
        function2 Two ;
        cout << "**********************************************" << endl ; // welcome message
        cout << "*****               DS2ex03              *****" << endl ;
        cout << "***** 0 : Quit                           *****" << endl ;
        cout << "***** 1 : Read and analyze data          *****" << endl ;
        cout << "***** 2 : Linear probing                 *****" << endl ;
        cout << "***** 3 : Double hash                    *****" << endl ;
        cout << "**********************************************" << endl ;
        cout << endl << "Please enter your choice:" << endl ;
        
        cin >> Command ; // read in user command
        cout << endl ;
        
        if ( Command == 0 ) { // bye :(((
            cout << "Bye :(((" << endl ;
            return 0 ;
        } // quit
        
        else if ( Command > 3 || Command < 0 ) {
            cout << "Error command! please enter an acceptable command:" << endl << endl ;
            continueOrNot = true ;
        } // wrong command
        
        else if ( Command == 1 ) { // read, count and build
            bool function1Confirm = false ;
            
            do {
                cout << "Please enter the file you want to build a 2-3 Tree or [0] to quit:" << endl ;
                cin >> FileNumber ;
                
                if ( FileNumber == "0" ) {
                    function1Confirm = true ;
                    continueOrNot = true ;
                } // quit
                
                else {
                    string txtFileName = "input" + FileNumber + ".txt" ;
                    string binFileName = "input" + FileNumber + ".bin" ;
                    input.open( txtFileName.c_str() ) ;
                    if ( input.is_open() ) {
                        // One.ReadNAnalyze() ;
                        function1Confirm = true ;
                        continueOrNot = true ;
                    } // open successfully
                    input.open( binFileName.c_str() ) ;
                    if ( input.is_open() ) {
                        // One.ReadNAnalyze() ;
                        function1Confirm = true ;
                        continueOrNot = true ;
                    } // open successfully
                    else cout << "*****  file does not exist!  *****" << endl ;
                } // continue
            } while( ! function1Confirm ) ;
            
            Count = 1 ;
            FileNumber = "0" ;
            input.close() ;
            output.close() ;
        } // 2-3 tree
        
        else if ( Command == 2 ) {
            bool function2Confirm = false ;
            
            do {
                cout << "Please enter the file you want to build a AVL Tree or [0] to quit:" << endl ;
                cin >> FileNumber ;
                
                if ( FileNumber == "0" ) {
                    function2Confirm = true ;
                    continueOrNot = true ;
                } // quit
                
                else {
                    string fileName = "input" + FileNumber + ".txt" ;
                    input.open( fileName.c_str() ) ;
                    if ( input.is_open() ) {
                        function2Confirm = true ;
                        continueOrNot = true ;
                    } // open successfully
                    else cout << "*****  " << fileName << " does not exist!  *****" << endl ;
                } // open file and input data to BST
            } while ( ! function2Confirm ) ;
            
            Count = 0 ;
            FileNumber = "0" ;
            input.close() ;
            output.close() ;
        } // AVL Tree
    } while( continueOrNot ) ;
}
