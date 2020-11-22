#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void write_file(char *file_name, float *array, unsigned long size)
{
    FILE *output_file = fopen(file_name, "wb"); // Abrir archivo
    fwrite(array, sizeof(float), size, output_file);
    fclose(output_file); //Cerrar archivo
}

void create_file(char *file_name, unsigned long size)
{
    float *numbers = (float *)malloc(sizeof(float) * size);
    float float_random;
    srand((unsigned)time(NULL));
    for (unsigned long i = 0; i < size; i++)
    {
        float_random = (float)rand() / RAND_MAX;
        numbers[i] = float_random;
    }
    write_file(file_name, numbers, size);
}

int main()
{

    create_file("2097152floats.raw",2097152);
    //create_file("1600000floats.raw",1600000l);
}