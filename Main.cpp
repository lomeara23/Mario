#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "MarioFileReader.h"
#include "World.h"

using namespace std;

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    MarioFileReader *fr = new MarioFileReader();
    if(fr->readInputs(argv[1])){
        World *testWorld = new World(fr->getPerc(0),
        fr->getPerc(1),fr->getPerc(2),fr->getPerc(3),
        fr->getPerc(5),fr->getPerc(6),fr->getPerc(7),
        argv[2]);

        while(testWorld->isPlaying){
            testWorld->moveMario();
        }
        testWorld->closeFile();
        ofstream out;
        out.open(argv[2], ios::app);
        if(testWorld->getWinLoss()){
            out << "Mario won in ";
        } else {
            out << "Mario lost in ";
        }
        out << testWorld->getTotalMoves() << " moves.";
        out.close();
        
        delete testWorld;
    } else {
        cout << "World gen ratios do not add to 100%!" << endl;
    }
    delete fr;
    return 0;
}
