#include <stdio.h>
#include <string.h>

char *funcion(char *p)
{
    strcpy(p,"adios");
    return p;
}
int main()
{
    char frase[30] = "";

    strcpy(frase,"hola");
    printf("Antes --> %s\n",frase);
    printf("Despues --> %s\n",funcion(frase));
    return 0;
}
