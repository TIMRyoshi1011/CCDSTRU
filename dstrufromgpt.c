#include <stdio.h>
#include <stdbool.h>

#define SIZE 4

// Board representation
char board[SIZE][SIZE];
bool turn = true; // true for Uno, false for Tres

// Winning conditions (preset patterns)
int win_patterns[4][4][2] = {
    {{0,0}, {0,1}, {0,2}, {0,3}}, // Top row
    {{0,0}, {1,1}, {2,2}, {3,3}}, // Diagonal 
    {{0,3}, {1,2}, {2,1}, {3,0}}, // Opposite diagonal
    {{3,0}, {3,1}, {3,2}, {3,3}}  // Bottom row
};

// Initialize the board
void init_board() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '.'; // Empty space
        }
    }
}

// Display the board
void display_board() {
    printf("\n  1 2 3 4\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// Check if a player has won
bool check_winner(char player) {
    for (int i = 0; i < 4; i++) {
        bool win = true;
        for (int j = 0; j < 4; j++) {
            int x = win_patterns[i][j][0];
            int y = win_patterns[i][j][1];
            if (board[x][y] != player) {
                win = false;
                break;
            }
        }
        if (win) return true;
    }
    return false;
}

// Check if the board is full
bool is_full() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == '.') return false;
        }
    }
    return true;
}

// Player move
void player_move(int x, int y) {
    x--; y--; // Adjust for 0-based index
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || board[x][y] != '.') {
        printf("Invalid move! Try again.\n");
        return;
    }
    
    board[x][y] = turn ? 'U' : 'T';
    turn = !turn;
}

int main() {
    init_board();
    int x, y;
    
    while (true) {
        display_board();
        printf("%s's turn. Enter row and column (1-4): ", turn ? "Uno (U)" : "Tres (T)");
        scanf("%d %d", &x, &y);
        
        player_move(x, y);
        
        if (check_winner('U')) {
            display_board();
            printf("Uno Wins!\n");
            break;
        }
        if (check_winner('T')) {
            display_board();
            printf("Tres Wins!\n");
            break;
        }
        if (is_full()) {
            display_board();
            printf("Dos Wins (Board Full)!\n");
            break;
        }
    }
    return 0;
}