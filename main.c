#include <stdio.h>

int main()
{
    int i,j;
    int chess[8][8] = {	{ 1, 2, 3, 5, 4, 3, 2, 1 },
			{ 9, 9, 9, 9, 9, 9, 9, 9 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 9, 9, 9, 9, 9, 9, 9, 9 },
			{ 1, 2, 3, 5, 4, 3, 2, 1 }};
    
    printf("1 - ладья, 2 - конь, 3 - слон, 5 - король, 4 - ферзь, 9 - пешка, 0 - пустая клетка\n");
    
    for( i = 0; i < 8; i++){
	for( j = 0; j < 8; j++){
	    printf("%2d ",chess[i][j]);
	}
	printf("\n");
    }

    return 0;
}