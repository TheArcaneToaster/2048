class BOARD
{
    private:
        static const unsigned DIMENSION = 4;
        int board[DIMENSION][DIMENSION] = {};
        unsigned highest;
        unsigned zeroes;

    public:
        BOARD() : highest(0), zeroes(DIMENSION*DIMENSION) {}
        ~BOARD() = default;

        const unsigned oczko = 2048;

        //Data and visuals
        unsigned return_dimension() const {return DIMENSION;}
        unsigned highest_on_board() const;
        void show_board() const;
        unsigned how_many_zeroes() { return zeroes; }

        //Actions
        void update_board();
        bool add_tile();
        void find_highest_on_board();
        void count_zeroes_on_board();

        //Movement
        void row_right(unsigned row);
        void row_left(unsigned row);
        void column_down(unsigned column);
        void column_up(unsigned column);
};

class GAME : protected BOARD
{
    private:
        void move_right();
        void move_left();
        void move_down();
        void move_up();

    public:
        enum prompt{no_problemo, no_space, over_2048, winner, quitter};
        prompt GAME_OVER;

        GAME();
        ~GAME() { std::cout << "\033[1;33m+--+--+--AU REVOIR--+--+--+\033[0m" << std::endl; }

        //Making move
        void make_move(char move);
        void add_tile();

        //Game status
        void show_board() { BOARD::show_board(); }
        void credits();
};