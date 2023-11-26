#include "Mario.h"
#include "Level.h"
#include <iostream>
#include <fstream>

using namespace std;

class World{
    private:
        Mario *player;
        Level **levels;

        fstream out;

        string outputFile;

        bool winLoss;

        int levelCount;
        int levelDim;
        int initLives;
        int coinPerc;
        int goombaPerc;
        int koopaPerc;
        int shroomPerc;

        int totalMoves;

        void generateWorld();

        void handleAction(int tileX, int tileY, int level);

    public:     
        World();
        World(int levelCount, int levelDim, int initLives,
              int coinPerc, int goombaPerc, int koopaPerc,
              int shroomPerc, string output);
        ~World();

        bool isPlaying;

        void writeWorld();

        void moveMario();

        Level* getLevel(int level);

        int getTotalMoves();

        void closeFile();

        bool getWinLoss();
};