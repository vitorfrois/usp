#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../includes/person.h"
#include "../includes/myString.h"

#define SKIPSIZE 238
typedef struct PERSON Person;

Person initalizePerson(){
    Person size;
    size.firstName = 51;
    size.lastName = 51;
    size.email = 81;
    size.nationality = 51;
    size.age = 4;
    return size;
}

void printFeature(FILE *fp, char * featureName, int featureSize){
    char feature[featureSize];
    fread(&feature, 1, featureSize, fp);
    printf("%s%s\n", featureName, feature);
}

void printPerson(FILE *fp){
    Person size = initalizePerson();
    printFeature(fp, "Firstname: ", size.firstName);
    printFeature(fp, "Lastname: ", size.lastName);
    printFeature(fp, "Email: ", size.email);
    printFeature(fp, "Nationality: ", size.nationality);
    int age;
    fread(&age, 1, 4, fp);
    printf("Age: %d\n\n", age);
}

void inputFeature(FILE *fp, int featureSize){
    readFixedSizeString(fp, featureSize); 
}

void inputPerson(FILE *fp){
    Person size = initalizePerson();
    getchar(); 
    
    inputFeature(fp, size.firstName);
    inputFeature(fp, size.lastName);
    inputFeature(fp, size.email);
    inputFeature(fp, size.nationality);
    // inputFeature(fp, size.age);
    int age;
    scanf("%d", &age);
    fwrite(&age, 1, sizeof(int), fp);
}

int numRecordsCalculator(FILE *fp){
    fseek(fp, 0, SEEK_END); //go to the eof
    long int fileSize = ftell(fp); //computate n of bytes of the file
    fseek(fp, 0, SEEK_SET); //return to the begin
    return fileSize/SKIPSIZE;
}
