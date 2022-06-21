#include <iostream>

#include "game.hpp"

int main()
{
    GAME gra;
    char choice = 0;

    while(choice != 'q' || gra.finished == true)
    {
        std::cin >> choice;

        gra.make_move(choice);
        gra.show_board();
    }

    if (gra.bingo())
        std::cout << "\033[1;32m!---!---YOU'VE WON---!---!\033[0m" << std::endl;
    else    
        std::cout << "\033[1;31m!---!---YOU'VE LOST---!---!\033[0m" << std::endl;


    return 0;
}

/* TODO
GAME::move_up()
BOARD::column_up()
GAME::move_down()
BOARD::column_up()
GAME::make_move 
    -specify move 
*/