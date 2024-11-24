#include "game.h"

int main()
{
    Game game;
    game.awake();

    while (game.isRunning())
    {
        
        game.pollEvents();
        game.startFrame();
        //Update
        game.earlyUpdate();
        game.update();
        game.lateUpdate();
        //Render
        game.render();
        game.calculateDt();
    }

    return 0;
}