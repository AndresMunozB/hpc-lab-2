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
    get_opt(argc, argv, &iValue, &oValue, &NValue, &dValue);

    // VARIABLES A UTILIZAR
    List *list = list_init(NValue);
    clock_t t;
    double time_taken;
    //create_file("1600floats.raw",1600);
    for (int i = 0; i < 20; i++)
    {
        read_file(iValue, list->data, list->len); // LEER ARCHIVO
        t = clock();
        bubble_sort(list->data, list->len, dValue);
        t = clock() - t;
        time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        printf("TEST %d: bubble_sort() took %f seconds to execute \n", i, time_taken);
    }

    list_free(list);
}