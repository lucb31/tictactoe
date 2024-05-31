class Board {
    /*
    0 = Unset
    1 = Player 1
    2 = Player 2
    */
    int gameState[3][3] = {
        0,0,0,
        0,0,0,
        0,0,0
    };
    int currentTurn = 0;

    public: 
        void nextTurn();

        void setField(int const &position, int const &playerIndex);

        void printState();

        bool isOver();
    private:
        int getWinner();
        bool hasVacantFields();
        std::tuple<int, int> posToXY(int const &position);
        int posFromXY(int const &x, int const &y);

};