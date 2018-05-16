#include "stdio.h"

char* T_W = "\033[0m";
char* B_C = "\033[1;36m";
char* BR_W = "\033[7m\033[1m";
char* BW_W = "\033[40m\033[1m";

void printfield(char* field[8][8])
{
    int i,j;
    for ( i = 0; i < 8; i++ ){
	printf("%s%d%s  ", B_C, 8-i, T_W);
	for ( j = 0; j < 8; j++ ){
	    if (((i+j)%2) == 1){
		printf("%s%2c %s",BW_W,*field[i][j],T_W);
	    } else {
		printf("%s%2c %s",BR_W,*field[i][j],T_W);
	    }
	}
	printf("\n");
    }
    printf("\n%s    a  b  c  d  e  f  g  h%s\n", B_C, T_W);
}
