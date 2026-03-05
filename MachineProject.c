// Disclaimer: This project is made with 3 people with me being the co-author of 2 people while the other one handles the testing and documentation as our final project for this course

#include <stdio.h>

#define SIZE 16   // Size of set P (A x A = 4 x 4)
#define MAX_REL 4 // Max relations in C

// Structures for sets
typedef struct
{
    int x, y; // Pair coordinates
} Pair;

typedef struct
{
    Pair pairs[SIZE];
    int size;
} Set;

// Global variables
Set Uno = {{{0}}};  // Player Uno's set
Set Tres = {{{0}}}; // Player Tres's set
Set F;              // Set of remaining pairs (P - Uno - Tres)
int turn = 1;       // 1 = Uno's turn, 0 = Tres' turn
int go = 0;         // 1 = make a move, 0 = remove a move
int over = 0;       // 1 = game over, 0 = still playing

char board[4][4]; // board

// Winning relation set
Set C[MAX_REL] =
    {
        {{{1, 1}, {1, 2}, {1, 3}, {1, 4}}, 4},
        {{{1, 1}, {2, 2}, {3, 3}, {4, 4}}, 4},
        {{{1, 4}, {2, 3}, {3, 2}, {4, 1}}, 4},
        {{{4, 1}, {4, 2}, {4, 3}, {4, 4}}, 4}};

void GridP()
{
    int index = 0;
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 1; j <= 4; j++)
        {
            F.pairs[index].x = i;
            F.pairs[index].y = j;
            index++;
        }
    }
    F.size = SIZE;

    // Initialize board with empty spaces
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void displayBoard()
{
    // loop for Uno moves

    // loop for Tres moves

    // Display the board
    printf("\n  1 2 3 4\n");
    printf(" ---------\n");
    for (int i = 0; i < 4; i++)
    {
        printf("%d|", i + 1);
        for (int j = 0; j < 4; j++)
        {
            printf("%c|", board[i][j]);
        }
        printf("\n ---------\n");
    }
}

void printSet(Set *set, const char *name)
{
    printf("%s: {", name);
    for (int i = 0; i < set->size; i++)
    {
        printf("(%d, %d)", set->pairs[i].x, set->pairs[i].y);
        if (i < set->size - 1)
            printf(", ");
    }
    printf("}\n");
}

int isInSet(Pair pos)
{
    for (int i = 0; i < MAX_REL; i++)
    {
        for (int j = 0; j < C[i].size; j++)
        {
            if (C[i].pairs[j].x == pos.x && C[i].pairs[j].y == pos.y)
            {
                return 1;
            }
        }
    }
    return 0;
}
void addToSet(Pair pos)
{
    int i, j;

    if (turn) // Uno's turn
    {
        Uno.pairs[Uno.size] = pos;
        Uno.size++;
    }
    else // Tres' turn
    {
        Tres.pairs[Tres.size] = pos;
        Tres.size++;
    }

    // Remove from available positions (Set F)
    for (i = 0; i < F.size; i++)
    {
        if (F.pairs[i].x == pos.x && F.pairs[i].y == pos.y)
        {
            // Shift elements left
            for (j = i; j < F.size - 1; j++)
            {
                F.pairs[j] = F.pairs[j + 1];
            }
            F.size--; // Reduce set size
        }
    }
}

void nextPlayerMove(Pair pos)
{
    pos.x--;
    pos.y--;

    if (pos.x < 0 || pos.x >= SIZE || pos.y < 0 || pos.y >= SIZE || board[pos.x][pos.y] != ' ')
    {
        printf("Invalid input. Enter values between 1 and 4.\n");
        return;
    }

    board[pos.x][pos.y] = turn ? 'U' : 'T';
    addToSet((Pair){pos.x + 1, pos.y + 1}); // Add move to the player's set

    // Switch turn: Uno -> Tres -> Dos -> Uno
    if (turn == 1)
        turn = 0; // Next turn is Tres
    else if (turn == 0)
        turn = 2; // Next turn is Dos
    else
        turn = 1; // Next turn is Uno
}

void removeFromSet(Set *set, Pair pos)
{
    int i, j;
    for (i = 0; i < set->size; i++)
    {
        if (set->pairs[i].x == pos.x && set->pairs[i].y == pos.y)
        {
            // Add back to the available grid (Set F)
            F.pairs[F.size] = set->pairs[i];
            F.size++;

            // Shift elements left
            for (j = i; j < set->size - 1; j++)
            {
                set->pairs[j] = set->pairs[j + 1];
            }
            set->size--; // Reduce set size

            board[pos.x - 1][pos.y - 1] = ' '; // Remove from the grid
            return;
        }
    }
}

void dosTurn()
{
    int row, col;
    Pair pos;
    int valid = 0; // Flag to check if the input is valid

    printf("\nSelect a pair to remove from Uno or Tres.\n");

    while (valid == 0) // Continue until a valid move is made
    {
        printf("Enter row and column of the pair to remove (1-4): ");
        scanf("%d %d", &row, &col);

        pos.x = row;
        pos.y = col;

        // Check if pair is in Uno
        int inUno = 0, inTres = 0, i;
        for (i = 0; i < Uno.size; i++)
        {
            if (Uno.pairs[i].x == pos.x && Uno.pairs[i].y == pos.y)
            {
                inUno = 1;
            }
        }

        // Check if pair is in Tres
        for (i = 0; i < Tres.size; i++)
        {
            if (Tres.pairs[i].x == pos.x && Tres.pairs[i].y == pos.y)
            {
                inTres = 1;
            }
        }

        // If valid pair found, remove from the respective set and update the board
        if (inUno)
        {
            removeFromSet(&Uno, pos);
            board[row - 1][col - 1] = ' '; // Remove from board
            printf("Pair (%d, %d) removed from Uno!\n", row, col);
            valid = 1; // Set valid to 1 to exit the loop
        }
        else if (inTres)
        {
            removeFromSet(&Tres, pos);
            board[row - 1][col - 1] = ' '; // Remove from board
            printf("Pair (%d, %d) removed from Tres!\n", row, col);
            valid = 1; // Set valid to 1 to exit the loop
        }
        else
        {
            printf("Invalid choice! The pair is not in Uno or Tres. Please try again.\n");
        }
    }

    displayBoard(); // Display the updated board after the move
    turn = 0;       // Next turn is Tres
}

int winningSet(char player)
{
    for (int i = 0; i < MAX_REL; i++)
    {
        int win = 1;

        for (int j = 0; j < MAX_REL; j++)
        {
            int x = (C[i].pairs[j].x) - 1; // -1 to subtract the number to match the index of the array
            int y = (C[i].pairs[j].y) - 1; // -1 to subtract the number to match the index of the array

            if (board[x][y] != player)
            {
                win = 0;
                break;
            }
        }

        if (win)
            return 1;
    }
    return 0;
}

int boardFull() {
    for (int i = 0; i < SIZE; i++) 
        for (int j = 0; j < SIZE; j++) 
            if (board[i][j] == ' ') 
                return 0;
    return 1;
}

void checkGameOver()
{
    if (winningSet('U'))
    {
        displayBoard();
        printf("Uno Wins!\n");
        over = 1;
    }
    if (winningSet('T'))
    {
        displayBoard();
        printf("Tres Wins!\n");
        over = 1;
    }
    if (boardFull()) {
        displayBoard();
        printf("Dos Wins!\n");
        over = 1;
    }
}

int main()
{
    GridP(); // Initialize the game board

    printf("Starting 3-Player Game\n");

    int row, col; // Variables to store user input
    Pair pos;     // Pair for the user’s move

    // Main game loop
    while (over == 0)
    {
        displayBoard();

        // Display whose turn it is
        if (turn == 1)
        {
            printf("\nUno's turn.\n");
        }
        else if (turn == 2)
        {
            printf("\nDos' turn.\n");
            dosTurn(); // Dos' turn to remove a pair
            turn = 1; // to revert turn back to 1
            printf("\nUno's turn.\n"); //to display its uno's turn
        }
        else
        {
            printf("\nTres' turn.\n");
        }

        // Ask for user input for Uno or Tres
        if (turn != 2) // Only ask for input if it's not Dos' turn
        {
            printf("Enter row and column (1-4): ");
            scanf("%d %d", &row, &col);

            // Validate input range
            if (row < 1 || row > 4 || col < 1 || col > 4)
            {
                printf("Invalid input. Enter values between 1 and 4.\n");
            }
            else
            {
                pos.x = row;
                pos.y = col;

                // Process the move for Uno or Tres
                nextPlayerMove(pos);

                // check for the winner
                checkGameOver();

                // Print the sets for Uno, Tres, and F
                printf("\n");
                printSet(&Uno, "Uno");
                printSet(&Tres, "Tres");
                printSet(&F, "F");
            }
        }
    }

    printf("\nGame Over!\n");

    return 0;
}
