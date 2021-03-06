#include <time.h>
#include "utils.h"

void read_file(char *file_name, float *array, unsigned long size)
{
    FILE *input_file = fopen(file_name, "rb"); // Abrir archivo
    fread(array, sizeof(float), size, input_file);
    fclose(input_file); //Cerrar archivo
}

void write_file(char *file_name, float *array, unsigned long size)
{
    FILE *output_file = fopen(file_name, "wb"); // Abrir archivo
    fwrite(array, sizeof(float), size, output_file);
    fclose(output_file); //Cerrar archivo
}

void write_file_normal(char *file_name, double *array, unsigned long size)
{
    FILE *output_file = fopen(file_name, "w"); // Abrir archivo
    fprintf(output_file, "%s\n", "time");
    for (int i = 0; i < size; i++)
        fprintf(output_file, "%f\n", array[i]);
    fclose(output_file); //Cerrar archivo
}

void print_float_array(float *array, unsigned long size)
{
    for (unsigned long i = 0; i < size; i++)
        printf("%f\n", array[i]);
}

unsigned long pow2(int exp)
{
    if (exp == 0)
        return 1;
    unsigned long res = 1;
    for (int i = 0; i < exp; i++)
        res = res * 2;
    return res;
}

int get_opt(int argc, char *argv[], char **i, char **o, unsigned long *n, int *d, int *l, int *h)
{
    int c;

    opterr = 0;
    if (argc < 13)
    {
        printf("The number of parameters less than requested\n");
        return 0;
    }
    else if (argc > 13)
    {
        printf("The number of parameters greater than the requested\n");
        return 0;
    }

    while ((c = getopt(argc, argv, "i:o:N:d:l:h:")) != -1)
    {
        switch (c)
        {
        case 'i':
            *i = optarg;
            break;
        case 'o':
            *o = optarg;
            break;
        case 'N':
            sscanf(optarg, "%lu", n);
            break;
        case 'd':
            sscanf(optarg, "%i", d);
            break;
        case 'l':
            sscanf(optarg, "%i", l);
            break;
        case 'h':
            sscanf(optarg, "%i", h);
            break;
        case '?':
            if (optopt == 'i' || optopt == 'o' || optopt == 'N' || optopt == 'd' || optopt == 'l' || optopt == 'h')
            {
                fprintf(stderr, "Opcion -%c requiere un argumento.\n", optopt);
                exit(EXIT_FAILURE);
            }
            else if (isprint(optopt))
                fprintf(stderr, "Opcion desconocida `-%c'.\n", optopt);
            else
                fprintf(stderr, "Opcion con caracter desconocido `\\x%x'.\n", optopt);
        default:
            abort();
        }
    }
    return 1;
}