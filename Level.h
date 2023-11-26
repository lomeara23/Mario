#include <cstdlib>

class Level{
    private: 
        char **level;

        int coinCount;
        int noneCount;
        int goombaCount;
        int koopaCount;
        int shroomCount;
        void getCounts(int levelDim, int coinPerc, int goombaPerc,
                       int koopaPerc, int shroomPerc);

        void initGrid(int levelDim, bool hasWarpPipe);
    
    public: 
        Level();
        Level(int dimensions, int coinPerc, int goombaPerc,
              int koopaPerc, int shroomPerc, bool hasWarpPipe=true);
        ~Level();
        char getTile(int x, int y);
        void setTile(int x, int y, char newChar);

};