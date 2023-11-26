#include "Level.h"

#include <iostream>
using namespace std;

// Default constructor & destructor
Level::Level(){
}
Level::~Level(){
}

Level::Level(int levelDim, int coinPerc, int goombaPerc,
             int koopaPerc, int shroomPerc, bool hasWarpPipe){
    level = new char*[levelDim];
    for(int i = 0 ; i < levelDim ; i++){
        level[i] = new char[levelDim];
    }
    getCounts(levelDim, coinPerc, goombaPerc, koopaPerc, shroomPerc);
    initGrid(levelDim, hasWarpPipe);
}

// Fill all levels with empty tiles, then populate it with items
void Level::initGrid(int levelDim, bool hasWarpPipe){
    for(int x = 0 ; x < levelDim ; x++){
        for(int y = 0 ; y < levelDim ; y++){
            level[x][y] = 'x';
        }
    }
    
    for(int totalCoins = 0 ; totalCoins < coinCount ; totalCoins++){
        int coinX = rand() % levelDim;
        int coinY = rand() % levelDim;

        while (level[coinX][coinY] != 'x'){
            coinX++;
            if(coinX == levelDim){
                coinX = 0;
                coinY++;
                if(coinY == levelDim){
                    coinY = 0;
                }
            }
        }
        level[coinX][coinY] = 'c';
    }

    for(int totalGoombas = 0 ; totalGoombas < goombaCount ; totalGoombas++){
        int goombaX = rand() % levelDim;
        int goombaY = rand() % levelDim;

        while (level[goombaX][goombaY] != 'x'){
            goombaX++;
            if(goombaX == levelDim){
                goombaX = 0;
                goombaY++;
                if(goombaY == levelDim){
                    goombaY = 0;
                }
            }
        }
        level[goombaX][goombaY] = 'g';
    }

    for(int totalKoopas = 0 ; totalKoopas < koopaCount ; totalKoopas++){
        int koopaX = rand() % levelDim;
        int koopaY = rand() % levelDim;

        while (level[koopaX][koopaY] != 'x'){
            koopaX++;
            if(koopaX == levelDim){
                koopaX = 0;
                koopaY++;
                if(koopaY == levelDim){
                    koopaY = 0;
                }
            }
        }
        level[koopaX][koopaY] = 'k';
    }

    for(int totalShrooms = 0 ; totalShrooms < shroomCount ; totalShrooms++){
        int shroomX = rand() % levelDim;
        int shroomY = rand() % levelDim;

        while (level[shroomX][shroomY] != 'x'){
            shroomX++;
            if(shroomX == levelDim){
                shroomX = 0;
                shroomY++;
                if(shroomY == levelDim){
                    shroomY = 0;
                }
            }
        }
        level[shroomX][shroomY] = 'm';
    }

    int bossX = rand() % levelDim;
    int bossY = rand() % levelDim;
    level[bossX][bossY] = 'b';

    if(hasWarpPipe){
        int pipeX = rand() % levelDim;
        int pipeY = rand() % levelDim;
        level[pipeX][pipeY] = 'w';
    }
}

// Calculate the required number of each item on the map
void Level::getCounts(int levelDim, int coinPerc, int goombaPerc,
                      int koopaPerc, int shroomPerc){
    coinCount = (int)((coinPerc/100.0)*levelDim*levelDim);
    goombaCount = (int)((goombaPerc/100.0)*levelDim*levelDim);
    koopaCount = (int)((koopaPerc/100.0)*levelDim*levelDim);
    shroomCount = (int)((shroomPerc/100.0)*levelDim*levelDim);
}

char Level::getTile(int x, int y){
    return level[x][y];
}

void Level::setTile(int x, int y, char newChar){
    level[x][y] = newChar;
}