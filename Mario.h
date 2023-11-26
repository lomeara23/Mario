#include <cstdlib>

class Mario{
    private:
        int lives;
        int coins;
        int powerLevel;
        int killstreak;

        int currLevel;

        int x;
        int y;

    public:
        Mario();
        Mario(int startingLives, int startingX, int startingY);
        ~Mario();

        int getX();
        int getY();
        int getCurrentLevel();

        void setX(int x);
        void setY(int y);
        void nextLevel();

        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();

        void addCoin();
        int getCoins();
        void powerUp();

        bool fightMinion(char minionType);
        bool fightBoss();

        void powerDown();
        void loseLife();
        int getLives();

        bool buggedFightBoss();

        int getPowerLevel();
};