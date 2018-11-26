#include <omp.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "Vector.h"

int partition_original_paralelo(Vector* arr, int low, int high){
    int i = low - 1;           // index of smaller element
    int pivot = VECTOR_ver_elemento_en_posicion_a(*arr, high);     // hector bb
    int j, elemento;
    for(j = low; j < high; j++){
        // If current element is smaller than or
        // equal to pivot
        elemento = VECTOR_ver_elemento_en_posicion_a(*arr, j);
        if(elemento <= pivot){
            // increment index of smaller element
            i = i + 1;
            VECTOR_intercambio(arr, i, j);
        }
    }
    i = i + 1;
    VECTOR_intercambio(arr, i, high);
    return i;
}

void quickSort_original_paralelo(Vector* arr, int low, int high){
    if(low < high){
        int pi = partition_original_paralelo(arr, low, high);
        // printf("Maximo= %d\n",omp_get_max_threads());
        // printf("Hilos= %d\n", omp_get_num_threads());
        // printf("SOy= %d\n", omp_get_thread_num());
        if(omp_get_num_threads() < omp_get_max_threads()){
            //printf("Entre");
            #pragma omp parallel
            {
                #pragma omp single nowait
                {
                    quickSort_original_paralelo(arr, low, pi - 1);
                }
                #pragma omp single nowait
                {
                    quickSort_original_paralelo(arr, pi + 1, high);
                }

            }
        }else{
            quickSort_original_paralelo(arr, low, pi - 1);
            quickSort_original_paralelo(arr, pi + 1, high);
        }
    }
}

void QuickSortOriginal_paralelo(Vector* A){
    int extremo_derecho = VECTOR_tamano_vector(*A) - 1;
    quickSort_original_paralelo(A, 0, extremo_derecho);
}

int partition(Vector* arr, int low, int high){
    int i = low - 1;
    int pivot = VECTOR_ver_elemento_en_posicion_a(*arr, high);
    int j, elemento;
    for(j = low; j < high; j++){
        elemento = VECTOR_ver_elemento_en_posicion_a(*arr, j);
        if(elemento <= pivot){
            i = i + 1;
            VECTOR_intercambio(arr, i, j);
        }
    }
    i = i + 1;
    VECTOR_intercambio(arr, i, high);
    return i;
}

void quickSort(Vector* arr, int low, int high){
    if(low < high){
        int pi = partition(arr, low, high);
        if(omp_get_num_threads() < omp_get_max_threads() ){
            #pragma omp parallel
            {
                #pragma omp single nowait
                {
                    quickSort(arr, low, pi - 1);
                }
                #pragma omp single nowait
                {
                    quickSort(arr, pi + 1, high);
                }
            }
        }else{
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }

    }
}

void QuickSort(Vector* A){
    int extremo_derecho = VECTOR_tamano_vector(*A) - 1;
    quickSort(A, 0, extremo_derecho);
}


double DoubleQuickSort_paralelo(Vector* arreglo){
    double tiempo = omp_get_wtime();
    int i;
    int contdir=0;
    int continv=0;
    int tamano = VECTOR_tamano_vector(*arreglo);
    #pragma omp parallel for private(i) reduction(+:contdir)
    for (i = 1; i < tamano; i++) {
        int elemento1 = VECTOR_ver_elemento_en_posicion_a(*arreglo, i-1);
        int elemento2 = VECTOR_ver_elemento_en_posicion_a(*arreglo, i);
        if(elemento1 <= elemento2){
            contdir += 1;
        }
    }
    //printf("contdir=%d, tamano=%d\n", contdir, tamano);
    if(contdir == tamano - 1){
        //printf("aqui");
        tiempo = omp_get_wtime() - tiempo;
        return tiempo;
    }
    #pragma omp parallel for private(i) reduction(+:continv)
    for (int i = 0; i < tamano; i++) {
        int elemento1 = VECTOR_ver_elemento_en_posicion_a(*arreglo, i-1);
        int elemento2 = VECTOR_ver_elemento_en_posicion_a(*arreglo, i);
        if(elemento1 >= elemento2){
            continv += 1;
        }
    }
    if(continv == tamano - 1){
        int longitud = floor(tamano / 2); //Redondeo hacia arriba
        #pragma omp parallel for private(i)
        for(i = 0; i < longitud; i++){
            VECTOR_intercambio(arreglo, i, tamano - 1 - i);
        }
        tiempo = omp_get_wtime() - tiempo;
        return tiempo;
    }
    int division = ceil((tamano - 1) / 1.7);
    if(continv >= division || contdir >= division){
        QuickSort(arreglo);
    }else{
        QuickSortOriginal_paralelo(arreglo);
    }
    tiempo = omp_get_wtime() - tiempo;
    return tiempo;
}

double QuickSortParalelo_peor_caso(int cantidad_elementos){
    Vector v = VECTOR_rellenado_caso_azar(cantidad_elementos, 0, 1);
    // VECTOR_imprimir_vector(v);
    double tiempo = DoubleQuickSort_paralelo(&v);
    // printf("\n");
    // VECTOR_imprimir_vector(v);
    VECTOR_liberar_vector(&v);
}

double QuickSortParalelo_promedio_caso(int cantidad_elementos){
    Vector v = VECTOR_rellenado_caso_azar(cantidad_elementos, -100, 100);
    VECTOR_imprimir_vector(v);
    double tiempo = DoubleQuickSort_paralelo(&v);
    printf("\n");
    VECTOR_imprimir_vector(v);
    VECTOR_liberar_vector(&v);
    return tiempo;
}

double QuickSortParalelo_mejor_caso(int cantidad_elementos){
    Vector v = VECTOR_mejor_caso(cantidad_elementos);
    //VECTOR_imprimir_vector(v);
    double tiempo = DoubleQuickSort_paralelo(&v);
    //printf("\n");
    //VECTOR_imprimir_vector(v);
    VECTOR_liberar_vector(&v);
    return tiempo;
}

double QuickSortParalelo_invertido_caso(int cantidad_elementos){
    Vector v = VECTOR_invertido_caso(cantidad_elementos);
    //VECTOR_imprimir_vector(v);
    double tiempo = DoubleQuickSort_paralelo(&v);
    //printf("\n");
    //VECTOR_imprimir_vector(v);
    VECTOR_liberar_vector(&v);
    return tiempo;
}

void nombre_archivo(char *nombre, int caso){
    const char* carpeta = "datos/paralelo/";
    strcat(nombre, carpeta);
    if (caso == 0) {
        strcat(nombre, "peor_caso.txt");
    }else if(caso == 1){
        strcat(nombre, "mejor_caso.txt");
    }else{
        strcat(nombre, "caso_promedio.txt");
    }
}

FILE* abrir_archivo(const char* nombre_archivo){
    FILE* archivo = fopen(nombre_archivo, "w+");
    return archivo;
}

void cerrar_archivos(int num_archivos, FILE* archivos[num_archivos]){
    int i;
    for (i = 0; i < num_archivos; i++) {
        fclose(archivos[i]);
    }
}

void creacion_de_archivos(int de, int a, int incremento){
    int i, j;
    char casos[3][30];
    FILE* archivos[3];

    for (i = 0; i < 3; i++) {
        nombre_archivo(casos[i], i);
        archivos[i] = abrir_archivo(casos[i]);
    }
    for(i = de; i <= a; i += incremento){
        for(j = 0; j < 3; j++){
            double tiempo = 0;
            if(j == 0){
                tiempo = QuickSortParalelo_peor_caso(i);
            }else if(j == 1){
                //tiempo = QuickSortParalelo_mejor_caso(i);
            }else{
                //tiempo = QuickSortParalelo_promedio_caso(i);
            }
            fprintf(archivos[j], "%d,%lf\n", i, tiempo);

        }
    }
    cerrar_archivos(3, archivos);
}

///*10000,20000,1000
int main(int argc, char const *argv[]) {//100-1

    creacion_de_archivos(0, 10000, 100);

    //QuickSortParalelo_promedio_caso(31);
    //QuickSortParalelo_mejor_caso(31);
    //QuickSortParalelo_invertido_caso(31);
    /*
    QuickSortParalelo_mejor_caso(40);
    printf("\n");
    QuickSortParalelo_peor_caso(40);
    */
    return 0;
}
//*/
