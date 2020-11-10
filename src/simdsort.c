#include <time.h>
#include "functions.h"
#include "utils.h"

int main(int argc, char *argv[])
{
    // PARAMETROS DE ENTRADA
    unsigned long NValue = 0;
    int dValue = 0;
    char *iValue = NULL;
    char *oValue = NULL;
    if (get_opt(argc, argv, &iValue, &oValue, &NValue, &dValue) == 0)
        return 0;

    // VARIABLES A UTILIZAR
    List *list = list_init(NValue);
    List *list_sorted = list_create();
    clock_t t;
    double time_taken;

    read_file(iValue, list->data, list->len); // LEER ARCHIVO
    t = clock();
    //print_float_array(list->data,list->len);
    simd_sort(list, list_sorted, dValue); //ORDENAR LOS VALORES
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    if(dValue)
        printf("simd_sort() took %f seconds to execute \n", time_taken);
    //list_print(list_sorted);
    write_file(oValue, list_sorted->data, list_sorted->len); //ESCRIBIR LOS DATOS ORDENADOS
    //create_file("nuevo.raw", 16000000);

    // LIBERAR MEMORIA
    list_free(list);
    list_free(list_sorted);
    return 0;
}