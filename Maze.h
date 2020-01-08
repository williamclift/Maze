// Maze

using std::cout;
class Maze {
    public:
        Maze(int n);
        bool endMaze;
        void createMaze();
        int** maze;      //Maze Array
        void toString();
        std::string solveE();
        std::string solveO();
        std::string solve();
        void setSize(int size);
        void deleteMaze();


    private:
        int n;          //size of the maze (n x n)
        int cpi;        //Current Row Position
        int cpj;        //Current Column Position
        void makeMove(int move);
        void selectMove();
        void makePath();
        bool checkMove(int select);
        char** testMaze;
        void setTestMaze();
        void pathToString();

};
