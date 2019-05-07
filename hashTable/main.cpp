// 10627130 ªL«a¨} & 10627131 §õ®mÞ³ // Code Blocks 17.12
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <time.h>
#include <math.h>

using namespace std;

typedef struct DataStruct {
	char id[10];
	char name[10];
	unsigned char score[6];
	float average;
	int hValue = 0;
} DataStruct;

typedef struct Temp {
	char id[10];
	char name[10];
	unsigned char score[6];
	float average;
} Temp;

static string FileNumber = "0";
static int Count = 0;
static int Command = 0;
static fstream input;
static fstream output;

class function1 {
	DataStruct temp;
public:
	vector<DataStruct> dataBase;

	void ReadTxt() {
		string outputName = "input" + FileNumber + ".bin";
		output.open( outputName.c_str(), fstream::out | fstream::binary );
		char rBuf[255];

		while ( input.getline( rBuf, 255, '\n' ) ) {
			string temp;
			Temp tempData;
			int cNo = 0, pre = 0, pos = 0;

			Count++;
			temp.assign( rBuf );
			pos = temp.find_first_of( '\t', pre );

			while ( pos != string::npos ) {
				switch ( ++cNo ) {
					case 1: strcpy( tempData.id, temp.substr( pre, pos - pre ).c_str() );
						break;
					case 2: strcpy( tempData.name, temp.substr( pre, pos - pre ).c_str() );
						break;
					default: tempData.score[cNo - 3] = atoi( temp.substr( pre, pos - pre ).c_str() );
						break;
				} // end switch

				pre = ++pos;
				pos = temp.find_first_of( '\t', pre );
			} // end inner while

			pos = temp.find_last_of( '\t' );
			tempData.average = atof( temp.substr( pos + 1 ).c_str() );
			output.write( (char*)& tempData, sizeof( tempData ) );
		} // end outer while
	} // ReadTxt()

	void ReadBin() {
        dataBase.clear();
		Temp tempData;
		DataStruct data;
		int studentNo = 0;

		input.seekg( 0, input.end );
		studentNo = input.tellg() / sizeof( tempData );
		input.seekg( 0, input.beg );

		for ( int i = 0; i < studentNo; i++ ) {
			input.read( (char*)& tempData, sizeof( tempData ) );
			//cout << "[" << i+1 << "]" << tempData.id << ", " << tempData.name << endl ;
			strcpy( data.id, tempData.id );
			strcpy( data.name, tempData.name );
			for ( int j = 0; j < 6; j++ ) data.score[j] = tempData.score[j];
			data.average = tempData.average;
			dataBase.push_back( data );
		} // print

		cout << endl;
	} // ReadBin()
};

class function2 : public function1 {
public:
	int FindPrimeNumber( int dataSize ) {
		for ( bool findprime = false; findprime != true; dataSize++ ) {
			for ( int i = 2; i <= dataSize; i++ ) {
				if ( dataSize % i == 0 ) {
					if ( dataSize == i ) {
						findprime = true;
						return dataSize;
					} // return
					else break;
				}  // if
			} // for
		} // for

		return dataSize;
	} //FindPrimeNumber()

	unsigned long long getHValue( char id[10] ) {
		unsigned long long hValue = 1;

		for ( int i = 0; i < 8; i++ ) {
			if ( id[i] != '\0' )
				hValue = hValue * (int)id[i];
		} // multiply the id

		return hValue;
	} //getHvalue

	void BuildHashTableX() {
		float size = ( dataBase.size() * 1.2 ) + 1;
		size = FindPrimeNumber( (int)size );
		vector<DataStruct> X;
		X.resize( (int)size );
		int tempHValue = 0;
		int times = 0;
		float average = 0;

		for ( int i = 0; i < dataBase.size(); i++ ) {
			tempHValue = getHValue( dataBase[i].id ) % (int)size;

			//cout << tempHValue << endl ;

			dataBase[i].hValue = tempHValue;
			times++;
			while ( X[tempHValue].hValue != 0 ) {
				tempHValue++;
				if ( tempHValue == size ) tempHValue = tempHValue - (int)size;
				times++;
			} // while
			X[tempHValue] = dataBase[i];
		} // put into hashTable

		// for ( int i = 0 ; i < X.size() ; i++ ) cout << X[i].id << " " << X[i].name << " " << (int)X[i].score[0] << " " << X[i].average << endl ;
		cout << "Hash Table X has been created." << endl;
		average = (float)times / (float)dataBase.size();
		UnsuccessfulSearch( X );
		cout << "successful search: " << average << " comparisons on average." << endl<< endl;
		PrintHashTable( size, X );
	} // BuildHashTableX()

	void UnsuccessfulSearch( vector<DataStruct> table ) {
        int j = 0;
		int times = 0;
		float average = 0;
		for ( int i = 0; i < table.size(); i++ ) {
            j = i;
			while ( 1 ) {
				if ( j == table.size() ) j = 0;
                if ( table[j].hValue == 0 ) break;
                j++;
                times++;
			} // while

		} // for

		average = (float)times / (float)table.size();
		cout << "unsuccessful search: " << average << " comparisons on average." << endl;
	} // UnsuccessfulSearch()

	void PrintHashTable( int TableSize, vector<DataStruct> X ) {
		output.open( ( "linear" + FileNumber + ".txt" ).c_str(), fstream::out );
		output << " --- Hash Ta-----------------------------------------------------------------------------------------------ble X --- (linear probing)" << endl;

		for ( int i = 0; i < TableSize; i++ ) {
			if ( i < 10 ) output << "[  " << i << "]";
			else if ( i >= 10 ) output << "[ " << i << "]";
			if ( X[i].hValue != 0 ) {
				if ( X[i].hValue < 10 ) output << "          " << X[i].hValue;
				else if ( X[i].hValue >= 10 ) output << "         " << X[i].hValue;
				if ( X[i].id[7] != '\0' ) output << ",   ";
				else if ( X[i].id[7] == '\0' ) output << ",    ";
				output << X[i].id << ",\t\t" << X[i].name << ",\t\t" << X[i].average << endl;
			} // if()
			else output << endl;
		} // for
	} // PrintHashTable()
};

class function3 : public function2 {
public:
	void BuildHashTableY() {
		float size = ( dataBase.size() * 1.2 ) + 1;
		size = FindPrimeNumber( (int)size );
		vector<DataStruct> Y;
		Y.resize( (int)size );
		int tempHValue = 0;
		int step = 0;
		int times = 0;
		float average = 0;

		for ( int i = 0; i < dataBase.size(); i++ ) {
			int tempHValue = getHValue( dataBase[i].id ) % (int)size;

			dataBase[i].hValue = tempHValue;
			if ( Y[tempHValue].hValue != 0 ) {
				int highestStep = FindPrimeNumber( (int)( dataBase.size() / 3 + 1 ) );

				step = highestStep - ( getHValue( dataBase[i].id ) % highestStep );
				//cout<< dataBase[i].hValue << "...." <<getHValue( dataBase[i].id ) % highestStep <<" ...."<<highestStep << "....."<<tempHValue << dataBase[i].name << endl;
			} // step

			times++;
			while ( Y[tempHValue].hValue != 0 ) {
				tempHValue = step + tempHValue;
				if ( tempHValue >= size ) tempHValue = tempHValue - size;
				times++;
			} // while
			Y[tempHValue] = dataBase[i];
		} // put into hashTable
		cout << "Hash Table Y has been created." << endl;
		average = (float)times / (float)dataBase.size();
		cout << "successful search: " << average << " comparisons on average." << endl << endl;
		PrintHashTable( size, Y );
	} // BuildHashTableY()

	void PrintHashTable( int TableSize, vector<DataStruct> X ) {
		output.open( ( "double" + FileNumber + ".txt" ).c_str(), fstream::out );
		output << " --- Hash Table Y --- (double hashing)" << endl;

		for ( int i = 0; i < TableSize; i++ ) {
			if ( i < 10 ) output << "[  " << i << "]";
			else if ( i >= 10 ) output << "[ " << i << "]";
			if ( X[i].hValue != 0 ) {
				if ( X[i].hValue < 10 ) output << "          " << X[i].hValue;
				else if ( X[i].hValue >= 10 ) output << "         " << X[i].hValue;
				output << ",   " << X[i].id << ",      " << X[i].name << ",      " << X[i].average << endl;
			} // if()
			else output << endl;
		} // for
	} // PrintHashTable()
};

class function4 : public function2 {
public:
	void BuildHashTableZ() {
		float size = ( dataBase.size() * 1.2 ) + 1;
		size = FindPrimeNumber( (int)size );
		vector<DataStruct> Z;
		Z.resize( (int)size );
		int tempHValue = 0;
		int step = 1;
		int times = 0;
		int save = 0;
		int plusN = 0;
		float average = 0;

		for ( int i = 0; i < dataBase.size(); i++ ) {
			int tempHValue = getHValue( dataBase[i].id ) % (int)size;

			dataBase[i].hValue = tempHValue;

			times++;
			save = tempHValue;
			plusN = 1;
			step = 1;

            if ( Z[tempHValue].hValue == 0 ) {
                    Z[tempHValue] = dataBase[i];
                    continue;
            } // block is empty

			while ( Z[tempHValue].hValue !=0 && plusN <=(Z.size()-1)/2 ) {

				tempHValue = save+step; // plus
				times++;
				if ( tempHValue >= Z.size() ) {
                    tempHValue = tempHValue - Z.size();
                    if ( Z[tempHValue].hValue == 0 ) {
                        Z[tempHValue] = dataBase[i];
                        break;
                    }
				} // out of bound
				else {
                    if ( Z[tempHValue].hValue == 0 ) {
                        Z[tempHValue] = dataBase[i];
                        break;
                    }
				} // !out of bound

				/*tempHValue = save-step; // minus
				times++;
				if ( tempHValue < 0 ) {
                    tempHValue = size - tempHValue;
                    if ( Z[tempHValue].hValue == 0 ) {
                        Z[tempHValue] = dataBase[i];
                        break;
                    }
				} // less than zero
				else {
                    if ( Z[tempHValue].hValue == 0 ) {
                        Z[tempHValue] = dataBase[i];
                        break;
                    }
				} // !less than zero*/

                plusN++;
				step = plusN*plusN;
				cout<< step<< endl;
				if ( step >= Z.size() ) step = step % Z.size();
				//cout<< step<<endl;
				times++;
			} // while
		} // put into hashTable


		cout << "Hash Table Z has been created." << endl;
		average = (float)times / (float)dataBase.size();
		cout << "successful search: " << average << " comparisons on average." << endl << endl;
		PrintHashTable( size, Z );
	} // BuildHashTableY()

	void PrintHashTable( int TableSize, vector<DataStruct> X ) {
		output.open( ( "quadratic" + FileNumber + ".txt" ).c_str(), fstream::out );
		output << " --- Hash Table Z --- (quadratic probing)" << endl;

		for ( int i = 0; i < TableSize; i++ ) {
			if ( i < 10 ) output << "[  " << i << "]";
			else if ( i >= 10 ) output << "[ " << i << "]";
			if ( X[i].hValue != 0 ) {
				if ( X[i].hValue < 10 ) output << "          " << X[i].hValue;
				else if ( X[i].hValue >= 10 ) output << "         " << X[i].hValue;
				output << ",   " << X[i].id << ",      " << X[i].name << ",      " << X[i].average << endl;
			} // if()
			else output << endl;
		} // for
	} // PrintHashTable()
};

int main() {
	bool continueOrNot = false;

	do {
		function1 One;
		function2 Two;
		function3 Three;
		function4 Four;
		cout << "**********************************************" << endl; // welcome message
		cout << "*****               DS2ex03              *****" << endl;
		cout << "***** 0 : Quit                           *****" << endl;
		cout << "***** 1 : Read and convert data          *****" << endl;
		cout << "***** 2 : Linear probing                 *****" << endl;
		cout << "***** 3 : Double hash                    *****" << endl;
		cout << "***** 4 : Quadratic probing              *****" << endl;
		cout << "**********************************************" << endl;
		cout << endl << "Please enter your choice:" << endl;

		cin >> Command; // read in user command
		cout << endl;

		if ( Command == 0 ) { // bye :(((
			cout << "Bye :(((" << endl;
			return 0;
		} // quit

		else if ( Command > 4 || Command < 0 ) {
			cout << "Error command! please enter an acceptable command:" << endl << endl;
			continueOrNot = true;
		} // wrong command

		else if ( Command == 1 ) {
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
					input.open( binFileName.c_str(), fstream::in | fstream::binary );

					if ( input.is_open() ) {
						One.ReadBin();
						function1Confirm = true;
						continueOrNot = true;
					} // binary file open successfully

					else {
						input.open( txtFileName.c_str(), fstream::in );
						if ( input.is_open() ) {
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

			input.close();
			output.close();
			Count = 0;
			FileNumber = "0";
		} // text2Binary or readBinary

		else if ( Command == 2 ) {
			bool function2Confirm = false;

			do {
				cout << "Please enter the file you want to proceed a linear probing or [0] to quit:" << endl;
				cin >> FileNumber;

				if ( FileNumber == "0" ) {
					function2Confirm = true;
					continueOrNot = true;
				} // quit

				else {
					string fileName = "input" + FileNumber + ".bin";
					input.open( fileName.c_str(), fstream::in | fstream::binary );

					if ( input.is_open() ) {
						Two.ReadBin();
						Two.BuildHashTableX();
						function2Confirm = true;
						continueOrNot = true;
					} // open successfully

					else {
						cout << "*****  " << fileName << " does not exist!  *****" << endl;
						cout << "*****  Please proceed function 1 first !   *****" << endl;
					} // open failed
				} // open file and input data to build hash x
			} while ( !function2Confirm );

			input.close();
			output.close();
			Count = 0;
			FileNumber = "0";
		} // linear probing

		else if ( Command == 3 ) {
			bool function3Confirm = false;

			do {
				cout << "Please enter the file you want to proceed a double hash or [0] to quit:" << endl;
				cin >> FileNumber;

				if ( FileNumber == "0" ) {
					function3Confirm = true;
					continueOrNot = true;
				} // quit

				else {
					string fileName = "input" + FileNumber + ".bin";
					input.open( fileName.c_str(), fstream::in | fstream::binary );

					if ( input.is_open() ) {
						Three.ReadBin();
						Three.BuildHashTableY();
						function3Confirm = true;
						continueOrNot = true;
					} // open successfully

					else {
						cout << "*****  " << fileName << " does not exist!  *****" << endl;
						cout << "*****  Please proceed function 1 first !   *****" << endl;
					} // open failed
				} // open file and input data to build hash y
			} while ( !function3Confirm );

			input.close();
			output.close();
			Count = 0;
			FileNumber = "0";
		} // double hashing

		else if ( Command == 4 ) {
			bool function4Confirm = false;

			do {
				cout << "Please enter the file you want to proceed a quadratic probing or [0] to quit:" << endl;
				cin >> FileNumber;

				if ( FileNumber == "0" ) {
					function4Confirm = true;
					continueOrNot = true;
				} // quit

				else {
					string fileName = "input" + FileNumber + ".bin";
					input.open( fileName.c_str(), fstream::in | fstream::binary );

					if ( input.is_open() ) {
						Four.ReadBin();
						Four.BuildHashTableZ();
						function4Confirm = true;
						continueOrNot = true;
					} // open successfully

					else {
						cout << "*****  " << fileName << " does not exist!  *****" << endl;
						cout << "*****  Please proceed function 1 first !   *****" << endl;
					} // open failed
				} // open file and input data to build hash y
			} while ( !function4Confirm );

			input.close();
			output.close();
			Count = 0;
			FileNumber = "0";
		} // quadratic probing
	} while ( continueOrNot );
} // main
