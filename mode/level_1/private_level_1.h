#ifndef PRIVATE_LEVEL_1_H
#define PRIVATE_LEVEL_1_H

#include <Character.h>
#include <SDL_Util.h>
#include <stdint.h>

#define ROW (9) // normal gpa 10
#define COL (16) // normal gpa 15

typedef enum levelMode_e {
    DEFAULT,
    OPTIONS,
    PIECE_SELECT,
    MOVE,
    POSTMOVE,
    ATTACK,
    STATS,
    SETTINGS,
} levelMode_t;

typedef struct map_s {
    const char tiles[ROW][COL] =
    {
        {'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n'},
        {'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n'},
        {'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n'},
        {'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n'},
        {'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n'},
        {'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n'},
        {'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n'},
        {'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n'},
        {'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n'}
    }; 



    /* 
    ====Legend====
    r - river
    s - sea
    w - wall
    ==============
    */
    const char terrain[ROW][COL] =
    {
        {'s', 's', 's', 's', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'r', ' ', ' ', ' ', ' '},
        {'s', 's', 's', 's', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'r', ' ', ' ', ' ', ' '},
        {'s', 's', 's', 's', ' ', ' ', 'w', ' ', ' ', ' ', ' ', 'r', ' ', ' ', ' ', ' '},
        {'s', 's', 's', 's', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'r', ' ', ' ', ' ', ' '},
        {'s', 's', 's', 's', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'r', ' ', ' ', ' ', ' '},
        {'s', 's', 's', 's', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'r', ' ', ' ', ' ', ' '},
        {'s', 's', 's', 's', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'r', ' ', ' ', ' ', ' '},
        {'s', 's', 's', 's', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'r', ' ', ' ', ' ', ' '},
        {'s', 's', 's', 's', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'r', ' ', ' ', ' ', ' '}
    };


    /* 
    ====Legend====
    p - peice
    r - river
    s - sea
    w - wall
    ==============
    */
    char collision[ROW][COL] =
    {
        {'s', 's', 's', 's', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'r', ' ', ' ', ' ', ' '},
        {'s', 's', 's', 's', ' ', ' ', ' ', 'p', ' ', ' ', ' ', 'r', ' ', ' ', ' ', ' '},
        {'s', 's', 's', 's', ' ', ' ', 'w', ' ', ' ', ' ', ' ', 'r', ' ', ' ', ' ', ' '},
        {'s', 's', 's', 's', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'r', ' ', ' ', ' ', ' '},
        {'s', 's', 's', 's', ' ', ' ', ' ', 'p', ' ', ' ', ' ', 'r', ' ', ' ', ' ', ' '},
        {'s', 's', 's', 's', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'r', ' ', ' ', ' ', ' '},
        {'s', 's', 's', 's', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'r', ' ', ' ', ' ', ' '},
        {'s', 's', 's', 's', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'r', ' ', ' ', ' ', ' '},
        {'s', 's', 's', 's', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'r', ' ', ' ', ' ', ' '}
    };

    char moveAttSpaces[ROW][COL] =
    {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };

    Character* pieceLocations[ROW][COL] = {NULL};

    const char empty[ROW][COL] = 
    {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };

    void fillMoveAttSpaces(int i_index, int j_index, int numMoves) {
        memcpy(&moveAttSpaces, &collision, sizeof(collision));
        moveAttSpaces[i_index][j_index] = '0';

        for (char move = '0'; move < '0' + numMoves; ++move) {
            for (int i = 0; i < ROW; ++i) {
                for (int j = 0; j < COL; ++j) {
                    if (moveAttSpaces[i][j] == move) {
                        fillMoveArray(i, j, move + 1);
                    }
                }
            }
        }

        for (int i = 0; i < ROW; ++i) {
            for (int j = 0; j < COL; ++j) {
                if (LIMITS('0', moveAttSpaces[i][j], '0' + numMoves)) {
                    fillAttackArray(i, j, numMoves);
                }
            }
        }
    }

    private:
        void fillMoveArray(int i, int j, char numChar) {
            if (LIMITS(0, i - 1, ROW) && moveAttSpaces[i - 1][j] == ' ') { // [ ][x][ ]
                moveAttSpaces[i - 1][j] = numChar;                         // [ ][o][ ]
            }                                                              // [ ][ ][ ]

            if (LIMITS(0, j - 1, COL) && moveAttSpaces[i][j - 1] == ' ') { // [ ][ ][ ]
                moveAttSpaces[i][j - 1] = numChar;                         // [x][o][ ]
            }                                                              // [ ][ ][ ]

            if (LIMITS(0, j + 1, COL) && moveAttSpaces[i][j + 1] == ' ') { // [ ][ ][ ]
                moveAttSpaces[i][j + 1] = numChar;                         // [ ][o][x]
            }                                                              // [ ][ ][ ]

            if (LIMITS(0, i + 1, ROW) && moveAttSpaces[i + 1][j] == ' ') { // [ ][ ][ ]
                moveAttSpaces[i + 1][j] = numChar;                         // [ ][o][ ]
            }                                                              // [ ][x][ ]
        }

        void fillAttackArray(int i, int j, int numMoves) {
            if (LIMITS(0, i - 1, ROW) && !LIMITS('0', moveAttSpaces[i - 1][j], '0' + numMoves)) { // [ ][x][ ]
                moveAttSpaces[i - 1][j] = 'a';                                                    // [ ][o][ ]
            }                                                                                     // [ ][ ][ ]

            if (LIMITS(0, j - 1, COL) && !LIMITS('0', moveAttSpaces[i][j - 1], '0' + numMoves)) { // [ ][ ][ ]
                moveAttSpaces[i][j - 1] = 'a';                                                    // [x][o][ ]
            }                                                                                     // [ ][ ][ ]

            if (LIMITS(0, j + 1, COL) && !LIMITS('0', moveAttSpaces[i][j + 1], '0' + numMoves)) { // [ ][ ][ ]
                moveAttSpaces[i][j + 1] = 'a';                                                    // [ ][o][x]
            }                                                                                     // [ ][ ][ ]

            if (LIMITS(0, i + 1, ROW) && !LIMITS('0', moveAttSpaces[i + 1][j], '0' + numMoves)) { // [ ][ ][ ]
                moveAttSpaces[i + 1][j] = 'a';                                                    // [ ][o][ ]
            }                                                                                     // [ ][x][ ]
        }
} map_t;

#endif // PRIVATE_LEVEL_1_H
