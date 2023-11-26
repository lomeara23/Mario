#include "World.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

// Default constructor & destructor
World::World(){
    isPlaying = true;
    levelCount = 5;
    levelDim = 5;
    initLives = 3;
    coinPerc = 20;
    goombaPerc = 15;
    koopaPerc = 10;
    shroomPerc = 15;
    outputFile = "./log.txt";
    totalMoves = 0;
    generateWorld();
}

World::World(int levelCount, int levelDim, int initLives,
              int coinPerc, int goombaPerc, 
              int koopaPerc, int shroomPerc, string outputFile){
    isPlaying = true;
    this->levelCount = levelCount;
    this->levelDim = levelDim;
    this->initLives = initLives;
    this->coinPerc = coinPerc;
    this->goombaPerc = goombaPerc;
    this->koopaPerc = koopaPerc;
    this->shroomPerc = shroomPerc;
    this->outputFile = outputFile;
    this->totalMoves = 0;
    generateWorld();
}

World::~World(){
    delete player;
    for(int i = 0 ; i < levelCount ; i++){
        delete[] levels[i];
    }
    delete[] levels;
    out.close();
}

// Creates the World, generating randomized levels according to the paramters provided tin the input file
void World::generateWorld(){
    out.open(outputFile, ios::app);
    levels = new Level*[levelCount];
    for(int i = 0 ; i < levelCount-1 ; i++){
        levels[i] = new Level(levelDim, coinPerc, goombaPerc, koopaPerc, shroomPerc);
    }
    levels[levelCount-1] = new Level(levelDim, coinPerc, goombaPerc, koopaPerc, shroomPerc, false);
    player = new Mario(initLives, rand() % levelDim, rand() % levelDim);

}

// Handle responses to each item Mario encounters
void World::handleAction(int tileX, int tileY, int level){
    char tileChar = levels[level]->getTile(tileX, tileY);
    switch(tileChar){
        case 'c':
            levels[level]->setTile(tileX,tileY,'h');
            player->addCoin();
            out << "Mario collected a coin. ";
            totalMoves++;
            break;

        case 'm':
            levels[level]->setTile(tileX,tileY,'h');
            player->powerUp();
            out << "Mario ate a mushroom. ";
            totalMoves++;
            break;

        case 'g':
            if(player->fightMinion(tileChar)){
                levels[level]->setTile(tileX,tileY,'h');
                out << "Mario fought a goomba and won. ";
                totalMoves++;
            } else {
                player->powerDown();
                out << "Mario fought a goomba and lost. ";
                totalMoves++;
            }
            break;
        case 'k':
            if(player->fightMinion(tileChar)){
                levels[level]->setTile(tileX,tileY,'h');
                out << "Mario fought a koopa and won. ";
                totalMoves++;
            } else {
                player->powerDown();
                out << "Mario fought a koopa and lost. ";
                totalMoves++;
            }
            break;

        case 'b':
            while(!player->fightBoss() && isPlaying){
                out << "Mario fought the boss and lost. ";
                totalMoves++;
                if(player->getPowerLevel() == 0 || player->getPowerLevel() == 1){
                    player->loseLife();
                    if(player->getLives() == 0){
                        isPlaying = false;
                        winLoss = false;
                        break;
                    }
                } else {
                    player->powerDown();
                    player->powerDown();
                }
            }
            if(isPlaying){
                out << "Mario fought the boss and won. ";
                totalMoves++;
                if(player->getCurrentLevel() == levelCount-1){
                    isPlaying = false;
                    winLoss = true;
                }
                player->nextLevel();
            }
            
            break;

        case 'w':
            player->nextLevel();
            out << "Mario warped. ";
            totalMoves++;
            break;

        default:
            totalMoves++;
            break;
    }
}

Level* World::getLevel(int level){
    return levels[level];
}

// Write the level map to file
void World::writeWorld(){
    for(int row = 0 ; row < levelDim ; row++){
        for(int col = 0 ; col < levelDim ; col++){
            out << getLevel(player->getCurrentLevel())->getTile(col,row);
        }
    out << endl;
    }
}

// Move Mario to a new tile then check if any action needs to be taken
void World::moveMario(){
    if(player->getLives() == 0){
        isPlaying = false;
        winLoss = false;
        return;
    }
    writeWorld();
    out << "Level: " << player->getCurrentLevel() << ", (" << player->getX() << "," << player->getY() << "), Power Level: " << player->getPowerLevel() << ", ";   
    levels[player->getCurrentLevel()]->setTile(player->getX(),player->getY(),'x');
    int dir = rand() % 4;
    string direction;
    switch(dir){
        case 0:
            player->setY((player->getY()+1) % levelDim);
            direction = "UP";
            break;
        case 1:
            player->setX((player->getX()+1) % levelDim);
            direction = "RIGHT";
            break;
        case 2:
            player->setY(((player->getY()-1)+levelDim) % levelDim);
            direction = "DOWN";
            break;
        case 3:
            player->setX(((player->getX()-1)+levelDim) % levelDim);
            direction = "LEFT";
            break;
    }
    handleAction(player->getX(), player->getY(), player->getCurrentLevel());
    out << "Lives: " << player->getLives() << ", coins: " << player->getCoins() << ", next direction: " << direction << ", current move: " << totalMoves << endl;
}

int World::getTotalMoves(){
    return totalMoves;
}


void World::closeFile(){
    out.close();
}

bool World::getWinLoss(){
    return winLoss;
}