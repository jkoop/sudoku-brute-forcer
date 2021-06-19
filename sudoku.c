#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool solveSudoku();
bool checkSudoku();
void printSudoku();
bool isAllUnique();

int main(){
    int sudoku[9][9] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    // copy sudoku to setSudoku
    int setSudoku[9][9];
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
			setSudoku[i][j] = sudoku[i][j];
        }
    }

    bool solved = solveSudoku(sudoku, setSudoku);

    printSudoku(sudoku, setSudoku);

    return solved;
}

bool solveSudoku(int sudoku[9][9], int setSudoku[9][9]){
    bool forward = 1;

    for(int i = 0; i < 81; i++){
        int x = i % 9;
        int y = i / 9; // will be truncated (floored)

        for(int j = 0; j < 10; j++){
            if(forward && setSudoku[y][x] > 0) break;

            if(!forward && setSudoku[y][x] > 0) {
                i = i - 2;
                break;
            }

            if(sudoku[y][x] >= 9){
                if(i == 0){
                    printf("\e[1;31mNot solvable\e[0m\n");
                    return false;
                }

                forward = false;
                sudoku[y][x] = setSudoku[y][x];
                i = i - 2;
                break;
            }

            forward = true;
            sudoku[y][x]++;

            if(checkSudoku(sudoku)) break;
        }
    }

    return true;
}

bool checkSudoku(int sudoku[9][9]){
    // check rows
    for(int i = 0; i < 9; i++){
        if(!isAllUnique(sudoku[i])){
            return false;
        }
    }

    // check cols
    for(int i = 0; i < 9; i++){
        int col[9];

        for(int j = 0; j < 9; j++){
            col[j] = sudoku[j][i];
        }

        if(!isAllUnique(col)){
            return false;
        }
    }

    // check blocks
    for(int h = 0; h < 3; h++){
        for(int i = 0; i < 3; i++){
            int block[9];

            for(int j = 0; j < 3; j++){
                for(int k = 0; k < 3; k++){
                    block[j * 3 + k] = sudoku[h * 3 + j][i * 3 + k];
                }
            }

            if(!isAllUnique(block)){
                return false;
            }
        }
    }

    return true;
}

void printSudoku(int sudoku[9][9], int setSudoku[9][9]){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
			if(sudoku[i][j] == 0){
				printf("- ");
			}else{
                if(setSudoku[i][j] > 0){
                    printf("\e[1;36m");
                    printf("%d ", sudoku[i][j]);
                    printf("\e[0m");
                }else{
                    printf("%d ", sudoku[i][j]);
                }
			}
        }
        printf("\n");
    }
}

bool isAllUnique(int row[9]){
    int count[10] = {0,0,0,0,0,0,0,0,0,0};

    for(int i = 0; i < 9; i++){
        if(row[i] != 0 && count[row[i]] > 0){
            return false;
        }else{
            count[row[i]]++;
        }
    }

    return true;
}
