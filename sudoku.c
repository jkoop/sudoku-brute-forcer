#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <termios.h>

void getSudoku();
bool solveSudoku();
bool checkSudoku();
void printSudoku();
bool isAllUnique();
int getch();

int main(){
    int sudoku[9][9];

    getSudoku(sudoku);

    // copy sudoku to setSudoku
    int setSudoku[9][9];
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            setSudoku[i][j] = sudoku[i][j];
        }
    }

    bool solved = solveSudoku(sudoku, setSudoku);

    return !solved;
}

void getSudoku(int sudoku[9][9]){
    int c;
    char k;

    printf("Enter numbers of sudoku. Use 0 for blank space:");

    for(int i = 0; i < 9; i++){
        printf("\n- - - | - - - | - - -");

        if(i == 2 || i == 5){
            printf("\n---------------------");
        }
    }

    printf("\e[10A\e[1G");
    fflush(stdout);

    while(true){
        k = getch();

        if(k >= 48 && k <= 57){
            k = k - 48;

            sudoku[c / 9][c % 9] = k;

            if(k == 0){
                printf("\e[2C");
            }else{
                printf("%i\e[1C", k);
            }

            c++;

            if(c % 3 == 0){
                printf("\e[2C");
            }

            if(c % 9 == 0 && c != 81){
                printf("\e[1B\e[1G");
            }

            if(c % 27 == 0 && c != 81){
                printf("\e[1B\e[1G");
            }

            fflush(stdout);

            if(c == 81){
                printf("\n");
                break;
            }
        }else if(k == 127){
            if(c > 0) c--;
            printf("\e[2D");

            if(c % 3 == 2){
                printf("\e[2D");
            }

            if(c % 9 == 8){
                printf("\e[1A\e[20C");
            }

            if(c % 27 == 26){
                printf("\e[1A");
            }

            printf("-\e[1D");

            fflush(stdout);
        }
    }
}

bool solveSudoku(int sudoku[9][9], int setSudoku[9][9]){
    bool forward = 1;
    int solutions = 0;

    printf("Solving... ");
    fflush(stdout);

    for(int i = 0; i < 81; i++){
        if(i < 0){
            if(solutions == 0){
                printf("\e[1G\e[1;31mNot solvable\e[0m\e[0K\n");
            }else{
                printf("\e[1G\e[1;32mFound %i solutions\e[0m\e[0K\n", solutions);
            }
            return false;
        }

        int x = i % 9;
        int y = i / 9; // will be truncated (floored)

        for(int j = 0; j < 10; j++){
            if(forward && setSudoku[y][x] > 0) break;

            if(!forward && setSudoku[y][x] > 0) {
                i = i - 2;
                break;
            }

            if(sudoku[y][x] >= 9){
                forward = false;
                sudoku[y][x] = setSudoku[y][x];
                i = i - 2;
                break;
            }

            forward = true;
            sudoku[y][x]++;

            if(checkSudoku(sudoku, x, y)){
                break;
            }
        }

        if(i == 80){
            printf("\e[1G\e[1;32mSolved!\e[0m\e[0K\n");
            printSudoku(sudoku, setSudoku);
            forward = false;
            i = i - 2;
            solutions++;
            printf("Solving... ");
            fflush(stdout);
        }
    }

    return true;
}

bool checkSudoku(int sudoku[9][9], int x, int y){
    int checkout[9];
    int field = sudoku[y][x];

    // check row
    if(!isAllUnique(sudoku[y], field)){
        return false;
    }

    // check cols
    for(int j = 0; j < 9; j++){
        checkout[j] = sudoku[j][x];
    }

    if(!isAllUnique(checkout, field)){
        return false;
    }

    // check blocks
    for(int j = 0; j < 3; j++){
        for(int k = 0; k < 3; k++){
            checkout[j * 3 + k] = sudoku[(y / 3) * 3 + j][(x / 3) * 3 + k];
        }
    }

    if(!isAllUnique(checkout, field)){
        return false;
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

            if(j % 3 == 2 && j != 8){
                printf("| ");
            }
        }

        if(i % 3 == 2 && i != 8){
            printf("\n---------------------");
        }

        printf("\n");
    }
}

bool isAllUnique(int row[9], int field){
    bool found = false;

    for(int i = 0; i < 9; i++){
        if(row[i] == field){
            if(found){
                return false;
            }else{
                found = true;
            }
        }
    }

    return true;
}

int getch(void){  // https://ubuntuforums.org/showthread.php?t=225713&page=2&p=1335772#post1335772
    int ch;
    struct termios oldt;
    struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt); /*store old settings */
    newt = oldt; /* copy old settings to new settings */
    newt.c_lflag &= ~(ICANON | ECHO); /* make one change to old settings in new settings */
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); /*apply the new settings immediately */
    ch = getchar(); /* standard getchar call */
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); /*reapply the old settings */
    return ch; /*return received char */
}
