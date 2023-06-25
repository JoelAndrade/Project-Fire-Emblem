#include "debug.h"

void printField(char* field, int row, int col) { // Input array like this array[0]
    for (int j = 0; j < row; ++j) {
        for (int i = 0; i < col; ++i) {
            std::cout << field[i];
        }

        std::cout << "\n";
        field += col;
    }

    std::cout << "\n";
}
