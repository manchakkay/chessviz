#include <stdio.h>

int main()
{
    //ПЕРЕМЕННЫЕ
    int type;
    char type_buffer[1];
    /*
	Тип хода
	"0" - Рокировка
	"1" - Тихий ход
	"2" - Взятие клетки
    */
    char figure[1];
    /*
	Вид фигуры
	"K" - Король
	"Q" - Ферзь
	"R" - Ладья
	"N" - Конь
	"B" - Слон
	"" - Пешка
    */
    int act;
    char act_buffer[4];
    /*
	Действие
	"0" - Шах
	"1" - Мат(конец игры)
	"2" - Взятие на проходе
    */
    int opt;
    char pawn_swap[1];
    /*
	Дополнения:
	"0" - Отсутствуют
	"1" - Пешка превращается в фигуру <pawn-swap>
    */
    char from[2];
    char to[2];
    char castle[2];
    /*
	Ячейки:
	<from> - стартовая клетка
	<to> - целевая клетка
	<castle> - клетка для выполнения рокировки
    */
    char white[10];
    char black[10];
    /*
	Ходы игроков(разделяются пробелом):
	<white> - ход белого (первый)
	<black> - ход чёрного (второй)
    */
    char step[22];
    /*
	Размен:
	<step> - строка для буферизации одного размена
    */
    char* field[8][8] = {{ "r", "n", "b", "q", "k", "b", "n", "r" },
			{ "p", "p", "p", "p", "p", "p", "p", "p" },
			{ " ", " ", " ", " ", " ", " ", " ", " " },
			{ " ", " ", " ", " ", " ", " ", " ", " " },
			{ " ", " ", " ", " ", " ", " ", " ", " " },
			{ " ", " ", " ", " ", " ", " ", " ", " " },
			{ "P", "P", "P", "P", "P", "P", "P", "P" },
			{ "R", "N", "B", "Q", "K", "B", "N", "R" }};
    /*
	Шахматное поле
    */
    //ФУНКЦИИ

    void printfield()
    {
	int i,j;
	for ( i = 0, i < 8, i++ ){
		for ( j = 0, j < 8, j++ ){
		    printf("%3c",field[i][j]);
		}
	printf("\n");
	}
    }

    //КОД
    
    void printfield();

    FILE *file;
    char *temp;
    char filename[256];
    
    printf("Файл ходов:");
    fgets(filename,255,stdin);
    file = fopen(filename,"r");
    
    while(1){
	temp = fgets(step,sizeof(step),file);
	if (temp == NULL){
	    break;
	} else {
	    printf("%s",step);
	}
    }
    
    return 0;
}
