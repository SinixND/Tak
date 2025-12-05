#ifndef IG20251205132519
#define IG20251205132519

struct Game{
    GameSettings gameSettings;
    MatchConstants matchConstants;
    Players players;
    Stones stones;
    Stacks stacks;
    Board board;
};

Game initGame();
Game run();
void deinitGame();

#endif