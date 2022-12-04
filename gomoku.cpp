#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

#define MAX_SIZE 15

const char HORZ = 196;
const char VERT = 179;
const char TL   = 218;
const char TM   = 194;
const char TR   = 191;
const char BL   = 192;
const char BM   = 193;
const char BR   = 217;
const int numW  = 3;
const int charW = 1;
const int numPerLine = 15;
const char VERT_START = 195;
const char VERT_END = 180;
const char VERT_MID = 197;
const string inputCommand = "Previous move/Next move/Stop [p/n/s]: ";
const string endOfHistory = "This is the end of the match.\nPrevious move/Next move/Stop [p/n/s]: ";
const string startOfGame = "This is the start of the match.\nPrevious move/Next move/Stop [p/n/s]: ";
const string invalidInput = "Illegal input, please try again: ";

enum Stone {NA, X, O};

string lineString( char left, char mid, char right, char horz, int wcell, int ncell )
{
    string result = "", cell = string( wcell, horz );
    result += left;
    for ( int i = 0; i < ncell - 1; i++ ) result += cell + mid;
    result += cell + right;
    return result;
}

void displayBoard(Stone arr[][MAX_SIZE], int size)
{
    //UPPERLINE
    cout << "   ";
    for(int i = 0; i < size; i++) {
        cout << "  " << (char)(i + 'a') << " ";
    }
    cout << endl;
    cout << "   " << lineString( TL, TM, TR, HORZ, 3, numPerLine ) << "\n";

    //MIDDLE
    for(int i = 0; i < size; i++) {
        cout << setw(2) << size - i << " " << VERT;
        for(int j = 0; j < size; j++) {
            if(arr[i][j] == NA) cout << "   " << VERT;
            if(arr[i][j] == X) cout << " X " << VERT;
            if(arr[i][j] == O) cout << " O " << VERT;
        }
        cout << endl;
        if(i != size - 1) cout << "   " << lineString( VERT_START, VERT_MID, VERT_END, HORZ, 3, numPerLine ) << "\n";
    }

    //UNDERLINE
    cout << "   " << lineString( BL, BM, BR, HORZ, 3, numPerLine ) << "\n";
}



void displayBoardSimple(Stone arr[][MAX_SIZE], int size)
{
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            cout << arr[i][j];
        }
    }
    cout << endl;
}

bool checkmove(string move)
{

    if (move.length() == 2) {

        bool condition_1 = (move[0]>=49 and move[0]<=57)?true:false;

        bool condition_2 = (move[1]>=97 and move[1]<=111)?true:false;

        if (condition_1 and condition_2) return true;
    }

    if (move.length() == 3) {

        bool condition_1 = (move[0] = '1')?true:false;

        bool condition_2 = (move[0]>=48 and move[0]<=53)?true:false;

        bool condition_3 = (move[2]>=97 and move[2]<=111)?true:false;

        if (condition_1 and condition_2 and condition_3) return true;
    }
    return false;
}

struct pmove {
    int row;
    int col;
};

pmove getmove(string Move)
{

    pmove result;

    if (Move.length() == 2) {

        result.row = 15 - (Move[0] - 48);

        result.col = Move[1] - 97;
    }

    if (Move.length() == 3) {

        result.row = 5 - (Move[1] - 48);

        result.col = Move[2] - 97;
    }

    return result;

}

bool makeMove(Stone board[][MAX_SIZE], int size, string playerMove, bool isFirstPlayerTurn)
{
    //BEGIN TODO
    pmove Move = getmove(playerMove);

    if (!checkmove(playerMove)) return false;

    if (board[Move.row][Move.col] != NA) return false;

    if (isFirstPlayerTurn) board[Move.row][Move.col] = X;
    else board[Move.row][Move.col] = O;

    return true;

    //END TODO
}

bool makeReMove(Stone board[][MAX_SIZE], int size, string playerMove)
{
    //BEGIN TODO
    pmove Move = getmove(playerMove);

    board[Move.row][Move.col] = NA;

    return true;

    //END TODO
}

bool hasWon(Stone board[][MAX_SIZE], int size, bool isFirstPlayerTurn)
{
    //BEGIN TODO

    Stone p = isFirstPlayerTurn?X:O;
    Stone unp = !isFirstPlayerTurn?X:O;

    for(int i=0; i<15; i++) {
        for(int j=0; j<15; j++) {
            if(board[i][j]==p) {

                // Win theo hàng ngang
                if (j==0) {
                    bool condition_1 = board[i][j+1] == p and board[i][j+2] == p and board[i][j+3] == p and board[i][j+4] == p;
                    bool condition_2 = board[i][j+5] != p;
                    if (condition_1 and condition_2) return true;
                }

                if (0<j and j<10) {
                    bool condition_1 = board[i][j+1] == p and board[i][j+2] == p and board[i][j+3] == p and board[i][j+4] == p;
                    bool condition_2 = board[i][j+5] != p and board[i][j-1] != p;
                    bool condition_3 = board[i][j+5] != unp or board[i][j-1] != unp;
                    if(condition_1 and condition_2 and condition_3) return true;
                }

                if (j==10) {
                    bool condition_1 = board[i][j+1] == p and board[i][j+2] == p and board[i][j+3] == p and board[i][j+4] == p;
                    bool condition_2 = board[i][j-1] != p;
                    if (condition_1 and condition_2) return true;
                }

                // Win thoe hàng dọc
                if (i==0) {
                    bool condition_1 = board[i+1][j] == p and board[i+2][j] == p and board[i+3][j] == p and board[i+4][j] == p;
                    bool condition_2 = board[i+5][j] != p;
                    if(condition_1 and condition_2) return true;
                }

                if (0<i and i<10) {
                    bool condition_1 = board[i+1][j] == p and board[i+2][j] == p and board[i+3][j] == p and board[i+4][j] == p;
                    bool condition_2 = board[i+5][j] != p and board[i-1][j] != p;
                    bool condition_3 = board[i+5][j] != unp or board[i-1][j] != unp;
                    if(condition_1 and condition_2 and condition_3) return true;
                }

                if (i==10) {
                    bool condition_1 = board[i+1][j] == p and board[i+2][j] == p and board[i+3][j] == p and board[i+4][j] == p;
                    bool condition_2 = board[i-1][j] != p;
                    if(condition_1 and condition_2) return true;
                }

                // Win theo chéo chính
                if (0<j and j<10 and 0<i and i<10) {
                    bool condition_1 = board[i+1][j+1] == p and board[i+2][j+2] == p and board[i+3][j+3] == p and board[i+4][j+4] == p;
                    bool condition_2 = board[i+5][j+5] != p and board[i-1][j-1] != p;
                    bool condition_3 = board[i+5][j+5] != unp or board[i-1][j-1] != unp;
                    if(condition_1 and condition_2 and condition_3) return true;
                }

                if ((i==0 and j<10) or (j==0 and i<10)) {
                    bool condition_1 = board[i+1][j+1] == p and board[i+2][j+2] == p and board[i+3][j+3] == p and board[i+4][j+4] == p;
                    bool condition_2 = board[i+5][j+5] != p;
                    if(condition_1 and condition_2) return true;
                }

                if ((i==10 and j>0) or (j==10 and i>0)) {
                    bool condition_1 = board[i+1][j+1] == p and board[i+2][j+2] == p and board[i+3][j+3] == p and board[i+4][j+4] == p;
                    bool condition_2 =  board[i-1][j-1] != p;
                    if(condition_1 and condition_2) return true;
                }

                if ((i==10 and j==10) or (j==10 and i==10)) {
                    bool condition_1 = board[i+1][j+1] == p and board[i+2][j+2] == p and board[i+3][j+3] == p and board[i+4][j+4] == p;
                    if(condition_1) return true;
                }

                // Win theo duong cheo phu
                if (4<j and j<14 and 4<i and i<14) {
                    bool condition_1 = board[i+1][j-1] == p and board[i+2][j-2] == p and board[i+3][j-3] == p and board[i+4][j-4] == p;
                    bool condition_2 = board[i+5][j-5] != p and board[i-1][j+1] != p;
                    bool condition_3 = board[i+5][j-5] != unp or board[i-1][j+1] != unp;
                    if(condition_1 and condition_2 and condition_3) return true;
                }

                if ((i==14 and j>4) or (j==14 and i>4)) {
                    bool condition_1 = board[i+1][j-1] == p and board[i+2][j-2] == p and board[i+3][j-3] == p and board[i+4][j-4] == p;
                    bool condition_2 = board[i+5][j-5] != p;
                    if(condition_1 and condition_2) return true;
                }

                if ((i==4 and j>4) or (j==4 and i>4)) {
                    bool condition_1 = board[i+1][j+1] == p and board[i+2][j+2] == p and board[i+3][j+3] == p and board[i+4][j+4] == p;
                    bool condition_2 =  board[i-1][j+1] != p;
                    if(condition_1 and condition_2) return true;
                }

                if ((i==4 and j==4) or (j==4 and i==4)) {
                    bool condition_1 = board[i+1][j+1] == p and board[i+2][j+2] == p and board[i+3][j+3] == p and board[i+4][j+4] == p;
                    if(condition_1) return true;
                }

            }



        }
    }

    return false;
    //END TODO
}

void displayHistory(string history, int numOfMoves)
{
    //BEGIN TODO
    Stone game[15][15];

    for(int i = 0; i < MAX_SIZE; i++) {
        for(int j = 0; j < MAX_SIZE; j++) {
            game[i][j] = NA;
        }
    }


    string move[230];

    for(int i=0, getFrom=0, getAmount=1, si=0; i<history.length(); i++) {
        if (history[i]>=97 and history[i]<=111) {
            move[si] = history.substr(getFrom,getAmount);
            getAmount=0;
            getFrom=i+1;
            si++;
        };

        getAmount++;
    }

    displayBoard(game, MAX_SIZE);

    char action;

    cout<<inputCommand;

    int i=0;

    bool player1Turn = true;

    while(cin >> action) {

        if(action == 'n') {

            if(i==numOfMoves) {
                cout<<endOfHistory;
                continue;
            }

            string playerMove = move[i];
            makeMove(game, MAX_SIZE, playerMove, player1Turn);
            displayBoard(game, MAX_SIZE);
            player1Turn = !player1Turn;
            i++;
        } else if(action == 'p') {

            if(i==0) {
                cout<<startOfGame;
                continue;
            }

            string playerMove = move[i-1];
            makeReMove(game, MAX_SIZE, playerMove);
            displayBoard(game, MAX_SIZE);
            player1Turn = !player1Turn;
            i--;
        } else if(action == 's') {
            return;
        } else {
            cout<<invalidInput;
            cout<<inputCommand;
        }

        cout<<inputCommand;

    }

    //END TODO
}

int goodState(Stone board[][MAX_SIZE], int size, bool isFirstPlayerTurn)
{
    //BEGIN TODO

    Stone p = isFirstPlayerTurn?X:O;
    Stone unp = !isFirstPlayerTurn?X:O;

    for(int i=0; i<15; i++) {
        for(int j=0; j<15; j++) {
            if(board[i][j]==p) {

                if (0<j and j<14) {
                    bool condition_1 = board[i][j+1] == p and board[i][j+2] == p;
                    bool condition_3 = board[i][j+3] != unp and board[i][j-1] != unp;
                    if(condition_1  and condition_3) return true;
                }

                // Win thoe hàng dọc

                if (0<i and i<14) {
                    bool condition_1 = board[i+1][j] == p and board[i+2][j] == p ;
                    bool condition_3 = board[i+3][j] != unp and board[i-1][j] != unp;
                    if(condition_1  and condition_3) return true;
                }


                // Win theo chéo chính
                if (0<j and j<14 and 0<i and i<14) {
                    bool condition_1 = board[i+1][j+1] == p and board[i+2][j+2] == p;
                    bool condition_3 = board[i+3][j+3] != unp and board[i-1][j-1] != unp;
                    if(condition_1  and condition_3) return true;
                }

                // Win theo duong cheo phu
                if (0<j and j<14 and 0<i and i<14) {
                    bool condition_1 = board[i+1][j-1] == p and board[i+2][j-2] == p;
                    bool condition_3 = board[i+3][j-3] != unp and board[i-1][j+1] != unp;
                    if(condition_1 and condition_3) return true;
                }

            }



        }
    }

    return false;
    //END TODO
}


// player 1 la max = ai = O, player 2 la min = player = X

int minimax(Stone board[][MAX_SIZE], int depth, bool isAI)
{

    if (hasWon(board, MAX_SIZE, false)){
        return 500;
    }

    if (hasWon(board, MAX_SIZE, true)){
        return -500;
    }

    if (goodState(board, MAX_SIZE, false)) {
        return 100 - depth * 10 ;
    }

    if (goodState(board, MAX_SIZE, true)) {
        return -100 + depth * 10;
    }


    if (depth == 2) return 0;

    if (isAI) {
        int best = -1000;

        for (int i=0; i<MAX_SIZE; i++) {
            for (int j=0; j<MAX_SIZE; j++) {

                if (board[i][j]==NA) {
                    board[i][j] = O;

                    best = max(best, minimax(board, depth+1, !isAI));

                    board[i][j] = NA;
                }
            }
        }

        return best;
    } else {
        int best = 1000;

        for (int i=0; i<MAX_SIZE; i++) {
            for (int j=0; j<MAX_SIZE; j++) {

                if (board[i][j]==NA) {
                    board[i][j] = X;

                    best = min(best, minimax(board, depth+1, !isAI));

                    board[i][j] = NA;
                }
            }
        }

        return best;
    }
}

pmove findBestMove(Stone board[][MAX_SIZE])
{

    int score = 0, bestScore = -999;
    pmove bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    for (int i=0; i<MAX_SIZE; i++) {
        for(int j=0; j<MAX_SIZE; j++) {

            if (board[i][j]==NA) {

                board[i][j] = O;


                score = minimax(board, 0, false);

                board[i][j] = NA;


                if (score > bestScore) {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestScore = score;
                }
            }
        }
    }

    return bestMove;
}


void versusComputer()
{
    //BEGIN TODO
    Stone game[15][15];
    for(int i = 0; i < MAX_SIZE; i++) {
        for(int j = 0; j < MAX_SIZE; j++) {
            game[i][j] = NA;
        }
    }

    displayBoard(game, MAX_SIZE);
    string playerMove;
    bool player1Turn = true;
    cout << "Player 1 turn: ";
    while(cin >> playerMove) {

        if(makeMove(game, MAX_SIZE, playerMove, player1Turn)) {

            if(hasWon(game, MAX_SIZE, player1Turn)) {
                displayBoard(game, MAX_SIZE);
                cout << ((player1Turn) ? "Player 1 won " : "Player 2 won ");
                return;
            }
            
            
            displayBoard(game, MAX_SIZE);

            cout << "Player 2 turn: "<<endl;
            
            pmove p2 = findBestMove(game);

            game[p2.row][p2.col] = O;

            if(hasWon(game, MAX_SIZE, !player1Turn)) {
                displayBoard(game, MAX_SIZE);
                cout << ((player1Turn) ? "Player 1 won " : "Player 2 won ");
                return;
            }

            displayBoard(game, MAX_SIZE);
            
            cout << "Player 1 turn: ";

        } else {
            cout << "Illegal move, please try again: ";
        }
    }
    //END TODO
}

void startGame()
{
    Stone game[15][15];
    for(int i = 0; i < MAX_SIZE; i++) {
        for(int j = 0; j < MAX_SIZE; j++) {
            game[i][j] = NA;
        }
    }
    displayBoard(game, MAX_SIZE);
    string playerMove;
    bool player1Turn = true;
    cout << "Player 1 turn: ";
    while(cin >> playerMove) {
        if(playerMove == "ff") {
            cout << ((player1Turn) ? "Player 2 won " : "Player 1 won ");
            break;
        } else if(makeMove(game, MAX_SIZE, playerMove, player1Turn)) {
            if(hasWon(game, MAX_SIZE, player1Turn)) {
                displayBoard(game, MAX_SIZE);
                cout << ((player1Turn) ? "Player 1 won " : "Player 2 won ");
                return;
            }
            player1Turn = !player1Turn;
            displayBoard(game, MAX_SIZE);
            cout << ((player1Turn) ? "Player 1 turn: " : "Player 2 turn: ");
        } else {
            cout << "Illegal move, please try again: ";
        }
    }
}

int main()
{
    cout << "Welcome to Gomoku!" << endl;
    cout << "1. Play game" << endl;
    cout << "2. History" << endl;
    cout << "3. Exit" << endl;
    cout << "Please select mode [1/2/3]: ";
    int mode;
    while(cin >> mode) {
        if(mode == 1) {
            startGame();
            return 0;
        } else if (mode == 2) {
            int numOfMoves;
            cout << "Please enter number of moves: ";
            cin >> numOfMoves;
            string history;
            cout << "Please enter history: ";
            cin >> history;
            displayHistory(history, numOfMoves);
            return 0;
        } else if (mode == 3) {
            versusComputer();
            return 0;
        } else if (mode == 4) {
            return 0;
        } else {
            cout << "Invalid mode, please try again: ";
        }
    }

    return 0;
}