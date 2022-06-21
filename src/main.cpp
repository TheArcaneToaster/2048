#include <iostream>

#include "game.hpp"

int main()
{
    GAME gra;
    char decisions = 0;

    while(decisions != 'q' || gra.GAME_OVER == true)
    {
        std::cout << "\033[32mWhat move do you want to make (u/d/l/r/q):\033[0m ";
        std::cin >> decisions;

        gra.make_move(decisions);
        gra.show_board();
    }

    if (gra.bingo())
        std::cout << "\033[1;32m!---!---YOU'VE WON---!---!\033[0m" << std::endl;
    else    
        std::cout << "\033[1;31m!---!---YOU'VE LOST---!---!\033[0m" << std::endl;


    return 0;
}

/* TODO
check zeros 
>game fail

przed wykonaniem ruchu sprawdzić, czy coś się
*/