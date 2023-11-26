#include "MarioFileReader.h"

// Default constructor & destructor
MarioFileReader::MarioFileReader(){
    percArr = new int[8];
}
MarioFileReader::~MarioFileReader(){
    delete [] percArr;
}

// Convert a text file to an HTML webpage with the original
// text in bold then the translated text italicized
bool MarioFileReader::readInputs(string inFile){    
    ifstream in;
    string line;
    int currLine = 0;
    int percSum = 0;
    in.open(inFile);

    while(getline(in, line) && currLine < 8){ // Iterate through the read file line by line
        percArr[currLine] = stoi(line);
        currLine++;
    }

    in.close();

    for(int i = 3 ; i < 8 ; i++){
        percSum += percArr[i];
    }
    return (percSum == 100);
}

int MarioFileReader::getPerc(int arrPos){
    return percArr[arrPos];
}