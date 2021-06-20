#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int getch();

int main(){
	char x = ' ';

	printf("Press any key to continue...\n");
	x = getch();

	printf("The key you entered is: %c \n", x);

	return 0;
}

int getch(void){
    int ch;
    struct termios oldt;
    struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt); /*store old settings */
    newt = oldt; /* copy old settings to new settings */
    newt.c_lflag &= ~(ICANON | ECHO); /* make one change to old settings in new settings */
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); /*apply the new settings immediatly */
    ch = getchar(); /* standard getchar call */
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); /*reapply the old settings */
    return ch; /*return received char */
}
