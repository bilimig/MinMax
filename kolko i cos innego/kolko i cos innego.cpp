#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using std::cout;
using std::cin;
using std::endl;

#define WIN 1000
#define DRAW 0
#define LOSS -1000

#define AI_MARKER 'O'
#define PLAYER_MARKER 'X'
#define EMPTY_SPACE '-'

#define START_DEPTH 0

// Print game state
void print_game_state(int state)
{
    if (WIN == state) { cout << "WIN" << endl; }
    else if (DRAW == state) { cout << "DRAW" << endl; }
    else if (LOSS == state) { cout << "LOSS" << endl; }
}

// All possible winning states
std::vector<std::vector<std::pair<int, int>>> winning_states;

// Print the current board state
void print_board(std::vector<std::vector<char>>& board)
{
    cout << endl;
    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board[i].size(); ++j)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Get all available legal moves (spaces that are not occupied)
std::vector<std::pair<int, int>> get_legal_moves(std::vector<std::vector<char>>& board)
{
    std::vector<std::pair<int, int>> legal_moves;
    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board[i].size(); ++j)
        {
            if (board[i][j] != AI_MARKER && board[i][j] != PLAYER_MARKER)
            {
                legal_moves.push_back(std::make_pair(i, j));
            }
        }
    }

    return legal_moves;
}

// Check if a position is occupied
bool position_occupied(std::vector<std::vector<char>>& board, std::pair<int, int> pos)
{
    std::vector<std::pair<int, int>> legal_moves = get_legal_moves(board);

    for (int i = 0; i < legal_moves.size(); ++i)
    {
        if (pos.first == legal_moves[i].first && pos.second == legal_moves[i].second)
        {
            return false;
        }
    }

    return true;
}

// Get all board positions occupied by the given marker
std::vector<std::pair<int, int>> get_occupied_positions(std::vector<std::vector<char>>& board, char marker)
{
    std::vector<std::pair<int, int>> occupied_positions;

    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board[i].size(); ++j)
        {
            if (marker == board[i][j])
            {
                occupied_positions.push_back(std::make_pair(i, j));
            }
        }
    }

    return occupied_positions;
}

// Check if the board is full
bool board_is_full(std::vector<std::vector<char>>& board)
{
    std::vector<std::pair<int, int>> legal_moves = get_legal_moves(board);

    return legal_moves.empty();
}

// Check if a player has won the game
bool is_winning_move(std::vector<std::vector<char>>& board, char marker, int length_to_win)
{
    int rows = board.size();
    int cols = board[0].size();

    // Check rows
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j <= cols - length_to_win; ++j)
        {
            bool win = true;
            for (int k = 0; k < length_to_win; ++k)
            {
                if (board[i][j + k] != marker)
                {
                    win = false;
                    break;
                }
            }
            if (win)
            {
                return true;
            }
        }
    }

    // Check columns
    for (int i = 0; i <= rows - length_to_win; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            bool win = true;
            for (int k = 0; k < length_to_win; ++k)
            {
                if (board[i + k][j] != marker)
                {
                    win = false;
                    break;
                }
            }
            if (win)
            {
                return true;
            }
        }
    }

    // Check diagonals (top-left to bottom-right)
    for (int i = 0; i <= rows - length_to_win; ++i)
    {
        for (int j = 0; j <= cols - length_to_win; ++j)
        {
            bool win = true;
            for (int k = 0; k < length_to_win; ++k)
            {
                if (board[i + k][j + k] != marker)
                {
                    win = false;
                    break;
                }
            }
            if (win)
            {
                return true;
            }
        }
    }

    // Check diagonals (top-right to bottom-left)
    for (int i = 0; i <= rows - length_to_win; ++i)
    {
        for (int j = length_to_win - 1; j < cols; ++j)
        {
            bool win = true;
            for (int k = 0; k < length_to_win; ++k)
            {
                if (board[i + k][j - k] != marker)
                {
                    win = false;
                    break;
                }
            }
            if (win)
            {
                return true;
            }
        }
    }

    return false;
}

// Check if the game is won by any player
bool game_is_won(std::vector<std::pair<int, int>>& occupied_positions, int size, int length_to_win)
{
    for (int i = 0; i < occupied_positions.size(); ++i)
    {
        int row = occupied_positions[i].first;
        int col = occupied_positions[i].second;

        std::vector<std::vector<char>> board = std::vector<std::vector<char>>(size, std::vector<char>(size, EMPTY_SPACE));
        board[row][col] = AI_MARKER;

        if (is_winning_move(board, AI_MARKER, length_to_win))
        {
            return true;
        }
    }

    return false;
}

// Get the opponent marker
char get_opponent_marker(char marker)
{
    return (marker == AI_MARKER) ? PLAYER_MARKER : AI_MARKER;
}

// Minimax algorithm with alpha-beta pruning
int minimax(std::vector<std::vector<char>>& board, char marker, int depth, int alpha, int beta, int size, int length_to_win)
{
    std::vector<std::pair<int, int>> legal_moves = get_legal_moves(board);

    if (is_winning_move(board, AI_MARKER, length_to_win))
    {
        return WIN - depth;
    }
    else if (is_winning_move(board, PLAYER_MARKER, length_to_win))
    {
        return LOSS + depth;
    }
    else if (legal_moves.empty())
    {
        return DRAW;
    }

    if (depth == START_DEPTH)
    {
        cout << "AI is thinking..." << endl;
    }

    int best_score;
    if (marker == AI_MARKER)
    {
        best_score = LOSS;

        for (int i = 0; i < legal_moves.size(); ++i)
        {
            int row = legal_moves[i].first;
            int col = legal_moves[i].second;

            board[row][col] = marker;

            int score = minimax(board, get_opponent_marker(marker), depth + 1, alpha, beta, size, length_to_win);
            best_score = std::max(best_score, score);

            board[row][col] = EMPTY_SPACE;

            alpha = std::max(alpha, best_score);
            if (beta <= alpha)
            {
                break;
            }
        }
    }
    else
    {
        best_score = WIN;

        for (int i = 0; i < legal_moves.size(); ++i)
        {
            int row = legal_moves[i].first;
            int col = legal_moves[i].second;

            board[row][col] = marker;

            int score = minimax(board, get_opponent_marker(marker), depth + 1, alpha, beta, size, length_to_win);
            best_score = std::min(best_score, score);

            board[row][col] = EMPTY_SPACE;

            beta = std::min(beta, best_score);
            if (beta <= alpha)
            {
                break;
            }
        }
    }

    return best_score;
}

// Get the optimal move for the AI
std::pair<int, int> get_optimal_move(std::vector<std::vector<char>>& board, int size, int length_to_win)
{
    std::vector<std::pair<int, int>> legal_moves = get_legal_moves(board);

    int best_score = LOSS;
    std::pair<int, int> best_move;

    for (int i = 0; i < legal_moves.size(); ++i)
    {
        int row = legal_moves[i].first;
        int col = legal_moves[i].second;

        board[row][col] = AI_MARKER;

        int score = minimax(board, PLAYER_MARKER, START_DEPTH + 1, LOSS, WIN, size, length_to_win);
        if (score > best_score)
        {
            best_score = score;
            best_move = std::make_pair(row, col);
        }

        board[row][col] = EMPTY_SPACE;
    }

    return best_move;
}

// Play the game
void play_game(int size, int length_to_win)
{
    std::vector<std::vector<char>> board(size, std::vector<char>(size, EMPTY_SPACE));

    int current_turn = 1;  // 1 for AI, 2 for player

    while (true)
    {
        if (current_turn == 1)  // AI's turn
        {
            std::pair<int, int> ai_move = get_optimal_move(board, size, length_to_win);
            int row = ai_move.first;
            int col = ai_move.second;

            board[row][col] = AI_MARKER;

            cout << "AI's move:" << endl;
            print_board(board);

            if (is_winning_move(board, AI_MARKER, length_to_win))
            {
                cout << "AI wins!" << endl;
                break;
            }

            if (board_is_full(board))
            {
                cout << "It's a draw!" << endl;
                break;
            }

            current_turn = 2;
        }
        else if (current_turn == 2)  // Player's turn
        {
            int row, col;
            cout << "Enter your move (row and column): ";
            cin >> row >> col;

            while (row < 0 || row >= size || col < 0 || col >= size || board[row][col] != EMPTY_SPACE)
            {
                cout << "Invalid move. Enter your move (row and column): ";
                cin >> row >> col;
            }

            board[row][col] = PLAYER_MARKER;

            cout << "Your move:" << endl;
            print_board(board);

            if (is_winning_move(board, PLAYER_MARKER, length_to_win))
            {
                cout << "You win!" << endl;
                break;
            }

            if (board_is_full(board))
            {
                cout << "It's a draw!" << endl;
                break;
            }

            current_turn = 1;
        }
    }
}

int main()
{
    int size, length_to_win;
    cout << "Enter the size of the board: ";
    cin >> size;
    cout << "Enter the length to win: ";
    cin >> length_to_win;

    play_game(size, length_to_win);

    return 0;
}
