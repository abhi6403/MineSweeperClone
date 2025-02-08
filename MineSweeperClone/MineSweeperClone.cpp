#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

class Board
{
private:
    int rows;  //number of rows
    int cols;  //number of columns
    const int mine = 10; //fixed number of mines

public:

    Board()
    {
        //Display Message when game starts
        cout << "-----------------------------------------" << endl;
        cout << "|                                       |" << endl;
        cout << "|        Welcome to Minesweeper!        |" << endl;
        cout << "|                                       |" << endl;
        cout << "-----------------------------------------" << endl;
    }

    ~Board()
    {
        //Display Message when game ends
        cout << "-----------------------------------------" << endl;
        cout << "|               Game Ends               |" << endl;
        cout << "|               Thank You               |" << endl;
        cout << "-----------------------------------------" << endl;
    }

    // Function to display the board
    void displayBoard(vector<vector<char>>& board)
    {
        // Display column indices
        cout << "  ";
        for (int c = 0; c < cols; ++c)
        {
            cout << c << " ";
        }
        cout << endl;

        // Display each row with its index
        for (int r = 0; r < rows; ++r)
        {
            cout << r << " ";

            for (int c = 0; c < cols; ++c)
            {
                cout << board[r][c] << " ";
            }
            cout << endl;
        }
    }

    // Function to initialize the board
    void initializeBoard(vector<vector<char>>& board, char fillchar)
    {
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < cols; ++c)
            {
                board[r][c] = fillchar;  // Fill each cell with the given character
            }
        }
    }

    // Function to place mines on the board
    void placeMines(vector<vector<char>>& board)
    {
        int placedMines = 0;
        srand(time(nullptr));  // Seed the random number generator

        while (placedMines < mine)
        {
            int r = rand() % rows;
            int c = rand() % cols;

            // Place a mine only if the cell is empty
            if (board[r][c] != '*')
            {
                board[r][c] = '*';
                placedMines++;
            }
        }
    }

    // Function to count adjacent mines
    int countAdjacentMines(const vector<vector<char>>& board, int r, int c)
    {
        int count = 0;

        // Loop through all neighboring cells
        for (int dr = -1; dr <= 1; ++dr)
        {
            for (int dc = -1; dc <= 1; ++dc)
            {
                int nr = r + dr;
                int nc = c + dc;

                // Check boundaries and if the neighbor contains a mine
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && board[nr][nc] == '*')
                {
                    count++;
                }
            }
        }
        return count;
    }

    // Function to reveal the board 
    void reveal(vector<vector<char>>& display, const vector<vector<char>>& mines, int r, int c)
    {
        if (r < 0 || r >= rows || c < 0 || c >= cols || display[r][c] != '-') return;
        int adjacentMines = countAdjacentMines(mines, r, c);

        // If there are adjacent mines, display the count
        if (adjacentMines > 0)
        {
            display[r][c] = '0' + adjacentMines;
        }
        else
        {
            // If no adjacent mines, reveal the cell as empty
            display[r][c] = ' ';

            for (int dr = -1; dr <= 1; ++dr)
            {
                for (int dc = -1; dc <= 1; ++dc)
                {
                    reveal(display, mines, r + dr, c + dc);
                }
            }
        }
    }

    void SetRowsAndCols(int row, int col)
    {
        rows = row;
        cols = col;
    }

    int GetRows()
    {
        return rows;
    }

    int GetCols()
    {
        return cols;
    }

    int GetMinesCount()
    {
        return mine;
    }
};

int main()
{
    Board board;
    int r, c;

    // User inputs for board dimensions
    cout << "Enter the number or rows and columns" << endl;
    cin >> r >> c;
    board.SetRowsAndCols(r, c);

    vector<vector<char>> mines(board.GetRows(), vector<char>(board.GetCols(), '-'));
    vector<vector<char>> display(board.GetRows(), vector<char>(board.GetCols(), '-'));

    board.initializeBoard(mines, '-');
    board.placeMines(mines);

    bool gameOver = false;
    int movesLeft = board.GetRows() * board.GetCols() - board.GetMinesCount();


    while (!gameOver)
    {
        board.displayBoard(display);

        cout << "enter your move (row and column)" << endl;
        cin >> r >> c;

        // Check for invalid moves
        if (r < 0 || r >= board.GetRows() || c < 0 || c >= board.GetCols())
        {
            cout << "Invalid move. try again" << endl;
            continue;
        }

        // Check if the player hits a mine
        if (mines[r][c] == '*')
        {
            cout << "Game Over! You hit a mine!" << endl;
            gameOver = true;
            break;
        }

        // Reveal the selected cell
        board.reveal(display, mines, r, c);
        movesLeft--;

        if (movesLeft == 0)
        {
            cout << "Congratulations! You've cleared the board!" << endl;
            gameOver = true;
            break;
        }
    }

    cout << "Final Board: " << endl;
    board.displayBoard(mines);
}

