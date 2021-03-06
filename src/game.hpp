#include <random>

#include "interface.hpp"

unsigned BOARD::highest_on_board() const
{
    return highest;
}

void BOARD::show_board() const
{
    std::cout << std::endl;

    for (unsigned i = 0; i < DIMENSION; i ++)
    {
        for (unsigned j = 0; j < DIMENSION; j++)
        {
            if (board[i][j] == 0)
                std::cout << "\033[34m";
            else if (board[i][j] == 2048)
                std::cout << "\033[1;32m";
            else if (board[i][j] > 2048)
                std::cout << "\033[31m";
            else if (board[i][j] >= 1000 && board[i][j] <= 1500)
                std::cout << "\033[33m";
            else if (board[i][j] > 1000 && board[i][j] < 2048)
                std::cout << "\033[35m";

            std::cout << '\t' << board[i][j];

                std::cout << "\033[0m";
        }
        std::cout << std::endl << std::endl;
    }
}

void BOARD::count_zeroes_on_board()
{
    unsigned zera = 0;

    for (unsigned i = 0; i < DIMENSION; i++)
    {
            for (unsigned j = 0; j < DIMENSION; j++)
            {
                if (board[i][j] == 0)
                    ++zera;
            }
    }
    zeroes = zera;
}

void BOARD::update_board()
{
    find_highest_on_board();
    count_zeroes_on_board();
}

bool BOARD::add_tile()
{
    update_board();
    if (zeroes == 0)
    {
        return false;
    }

    unsigned i = rand() % DIMENSION;
    unsigned j = rand() % DIMENSION;

    while (board[i][j] != 0)
    {
        i = rand() % DIMENSION;
        j = rand() % DIMENSION;
    }

    board[i][j] = 2;
    return true;
}

void BOARD::find_highest_on_board()
{
    for (int i = 0; i < DIMENSION - 1; i ++)
    {
        for (int j = 0; j < DIMENSION - 1; j++)
        {
            if (board[i][j] > highest)
                highest = board[i][j];
        }
    }
}

void BOARD::row_right(unsigned row)
{
    int k;

    for (unsigned i = DIMENSION - 1; i >= 1; i--)
    {
        k = i - 1;
        while (k > 0 && board[row][k] == 0)  //non-zero value to left
            --k;

        if (board[row][i] == 0 && (board[row][i+1] != 0 || i == DIMENSION -1)) //we are watching zero 
        {
            if (board[row][k] == 0)
                continue;
            else
            {
                board[row][i] = board[row][k];
                board[row][k] = 0;

                row_right(row);
            }
        }
        else    //we're watching non-zero value
        {
            if (board[row][k] == board[row][i])
            {
                board[row][i] += board[row][k];
                board[row][k] = 0;
            }
        }
    }
}

void BOARD::row_left(unsigned row)
{
    int k;

    for (unsigned i = 0; i <= DIMENSION -2; i++)
    {
        k = i + 1;
        while (k < DIMENSION -1 && board[row][k] == 0)  //non-zero value to left
            ++k;

        if (board[row][i] == 0 && (i == 0 || board[row][i-1] != 0 )) //we are watching zero 
        {
            if (board[row][k] == 0)
                continue;
            else
            {
                board[row][i] = board[row][k];
                board[row][k] = 0;

                row_left(row);
            }
        }
        else    //we're watching non-zero value
        {
            if (board[row][k] == board[row][i])
            {
                board[row][i] += board[row][k];
                board[row][k] = 0;
            }
        }
    }
}

void BOARD::column_down(unsigned column)
{
    int k;

    for (unsigned i = DIMENSION - 1; i >= 1; i--)
    {
        k = i - 1;
        while (k > 0 && board[k][column] == 0)  //non-zero value to left
            --k;

        if (board[i][column] == 0 && (board[i+1][column] != 0 || i == DIMENSION -1)) //we are watching zero 
        {
            if (board[k][column] == 0)
                continue;
            else
            {
                board[i][column] = board[k][column];
                board[k][column] = 0;

                column_down(column);
            }
        }
        else    //we're watching non-zero value
        {
            if (board[k][column] == board[i][column])
            {
                board[i][column] += board[k][column];
                board[k][column] = 0;
            }
        }
    }
}

void BOARD::column_up(unsigned column)
{
    int k;

    for (unsigned i = 0; i <= DIMENSION -2; i++)
    {
        k = i + 1;
        while (k < DIMENSION -1 && board[k][column] == 0)  //non-zero value to left
            ++k;

        if (board[i][column] == 0 && (i == 0 || board[i-1][column] != 0 )) //we are watching zero 
        {
            if (board[k][column] == 0)
                continue;
            else
            {
                board[i][column] = board[k][column];
                board[k][column] = 0;

                column_up(column);
            }
        }
        else    //we're watching non-zero value
        {
            if (board[k][column] == board[i][column])
            {
                board[i][column] += board[k][column];
                board[k][column] = 0;
            }
        }
    }
}

GAME::GAME() : GAME_OVER(no_problemo)
{
    update_board();

    add_tile();
    add_tile();
    show_board();
}

void GAME::add_tile()
{
    if (!BOARD::add_tile())
    {
        GAME_OVER = no_space;
    }
}

void GAME::move_right()
{
    for (unsigned row = 0; row < this->return_dimension(); row++)
        this->row_right(row);
}

void GAME::move_left()
{
    for (unsigned row = 0; row < this->return_dimension(); row++)
        this->row_left(row);
}

void GAME::move_down()
{
    for (unsigned column = 0; column < this->return_dimension(); column++)
        this->column_down(column);
}

void GAME::move_up()
{
    for (unsigned column = 0; column < this->return_dimension(); column++)
        this->column_up(column);
}

void GAME::make_move(char move)
{
    if (GAME_OVER != no_problemo)
        return;

    if (move == 'r')
        move_right();
    else if (move == 'l')
        move_left();
    else if (move == 'd')
        move_down();
    else if (move == 'u')
        move_up();
    else return;

    update_board();

    if (highest_on_board() == oczko)
        GAME_OVER = winner;
    else if (highest_on_board() > oczko)
        GAME_OVER = over_2048;

    if (GAME_OVER == no_problemo)
        add_tile();
}

void GAME::credits()
{
    switch (GAME_OVER)
    {
        case winner:
            std::cout << "\033[1;32m!---!---YOU'VE WON---!---!\033[0m" << std::endl;
            break;
        case no_space:
            std::cout << "\033[1;31m!---!---YOU'VE LOST---!---!\033[0m" << std::endl;
            std::cout << "\033[1;31m!--No place for new tiles-!\033[0m" << std::endl;
            break;
        case over_2048:
            std::cout << "\033[1;31m!---!---YOU'VE LOST---!---!\033[0m" << std::endl;
            std::cout << "\033[1;31m!-------Exceeded 2048-----!\033[0m" << std::endl;
            break;
        case quitter:
            std::cout << "\033[1;31m!---!---YOU'VE LOST---!---!\033[0m" << std::endl;
            std::cout << "\033[1;31m!---You quitted the game--!\033[0m" << std::endl;
            break;
        default:
            std::cout << "\033[1;31m!---!---YOU'VE LOST---!---!\033[0m" << std::endl;
            std::cout << "\033[1;31m!--Something went wrong---!\033[0m" << std::endl;
            break;
    }
}