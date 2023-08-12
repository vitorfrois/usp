#ifndef PERSON_H
#define PERSON_H

#include <stdio.h>

typedef struct PERSON{
    int firstName;
    int lastName;
    int email;
    int nationality;
    int age;
}Person;

Person initializePerson();
void printFeature(FILE *fp, char * featureName, int featureSize);
void printPerson(FILE *fp);
void inputFeature(FILE *fp, int featureSize);
void inputPerson(FILE *fp);
int numRecordsCalculator(FILE *fp);

#endif