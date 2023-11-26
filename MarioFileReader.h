#include <iostream>
#include <fstream>

using namespace std;

class MarioFileReader
{
    public:
        MarioFileReader();
        ~MarioFileReader();
        bool readInputs(string inFile);
        int getPerc(int arrPos);
    private:
        bool checkFileFormat(string file);
        int *percArr;
};