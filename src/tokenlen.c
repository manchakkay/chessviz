//Определение длины строки с ходом
int tokenlen(char* token)
{
    int i = 0;
    while ((token[i] != 0) && (token[i] != 10)){
	i++;
    }
    return i;
}
