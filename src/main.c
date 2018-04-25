#include "main.h"

char* TC_W = "\033[0m";
char* BC_R = "\033[1;31m";
char* B_Y = "\033[1;33m";
char* BC_W = "\033[1;37m";
char* BG_W = "\033[40m\033[1m";

//Вывод предупреждений
void warning(char* yellow, char* white)
{
    printf("%s(Внимание) %s%s%s%s\n",BC_W, B_Y, yellow, TC_W, white);
}

//Вывод ошибок
void error(char* red, char* white, int errorcode)
{
    printf("%s(Ошибка) %s%s%s%s\n",BC_W, BC_R, red, TC_W, white);
    exit(errorcode);
}

//Вывод состояния доски
int main(int argc, char *argv[])
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
    //int act;
    //char* act_buffer[4];
    /*
	Действие
	"0" - Шах
	"1" - Мат(конец игры)
	"2" - Взятие на проходе
    */
    //int opt;
    //char pawn_swap[1];
    /*
	Дополнения:
	"0" - Отсутствуют
	"1" - Пешка превращается в фигуру <pawn-swap>
    */
    int from[2];
    int to[2];
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
    int ended = 0;
    /*
	Мат:
	Определеляет, был ли мат
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
    void error(char*, char*, int);
    void warning(char*, char*);
    
    //КОД
    
    //Подготавливаем вторичные переменные
    FILE *file;
    char *temp;
    char filename[256];
    int loop = 0;
    int count, i;
    //int imove, jmove;
    //Производим ввод файла с записью ходов
    printf("%sАдрес исходного файла:%s\n",BG_W,TC_W);
    scanf("%s",filename);
    file = fopen(filename,"r");
    if (file){
	printf("\n");
	//Переключаем строки
	printfield(field);
	printf("\n");
	while(1){
	    //Заносим строку в переменную
	    temp = fgets(step,sizeof(step),file);
	    if (temp == NULL){
		break;
	    } else {
		//Определяем индекс хода относительно пробела между ними
		if (strchr(step,' ') != NULL){
		    count = 1;
		} else {
		    count = 0;
		}
		//Делим строку одного шага(ход белого и чёрного) на ходы
		char *token, *last;
		int len;
		token = strtok_r(step, " ", &last);
		for(i = 0; i <= count; i++){
		    //Выводим ход в правильном виде, учитывая знак новой строки в конце
		    printf ("%s%d. %s%s\n",B_Y, loop+1, BC_W, token);
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
		    } else if (tolower(token[0]) == token[0]){
			figure = "P";
		    } else {
			error("Невозможно определить фигуру",", фигуры соответствующие формату: K, Q, R, N, B или не указывайте ничего для определения пешки", 2);
		    }
		    //Фигура нам известа, определяем тип хода, используем для этого подготовленную заранее ф-ию(int searchsym)
		    if ((searchsym(token, len, "-") == 1) && (searchsym(token, len, "0") == 0)){
			type = 1;
		    } else if ((searchsym(token, len, "x") == 1) && (searchsym(token, len, "0") == 0)){
			type = 0;
		    } else if ((searchsym(token, len, "0") == 2) && (searchsym(token, len, "-") == 1)){
			type = 2;
		    } else if ((searchsym(token, len, "0") == 3) && (searchsym(token, len, "-") == 2)){
			type = 3;
		    } else {
			error("Ход нестандартного формата",", попробуйте: e2-e4, e2xe4, 0-0, 0-0-0",3);
		    }
		    if (type < 2){
			//В зависимости от типа хода, узнаём, что и куда переместить
			int ps;
			//Проверяем является ли фигура пешкой
			if (*(figure) == 80){
			    ps = 1;
			} else {
			    ps = 0;
			}
			//Делим ход на точку отправления и прибытия. Переводим всё это в массивы целочисленного типа
			from[0] = token[1-ps]-97;
			from[1] = 8-(token[2-ps]-48);
			to[0] = token[4-ps]-97;
			to[1] = 8-(token[5-ps]-48);
			//Проверка на правильность действия
			if ((*(field[to[1]][to[0]]) == 32) && (type == 0)){
			    error("Невозможно произвести захват пустой клетки", ", для обозначения тихого хода используйте формат: e2-e4, вместо e2xe4",5);
			}
			//Проверка на правильность фигуры
			if (toupper(*field[from[1]][from[0]]) != *figure){
			    error("Фигура в клетке не соответствует взятой", ", используемая фигура должна соответствовать фигуре на столе",6);
			}
			//Проверка на выход за пределы поля
			if ((from[0] > 7) || (from[1] > 7) || (to[0] > 7) || (to[1] > 7) ||  (from[0] < 0) || (from[1] < 0) || (to[0] < 0) || (to[1] < 0)){
			    error("Ход совершается за пределами поля", ", допустимые значения (a-f,1-8)",4);
			}
			//Проверка на соответствие хода фигуре
			//imove = abs(from[1] - to[1]);
			//jmove = abs(from[0] - to[0]);
			
			
			//printf("<%d:%d>\n",imove,jmove);
			
			//Обработка ходов
			field[to[1]][to[0]] = field[from[1]][from[0]];
			field[from[1]][from[0]] = " ";
		    } else {
		    //Рокировки
			
		    }
		    //Конец работы с ходами, далее вывод
		    printfield(field);
		    printf("\n");
		    //Сколько было матов?
		    ended+=searchsym(token, len, "#");
		    //Переключаем ходы
		    token = strtok_r(NULL, " ", &last);
		}
	    }
	    loop++;
	}
	if (ended == 0){
	    warning("Игра не закончена",", в списке ходов не был найден мат");
	} else if (ended > 1){
	    warning("Больше одного мата",", по пути игры было замечено несколько матов");
	}
    } else {
	//Ошибка говорящая сама за себя
	error("Файл по такому адресу не найден","",1);
    }
    return 0;
}
