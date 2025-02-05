// By: mathewn24

#include <iostream>
using namespace std;

/* Function prototypes */
void printPuzzle(int state);
int missingTile(int state);
bool isMoveValid(int state, char dir);
void moveMissingTile(int &state, char dir);
int randGenPuzzle();
int getTile(int state, int position);
int inversion(int puzzle);

/* Prints the puzzle state to the screen. */
void printPuzzle(int state) {

    int a, b, c, d, e, f, g, h, i; /* the variables each for the digits of the puzzle */

    if (state < 100000000){
        a = state / 10000000 % 10;
        b = state / 1000000 % 10;
        c = state / 100000 % 10;
        d = state / 10000 % 10;
        e = state / 1000 % 10;
        f = state / 100 % 10;
        g = state / 10 % 10;
        h = state % 10;
        cout << "." << " " << (a == 0 ? '.' : char('0' + a)) << " " << (b == 0 ? '.' : char('0' + b)) << "\n";
        cout << ( c == 0 ? '.' : char('0' + c)) << " " << ( d == 0 ? '.' : char('0' + d)) << " " << ( e == 0 ? '.' :char('0' + e) ) << "\n";
        cout << ( f == 0 ? '.' : char('0' + f)) << " " << ( g == 0 ? '.' : char('0' + g)) << " " << ( h == 0 ? '.' : char('0' + h)) << "\n";
    
    } else {
        a = state / 100000000 % 10;
        b = state / 10000000 % 10;
        c = state / 1000000 % 10;
        d = state / 100000 % 10;
        e = state / 10000 % 10;
        f = state / 1000 % 10;
        g = state / 100 % 10;
        h = state / 10 % 10;
        i = state % 10;
        cout << (a == 0 ? '.' : char('0' + a)) << " " << (b == 0 ? '.' : char('0' + b)) << " " << ( c == 0 ? '.' : char('0' + c)) << "\n";
        cout << ( d == 0 ? '.' : char('0' + d)) << " " << ( e == 0 ? '.' :char('0' + e) ) << " " << ( f == 0 ? '.' : char('0' + f)) << "\n";
        cout << ( g == 0 ? '.' : char('0' + g)) << " " << ( h == 0 ? '.' : char('0' + h)) << " " << ( i == 0 ? '.' : char('0' + i)) << "\n";
    }
}

/* Returns the position of the missing tile in the puzzle state. */
int missingTile(int state) {

    if (state < 100000000) {
        return 1;
    }

    for (int i = 9; i >= 1; i--) {
        int digit = state % 10;
        if (digit == 0) {
            return i;
        }
        state /= 10;
    }
    return -1;
}

/* Returns true if the missing tile in the puzzle state can move towards the
   direction dir; returns false otherwise. */
bool isMoveValid(int state, char dir) {

    int pos = missingTile(state);
    // Validation at the left most position
    if ((pos == 1 || pos == 4 ||  pos == 7) && dir == 'l') {
        return false;
    // Validation at the top most position
    } else if ((pos == 1 || pos == 2 ||  pos == 3) && dir == 'u'){
        return false;
    // Validation at the right most position.
    } else if ((pos == 3 || pos == 6 ||  pos == 9) && dir == 'r') {
        return false;
    // Validation at the bottom most position.
    } else if ((pos == 7 || pos == 8 ||  pos == 9) && dir == 'd') {
        return false;

    } else {
        return true;
    }
    return false;
}

/* Moves the missing tile in the puzzle state towards the direction dir. */
void moveMissingTile(int &state, char dir) {
    
    bool check = isMoveValid(state, dir);
    if (!check) {
        cout << "Invalid move. Try again!" << endl;
        return;
    }

    int startPos = missingTile(state);
    int swapPos;
    switch (dir) {
        case 'u': // Move up
            swapPos = startPos - 3; // Swap with the tile 3 positions higher
            break;
        case 'd': // Move down
            swapPos = startPos + 3; // Swap with the tile 3 positions lower
            break;
        case 'l': // Move left
            swapPos = startPos - 1; // Swap with the tile 1 position higher
            break;
        case 'r': // Move right
            swapPos = startPos + 1; // Swap with the tile 1 position lower
            break;
    }

    // Get the power of the positions to add and subtract from the int
    int startPow = 1;
    for(int i = 0; i < (9-startPos); i++) startPow *= 10;

    int swapPow = 1;
    for(int i = 0; i < (9-swapPos); i++) swapPow *= 10;
    
    // Get the respective digits at the start and swap positions.
    int startDigit = (state/startPow) % 10;
    int swapDigit = (state/swapPow) % 10;
    
    // Multiply the digits with their respective place values.
    // And add/subtract the result with the state integer to swap their positons. 
    state = state - (swapDigit*swapPow) + (swapDigit*startPow);
}

/* Returns a solvable randomly generated 8-puzzle. Do NOT modify! */
int randGenPuzzle() {
    int mask, p, divp, s, divm, j, inv;
    do {
        mask = 0;
        p = 0;
        divp = 1;
        while (mask != 111111111) {
            s = rand() % 9;
            divm = 1;
            for (j = 1; j <= s; j++)
                divm *= 10;
            if (mask / divm % 10 == 0) {
                p += s * divp;
                mask += divm;
                divp *= 10;
            }
        }
        inv = inversion(p);
    } while (inv % 2 != 0);
    return p;
}

int getTile(int state, int position){
    for(int i = 0; i < position; i++) {
        state /= 10;
    }
    return state % 10;
}

/* Returns the number of inversions of the puzzle state. */
int inversion(int state) {
    // Add a return statement in order to compile
    int inv = 0;
    char stateStr[10]; // Buffer to hold the state as a string
    sprintf(stateStr, "%09d", state); // Convert state to a 9-character string (including leading zeros)
    
    // Loop through each pair of tiles
    // Iterate through the state string
    for (int i = 0; i < 8; i++) {
        if (stateStr[i] == '0') continue; // Skip the missing tile
        
        for (int j = i + 1; j < 9; j++) {
            if (stateStr[j] == '0') continue; // Skip the missing tile
            
            // If the current tile is greater than the next tile, it's an inversion
            if (stateStr[i] > stateStr[j]) {
                inv++;
            }
        }
    }

    return inv;
}

int main() {
    int rounds = 1, seed, puzzle, prev;
    char move;

    cout << "Seed: ";
    cin >> seed;
    srand(seed);
    puzzle = randGenPuzzle();
    printPuzzle(puzzle);

    while (rounds < 100 && puzzle != 123456780) {
        cout << "Make a move [udlr]: ";
        cin >> move;
        prev = puzzle; // Store previous state of puzzle to check if state is updated.
        moveMissingTile(puzzle, move);
        // If move is valid, puzzle state will be updated and round will be increased.
        if (puzzle != prev) {
            printPuzzle(puzzle);
            rounds += 1;
        }
    }
    
    if (rounds < 30) {
        cout << "Well done!" << endl;
    } else if (rounds > 30 && rounds < 100) {
        cout << "Good enough!" << endl;
    } else {
        cout << "Too bad!" << endl;
    }

    return 0;
}
