typedef struct Vector{
    int* conjunto_numeros;
    int cantidad_elementos;
}Vector;

int num_azar(int de, int a);
Vector VECTOR_crear_vector(int num_elementos);
int VECTOR_tamano_vector(Vector vector);
int VECTOR_anadir_elemento(Vector* vector, int num, int posicion);
void VECTOR_anadir_elemento_final(Vector* vector, int num);
int VECTOR_establecer_elementos_posicion_determinada(Vector* vector, int num, int posicion);
int VECTOR_ver_elemento_en_posicion_a(Vector vector, int posicion);
int VECTOR_intercambio(Vector* vector, int pos1, int pos2);
Vector VECTOR_rellenado_caso_azar(int num_elementos, int de, int a);
Vector VECTOR_rellenado_peor_caso(int num_elementos);
Vector VECTOR_mejor_caso(int num_elementos);
Vector VECTOR_invertido_caso(int num_elementos);
void VECTOR_imprimir_vector(Vector vector);
void VECTOR_liberar_vector(Vector* vector);
int VECTOR_obtener_medio(Vector A, int p, int r);
