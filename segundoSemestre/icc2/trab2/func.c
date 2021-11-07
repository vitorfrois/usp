/*
    Gabriel Alves Kuabara - Monitor ICC II 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <math.h>

/*
    Atentem-se que essas funções servem para auxiliar vocês,
    não é necessário o uso delas, e vocês podem atera-lás
*/
unsigned char* read_wav_data(char* fname) {
    FILE* fp = open_file(fname, "rb");
    unsigned char buf4[4];

    fseek(fp, 40, SEEK_SET);
    fread(buf4, sizeof(buf4), 1, fp);
    int dataSize = buf4[0] | buf4[1]<<8 | buf4[2]<<16 | buf4[3]<<24;

    unsigned char* data = malloc(sizeof(*data) * (dataSize));
    
    int i = 0;
    while (i < dataSize) {
        fread(&data[i++], sizeof(unsigned char), 1, fp);
    }
    fclose(fp);
    return data;
}

/*
    Discrete Fourier Transform
    Para os curiosos, atentem-se a complexidade de tempo dela...
    é por esse motivo que os áudios são bem curtos
*/
double complex *DFT(unsigned char *audio, int length) {
    double complex *coef = (double complex *) calloc(length, sizeof(double complex));

    for (int k = 0; k < length; k++) {
        for (int n = 0; n < length; n++) {
            coef[k] += audio[n] * cexp((-2.0 * M_PI * (((k+1) * n * 1.0) / (length * 1.0))) * _Complex_I);
        }
        printf("%.1lf + %.1lfi\n", creal(coef[k]), cimag(coef[k]));
    }
    return coef;
}

