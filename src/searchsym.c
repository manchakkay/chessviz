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
