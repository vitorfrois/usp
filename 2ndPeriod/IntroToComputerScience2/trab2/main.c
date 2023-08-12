#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <math.h>

typedef struct {
    unsigned char audio;
    double complex coef;
    double polar;
    int n;
}Data;

char* readString(){
    char *string = malloc(sizeof(char));
    char character = ' ';
    int nCharsString = 0;
    do {
            character = getchar();
            string = realloc(string, (nCharsString + 1) * sizeof(char*));
            string[nCharsString] = character;
            nCharsString++;
    } while(character != '\n' && character != '\r');
    if(character == '\r')
        character = getchar();

    string[nCharsString - 1] = '\0';
    return string;
}

unsigned char* read_wav_data(char* fname, int* size, unsigned char **header) {
    FILE* fp = fopen(fname, "rb");
    if (fp == NULL){printf("Erro!\n");}
    unsigned char buf4[4];

    fread(*header, 44, 1, fp);
    rewind(fp);

    fseek(fp, 40, SEEK_SET);
    fread(buf4, sizeof(buf4), 1, fp);
    int dataSize = buf4[0] | buf4[1]<<8 | buf4[2]<<16 | buf4[3]<<24;
    *size = dataSize;
    
    unsigned char* data = malloc(sizeof(*data) * (dataSize));

    int i = 0;
    while (i < dataSize) {
        fread(&data[i++], sizeof(unsigned char), 1, fp);
    }
    fclose(fp);
    return data;
}

void insertionSort(Data* data, int lenght, int cap, char* option){
	int i, j;

    if(strcmp(option, "polar") == 0){
        Data key;
        for (i = 1; i < lenght; i++) {
            key = data[i];
            j = i - 1;

            /* Move elements of data->polar[0..i-1], that are
            greater than key, to one position ahead
            of their current position */
            while (j >= 0 && data[j].polar < key.polar) {
                data[j+1] = data[j];
                j = j - 1;
            }
            data[j+1] = key;
        }
            
    }else if(strcmp(option, "n") == 0){
        //printf("before n insertionSort:\n");
        for(i = 0; i < cap; i++)
            printf("%d\n", (int) data[i].polar);
        Data key;
        for (i = 1; i < lenght; i++) {
            key = data[i];
            j = i - 1;

            /* Move elements of data->n[0..i-1], that are
            greater than key, to one position ahead
            of their current position */
            while (j >= 0 && data[j].n > key.n) {
                data[j+1] = data[j];
                j = j - 1;
            }
            data[j+1] = key;
        } 
    }
}

/*
    Discrete Fourier Transform
    Para os curiosos, atentem-se a complexidade de tempo dela...
    é por esse motivo que os áudios são bem curtos
*/
void DFT(Data* data, int lenght) {
    int negativeValues = 0;
    for (int k = 0; k < lenght; k++) {
        for (int n = 0; n < lenght; n++) {
            data[k].coef += data[n].audio * cexp((-2.0 * M_PI * (((k+1) * n * 1.0) / (lenght * 1.0))) * _Complex_I);
        }
        data[k].polar = sqrt(pow(creal(data[k].coef), 2.0) + pow(cimag(data[k].coef), 2.0));
        if(creal(data[k].coef) <= 0.0 && cimag(data[k].coef) <= 0.0)
            negativeValues++;
    }
    printf("%d\n", negativeValues);
}

void IFT(Data* data, int lenght) {
    int n, k;

    for (n = 0; n < lenght; n++) {
        double complex aux = 0.0 + 0.0 * I;
        for (k = 0; k < lenght; k++) {
            aux += data[k].coef * cexp((2.0 * M_PI * (((k+1) * n * 1.0) / (lenght * 1.0))) * _Complex_I); 
        }
        aux = aux / lenght+1;
        data[n].audio = (int) creal(aux);
    }
}

void filterData(Data* data, int lenght, int cap){
    for(int i = cap; i < lenght; i++)
        data[i].coef = 0.0;
}

int main(){
    char* fileName = readString();
    int size, cap;

    unsigned char* header = malloc(sizeof(char) * 44);

    scanf("%d", &cap);
    unsigned char* aux = read_wav_data(fileName, &size, &header);
    Data* data = malloc(sizeof(Data) * size);
    for(int i = 0; i < size; i++){
        data[i].audio = aux[i];
        data[i].n = i;
    }

    printf("%d\n", size);

    DFT(data, size);
    insertionSort(data, size, cap, "polar");
    filterData(data, size, cap);
    
    insertionSort(data, size, cap, "n");
    
    IFT(data, size);

    FILE* fp = fopen("compressed.wav", "wb");
    fwrite(header, 1, 44, fp);
    fwrite(&data->audio, 1, size * sizeof(unsigned char), fp);

    free(data);
    free(header);
    free(fileName);
    free(aux);
    
    fclose(fp);
    return 0;
}