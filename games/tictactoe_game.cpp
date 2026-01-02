/**
 * @file
 * @brief A classic [Tic Tac Toe](https://en.wikipedia.org/wiki/Tic-tac-toe) game
 * with two-player support.
 * @details
 * The game allows two players to play Tic Tac Toe on a 3x3 grid.
 * Players take turns placing their marks (X or O) on the board.
 * The first player to get three of their marks in a row (horizontally,
 * vertically, or diagonally) wins. If all nine squares are filled without
 * a winner, the game ends in a draw.
 *
 * The game features:
 * - A 3x3 grid display
 * - Input validation
 * - Win condition checking
 * - Draw detection
 * - Option to play again
 *
 * @author [Devansh Rawat](https://github.com/Devansh-Rawat-gamedev)
 */

#include <iostream>   /// for IO operations
#include <vector>     /// for std::vector
#include <algorithm>  /// for std::fill
#include <cctype>     /// for std::toupper

// `Sleep` is only available in Windows in milliseconds.
// However, on Unix/Linux systems it is `sleep`, in seconds.
#ifdef _WIN32
#include <Windows.h>  /// for Sleep()
template <typename T>
constexpr typename std::enable_if<std::is_integral<T>::value, void>::type SLEEP(
    T milliseconds) {
    Sleep(milliseconds * 1000);
}
#else
#include <unistd.h>  /// for sleep()
template <typename T>
constexpr T SLEEP(T seconds) {
    return sleep(seconds);
}
#endif

/**
 * @namespace
 * @brief (Mini)game implementations.
 */
namespace games {
/**
 * @namespace
 * @brief Functions for the [Tic Tac Toe](https://en.wikipedia.org/wiki/Tic-tac-toe)
 * implementation.
 */
namespace tic_tac_toe {
/**
 * @brief The TicTacToeGame class manages the game state and logic.
 */
class TicTacToeGame {
private:
    std::vector<char> board;    ///< The 3x3 game board stored as a 1D vector
    char currentPlayer;         ///< Current player ('X' or 'O')
    bool gameOver;              ///< Whether the game has ended
    char winner;                ///< Winner ('X', 'O', or ' ' for draw)

public:
    /**
     * @brief Constructs a new Tic Tac Toe game.
     */
    TicTacToeGame() : board(9, ' '), currentPlayer('X'), gameOver(false), winner(' ') {}

    /**
     * @brief Prints the current state of the game board.
     * @returns void
     */
    void printBoard() const {
        std::cout << "\n";
        std::cout << " " << board[0] << " | " << board[1] << " | " << board[2] << " \n";
        std::cout << "-----------\n";
        std::cout << " " << board[3] << " | " << board[4] << " | " << board[5] << " \n";
        std::cout << "-----------\n";
        std::cout << " " << board[6] << " | " << board[7] << " | " << board[8] << " \n";
        std::cout << "\n";
    }

    /**
     * @brief Prints the board with position numbers for reference.
     * @returns void
     */
    void printReferenceBoard() const {
        std::cout << "\nBoard positions:\n";
        std::cout << " 1 | 2 | 3 \n";
        std::cout << "-----------\n";
        std::cout << " 4 | 5 | 6 \n";
        std::cout << "-----------\n";
        std::cout << " 7 | 8 | 9 \n";
        std::cout << "\n";
    }

    /**
     * @brief Checks if a move is valid.
     * @param position The board position (1-9) to check.
     * @returns true if the position is valid and empty
     * @returns false if the position is invalid or occupied
     */
    bool isValidMove(int position) const {
        if (position < 1 || position > 9) {
            return false;
        }
        return board[position - 1] == ' ';
    }

    /**
     * @brief Makes a move on the board.
     * @param position The board position (1-9) to place the mark.
     * @returns true if the move was successful
     * @returns false if the move was invalid
     */
    bool makeMove(int position) {
        if (!isValidMove(position)) {
            return false;
        }
        
        board[position - 1] = currentPlayer;
        return true;
    }

    /**
     * @brief Checks if the current player has won.
     * @returns true if the current player has three in a row
     * @returns false otherwise
     */
    bool checkWin() const {
        // Check rows
        for (int i = 0; i < 9; i += 3) {
            if (board[i] != ' ' && board[i] == board[i + 1] && board[i] == board[i + 2]) {
                return true;
            }
        }

        // Check columns
        for (int i = 0; i < 3; i++) {
            if (board[i] != ' ' && board[i] == board[i + 3] && board[i] == board[i + 6]) {
                return true;
            }
        }

        // Check diagonals
        if (board[0] != ' ' && board[0] == board[4] && board[0] == board[8]) {
            return true;
        }
        if (board[2] != ' ' && board[2] == board[4] && board[2] == board[6]) {
            return true;
        }

        return false;
    }

    /**
     * @brief Checks if the board is full (draw condition).
     * @returns true if all positions are filled
     * @returns false otherwise
     */
    bool checkDraw() const {
        for (char cell : board) {
            if (cell == ' ') {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Updates the game state after a move.
     * @returns void
     */
    void updateGameState() {
        if (checkWin()) {
            gameOver = true;
            winner = currentPlayer;
            return;
        }

        if (checkDraw()) {
            gameOver = true;
            winner = ' ';  // Draw
            return;
        }

        // Switch player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    /**
     * @brief Gets the current player.
     * @returns The current player ('X' or 'O')
     */
    char getCurrentPlayer() const {
        return currentPlayer;
    }

    /**
     * @brief Checks if the game is over.
     * @returns true if the game has ended
     * @returns false otherwise
     */
    bool isGameOver() const {
        return gameOver;
    }

    /**
     * @brief Gets the winner of the game.
     * @returns 'X' or 'O' for winner, ' ' for draw
     */
    char getWinner() const {
        return winner;
    }

    /**
     * @brief Resets the game to its initial state.
     * @returns void
     */
    void reset() {
        std::fill(board.begin(), board.end(), ' ');
        currentPlayer = 'X';
        gameOver = false;
        winner = ' ';
    }

    /**
     * @brief Utility function to clear the screen.
     * @returns void
     */
    void clearScreen() const {
        // Clear screen command
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif
    }
};

/**
 * @brief Utility function to get a valid integer input from the user.
 * @param prompt The prompt to display to the user.
 * @param min The minimum valid value.
 * @param max The maximum valid value.
 * @returns A valid integer within the specified range
 */
int getValidInput(const std::string& prompt, int min, int max) {
    int input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cout << "Invalid input. Please enter a number between " 
                      << min << " and " << max << ".\n";
            continue;
        }
        
        if (input < min || input > max) {
            std::cout << "Please enter a number between " << min 
                      << " and " << max << ".\n";
            continue;
        }
        
        return input;
    }
}

/**
 * @brief Main game loop that manages the gameplay.
 * @returns void
 */
void playGame() {
    TicTacToeGame game;
    bool playAgain = true;
    
    while (playAgain) {
        game.reset();
        
        std::cout << "\n======================================\n";
        std::cout << "        WELCOME TO TIC TAC TOE!\n";
        std::cout << "======================================\n";
        
        game.printReferenceBoard();
        std::cout << "Player 1: X\n";
        std::cout << "Player 2: O\n";
        std::cout << "\nGame starting...\n";
        SLEEP(2);
        
        while (!game.isGameOver()) {
            game.clearScreen();
            
            std::cout << "\n======================================\n";
            std::cout << "          TIC TAC TOE GAME\n";
            std::cout << "======================================\n";
            
            game.printBoard();
            game.printReferenceBoard();
            
            std::cout << "Current player: " << game.getCurrentPlayer() << "\n";
            
            int position = getValidInput("Enter position (1-9): ", 1, 9);
            
            if (!game.makeMove(position)) {
                std::cout << "Position " << position << " is already occupied or invalid. Try again.\n";
                SLEEP(2);
                continue;
            }
            
            game.updateGameState();
            
            if (game.isGameOver()) {
                game.clearScreen();
                game.printBoard();
                
                if (game.getWinner() == ' ') {
                    std::cout << "\n======================================\n";
                    std::cout << "            IT'S A DRAW!\n";
                    std::cout << "======================================\n";
                } else {
                    std::cout << "\n======================================\n";
                    std::cout << "      PLAYER " << game.getWinner() << " WINS!\n";
                    std::cout << "======================================\n";
                }
            }
        }
        
        char response;
        std::cout << "\nPlay again? (y/n): ";
        std::cin >> response;
        response = std::toupper(response);
        
        while (response != 'Y' && response != 'N') {
            std::cout << "Please enter 'y' or 'n': ";
            std::cin >> response;
            response = std::toupper(response);
        }
        
        playAgain = (response == 'Y');
        
        if (playAgain) {
            std::cout << "\nStarting new game...\n";
            SLEEP(2);
        }
    }
    
    std::cout << "\n======================================\n";
    std::cout << "    THANK YOU FOR PLAYING!\n";
    std::cout << "======================================\n";
    SLEEP(2);
}
}  // namespace tic_tac_toe
}  // namespace games

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    games::tic_tac_toe::playGame();
    return 0;
}