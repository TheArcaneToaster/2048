#include <iostream>

#include "game.hpp"

int main()
{
    GAME gra;
    char decisions = 0;

    while(gra.GAME_OVER == GAME::no_problemo)
    {
        std::cout << "\033[32mWhat move do you want to make (u/d/l/r/q):\033[0m ";
        std::cin >> decisions;

        if (decisions == 'q')
        {
            gra.GAME_OVER = GAME::quitter;
            break;
        }

        gra.make_move(decisions);
        gra.show_board();
    }

    gra.credits();

    return 0;
}