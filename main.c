#include <stdio.h>
#include <string.h>

#define TC_W   "\033[0m"
#define BC_C   "\033[1;36m"
#define BC_W   "\033[1;37m"

//Вывод состояния доски
void printfield(char* field[8][8])
{
    int i,j;
    for ( i = 0; i < 8; i++ ){
	printf("%s%d%s", BC_C, 8-i, BC_W);
	for ( j = 0; j < 8; j++ ){
	    printf("%2c",*field[i][j]);
	}
	printf("\n");
    }
    printf("%s  a b c d e f g h%s\n", BC_C, TC_W);
}

//Определение длины строки с ходом
int tokenlen(char* token)
{
    int i = 0;
    while ((token[i] != 0) && (token[i] != 10)){
	i++;
    }
    return i;
}

//Поиск кол-ва символов в строке
int searchsym(char* t, int l, char* sym)
{
    int i,ta,sa;
    int c = 0;
    sa = *sym;
    for (i = 0; i<l; i++){
	ta = t[i];
	if (ta == sa){
	    c++;
	}
    }
    return c;
}

int main()
{
    //ПЕРЕМЕННЫЕ
    int type;
    /*
	Тип хода
	"2" - Рокировка
	"1" - Тихий ход
	"0" - Взятие клетки
    */
    char* figure;
    /*
	Вид фигуры
	"K" - Король
	"Q" - Ферзь
	"R" - Ладья
	"N" - Конь
	"B" - Слон
	"P" - Пешка
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
    
    void printfield(char* [8][8]);
    int tokenlen(char* );
    int searchsym(char* , int, char*);
    
    //КОД
    
    //Подготавливаем вторичные переменные
    FILE *file;
    char *temp;
    char filename[256];
    int loop = 0;
    int ws = 0;
    int bs = 0;
    int tempid, count, i;
    //Производим ввод файла с записью ходов
    printf("Адрес исходного файла:\n");
    scanf("%s",filename);
    file = fopen(filename,"r");
    printf("\n");
    if (file){
	while(1){
	    //Берём одну строку из файла
	    temp = fgets(step,sizeof(step),file);
	    if (temp == NULL){
		break;
	    } else {
		//Определяем индекс хода относительно пробела между ними
		if (strchr(step,' ') != NULL){
		    count = 1;
		} else {
		    count = 0;
		};
		//Делим строку одного шага(ход белого и чёрного) на ходы
		char *token, *last;
		int len;
		token = strtok_r(step, " ", &last);
		for(i = 0; i <= count; i++){
		    //Выводим ход в правильном виде, учитывая знак новой строки в конце
		    printf ("%s", token);
		    if (i != count){
			printf("\n");
		    }
		    //Здесь ходы разделены на токены, можно с ними работать
		    len = tokenlen(token);
		    //Определена длина токена, узнаём какая фигура
		    if (token[0] == 75){
			figure = "K";
		    } else if (token[0] == 81){
			figure = "Q";
		    } else if (token[0] == 82){
			figure = "R";
		    } else if (token[0] == 78){
			figure = "N";
		    } else if (token[0] == 66){
			figure = "B";
		    } else {
			figure = "P";
		    }
		    //Фигура нам известа, определяем тип хода, используем для этого подготовленную заранее ф-ию(int search sym)
		    type = searchsym(token, len, "-");
		    //Конец работы с ходами, далее вывод и переключение строк
		    printfield(field);
		    printf("\n");
		    token = strtok_r(NULL, " ", &last);
		}
	    }
	    loop++;
	}
    } else {
	//Ошибка говорящая сама за себя
	printf("Файл по такому адресу не найден");
    }
    return 0;
}
