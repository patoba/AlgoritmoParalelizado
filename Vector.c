#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//De stdio se utiliza printf
//De stdlib se utiliza calloc, realloc, y free

typedef struct Vector{
    int* conjunto_numeros;
    int cantidad_elementos;
}Vector;


int num_azar(int de, int a){
    return (int) (rand () % (a-de+1) + de);
}

Vector VECTOR_crear_vector(int num_elementos){
    Vector vector;
    vector.conjunto_numeros = (int*) calloc(num_elementos, sizeof(int));
    vector.cantidad_elementos = num_elementos;
    return vector;
}

int VECTOR_tamano_vector(Vector vector){
    return vector.cantidad_elementos;
}

int VECTOR_anadir_elemento(Vector* vector, int num, int posicion){
    int tamano = VECTOR_tamano_vector(*vector);
    if(tamano >= posicion ) {
        (*vector).cantidad_elementos = VECTOR_tamano_vector(*vector) + 1;
        (*vector).conjunto_numeros = (int*) realloc((*vector).conjunto_numeros, sizeof(int)*(tamano + 1));
        int i;
        for(i = tamano; i > posicion; i--){
            (*vector).conjunto_numeros[i] = (*vector).conjunto_numeros[i - 1];
        }
        (*vector).conjunto_numeros[i] = num;
        return 1;
    }
    return 0;
}

void VECTOR_anadir_elemento_final(Vector* vector, int num){
    VECTOR_anadir_elemento(vector, num, VECTOR_tamano_vector(*vector));
}

int VECTOR_establecer_elementos_posicion_determinada(Vector* vector, int num, int posicion){
    int tamano = VECTOR_tamano_vector(*vector);
    if(tamano >= posicion){
        (*vector).conjunto_numeros[posicion] = num;
        return 1;
    }
    return 0;
}

int VECTOR_ver_elemento_en_posicion_a(Vector vector, int posicion){
    int tamano = VECTOR_tamano_vector(vector);
    int num = 0;
    if(tamano > posicion){
        num = vector.conjunto_numeros[posicion];
    }
    return num;
}

int VECTOR_intercambio(Vector* vector, int pos1, int pos2){
    int tamano = VECTOR_tamano_vector(*vector);
    if(tamano > pos1 && tamano > pos2){
        int temp1 = VECTOR_ver_elemento_en_posicion_a(*vector, pos1);
        int temp2 = VECTOR_ver_elemento_en_posicion_a(*vector, pos2);
        VECTOR_establecer_elementos_posicion_determinada(vector, temp1, pos2);
        VECTOR_establecer_elementos_posicion_determinada(vector, temp2, pos1);
        return 1;
    }
    return 0;
}

Vector VECTOR_rellenado_caso_azar(int num_elementos, int de, int a){
    Vector v = VECTOR_crear_vector(num_elementos);
    int i, azar;
    for (i = 0; i < num_elementos; i++) {
        azar = num_azar(de, a);
        VECTOR_establecer_elementos_posicion_determinada(&v, azar, i);
    }
    return v;
}

Vector VECTOR_rellenado_peor_caso(int num_elementos){
    return VECTOR_rellenado_caso_azar(num_elementos, -214748364, 214748364);
}

Vector VECTOR_mejor_caso(int num_elementos){
    Vector v = VECTOR_crear_vector(num_elementos);
    int i;
    for (i = 0; i < num_elementos; i++) {
        VECTOR_establecer_elementos_posicion_determinada(&v, i, i);
    }
    return v;
}

Vector VECTOR_invertido_caso(int num_elementos){
    Vector v = VECTOR_crear_vector(num_elementos);
    int i;
    for (i = 0; i < num_elementos; i++) {
        VECTOR_establecer_elementos_posicion_determinada(&v, num_elementos - i - 1, i);
    }
    return v;
}

int VECTOR_abs(int num){
    if (num < 0) {
        return -num;
    }
    return num;
}

int VECTOR_obtener_medio(Vector A, int p, int r){
    int prom = 0;
    int i;
    for(i = p; i < r + 1; i++){
        prom = prom + VECTOR_ver_elemento_en_posicion_a(A, i);
    }
    int resta = r + 1 - p;
    prom = ceil(prom / resta); //Hacia abajo
    int ant = 0;
    int pos = 0;
    for (i = 0; i < resta; i++) {
        int act = prom - VECTOR_ver_elemento_en_posicion_a(A, i + p);
        if (ant == 0 || ant >  VECTOR_abs(act)) {
            ant = VECTOR_abs(act);
            pos = i + p;
        }
    }
    return pos;
}

void VECTOR_imprimir_vector(Vector vector){
    int i;
    int tamano = VECTOR_tamano_vector(vector);
    printf("[");
    for(i = 0; i < tamano - 1; i++){
        printf("%d, ", vector.conjunto_numeros[i]);
    }
    printf("%d]\n", vector.conjunto_numeros[i]);
}

void VECTOR_liberar_vector(Vector* vector){
    free((*vector).conjunto_numeros);
}

/*
int main(int argc, char const *argv[]) {
    Vector v = VECTOR_crear_vector(10);
    VECTOR_imprimir_vector(v);
    VECTOR_liberar_vector(&v);
    return 0;
}
*/
