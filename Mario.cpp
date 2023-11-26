#include "Mario.h"

// Default constructor & destructor
Mario::Mario(){
    lives = 3;
    coins = 0;
    powerLevel = 0;
    killstreak = 0;
    currLevel = 0;
    x = 0;
    y = 0;
}
Mario::~Mario(){
}

Mario::Mario(int startingLives, int startingX, int startingY){
    lives = startingLives;
    coins = 0;
    powerLevel = 0;
    killstreak = 0;
    currLevel = 0;
    x = startingX;
    y = startingY;
}

int Mario::getCurrentLevel(){
    return currLevel;
}
void Mario::nextLevel(){
    currLevel++;
}

int Mario::getX(){
    return x;
}
void Mario::setX(int newX){
    x=newX;
}

int Mario::getY(){
    return y;
}
void Mario::setY(int newY){
    y=newY;
}

void Mario::addCoin(){
    coins++;
    if(coins == 20){
        coins = 0;
        lives++;
        killstreak = 0;
    }
}
void Mario::powerUp(){
    if(powerLevel != 2){
        powerLevel++;
    }
}

bool Mario::fightMinion(char minionType){
    int winPerc = 50;
    switch(minionType){
        case 'g':
            winPerc = 80;
            break;
        case 'k':
            winPerc = 65;
            break;
    }
    if(rand() % 100 < winPerc){
                killstreak++;
                if(killstreak == 7){
                    killstreak = 0;
                    lives++;
                }
                return true;
            } else {
                return false;
            }
}

bool Mario::fightBoss(){
    if(rand() % 100 < 50){
        killstreak++;
        if(killstreak == 7){
            killstreak = 0;
            lives++;
        }
        return true;
    } else {
        return false;
    }
}

void Mario::powerDown(){
    if (powerLevel == 0){
        loseLife();
    } else {
        powerLevel--;
    }
}

void Mario::loseLife(){
    lives--;
    killstreak = 0;
}

int Mario::getLives(){
    return lives;
}

bool Mario::buggedFightBoss(){
    (rand() % 100);
}

int Mario::getPowerLevel(){
    return powerLevel;
}

int Mario::getCoins(){
    return coins;
}