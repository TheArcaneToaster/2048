class BOARD
{
    private:
        static const unsigned DIMENSION = 4;
        int board[DIMENSION][DIMENSION] = {};
        unsigned highest;

    public:
        BOARD() : highest(0) {}
        ~BOARD() = default;

        //Data
        unsigned return_dimension() const {return DIMENSION;}
        unsigned highest_on_board() const;
        void show_board() const;

        //Actions
        void update_board();
        void add_tile();
        void find_highest_on_board();

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
        bool finished;

        GAME();

        //Making move
        void make_move(char move);

        //Game status
        bool game_ended();
        void show_board() { BOARD::show_board(); }
        bool bingo();

        ~GAME() { std::cout << "\033[1;33m+--+--+--AU REVOIR--+--+--+\033[0m" << std::endl; }
};