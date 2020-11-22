#include <stdio.h>
#include <stdlib.h>

void read_file(char *file_name, float *array, unsigned long size)
{
    FILE *input_file = fopen(file_name, "rb"); // Abrir archivo
    fread(array, sizeof(float), size, input_file);
    fclose(input_file); //Cerrar archivo
}

int is_sorted(char *name_file, unsigned long size)
{
    float *data = (float *)malloc(sizeof(float) * size);
    printf("vivo\n");
    read_file(name_file, data, size);
    
    for (unsigned long i=0; i < size - 1; i++)
    {
        printf("i %lu:(%f - %f) \n", i,data[i],data[i+1]);
        if (data[i] > data[i + 1])
            return 0;
    }
    free(data);
    return 1;
}

int main(){
    printf("vivo1\n");
    if(is_sorted("./2097152floatssorted2.raw",2097152))
        printf("IS SORTED\n");
    else
        printf("IS NOT SORTED\n");
    return 0;
}