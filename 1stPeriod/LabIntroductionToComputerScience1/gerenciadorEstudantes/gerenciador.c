#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
      unsigned int id;
      char* name;
      char* course;
      unsigned int age;
}student;

typedef struct{
      student* students;
      unsigned int nStudents;
}studentList;

studentList readStudentStruct(studentList);
void listPrinter(studentList, int);
char* readString();

int main(){
      studentList studentsInfo;
      studentsInfo.students = malloc(sizeof(studentList));
      studentsInfo = readStudentStruct(studentsInfo);
      int option;
      char aux;
      scanf("%d%c", &option, &aux);
      while(option != -1){
            if(option == 1){
                  int searchingID;
                  scanf("%d\n", &searchingID);
                  for(int i = 0; i < studentsInfo.nStudents; i++){
                        if(studentsInfo.students[i].id == searchingID){
                              listPrinter(studentsInfo, i);
                        }
                  }
            }else if(option == 2){
                  char* searchingCourse = readString();
                  for(int i = 0; i < studentsInfo.nStudents; i++){
                        if(strcmp(studentsInfo.students[i].course, searchingCourse) == 0){
                              listPrinter(studentsInfo, i);
                        }
                  }
            }else if(option == 3){
                  for(int i = 0; i < studentsInfo.nStudents; i++){
                        listPrinter(studentsInfo, i);
                  }
            }
            scanf("%d%c", &option, &aux);
      }
      return 0;
}

studentList readStudentStruct(studentList studentsInfo){
      int input;
      char aux;
      studentsInfo.nStudents = 0;
      scanf("%d%c", &input, &aux);
      studentsInfo.students = malloc(sizeof(student));
      while(input != -1){
            studentsInfo.students[studentsInfo.nStudents].id = input;
            studentsInfo.students[studentsInfo.nStudents].name = readString();
            studentsInfo.students[studentsInfo.nStudents].course = readString();
            scanf("%d\n", &input);
            studentsInfo.students[studentsInfo.nStudents].age = input;
            studentsInfo.nStudents++;
            studentsInfo.students = realloc(studentsInfo.students, sizeof(student) * (studentsInfo.nStudents+1));
            scanf("%d%c", &input, &aux);
      }
      return studentsInfo;
}

void listPrinter(studentList studentsInfo, int i){
      printf("Nome: %s\n", studentsInfo.students[i].name);
      printf("Curso: %s\n", studentsInfo.students[i].course);
      printf("N USP: %d\n", studentsInfo.students[i].id);
      printf("IDADE: %d\n\n", studentsInfo.students[i].age);
}

char* readString(){
      char *string = malloc(sizeof(char));
      char character = ' ';
      int nCharsString = 0;
      do {
            character = getchar();
            string = realloc(string, (nCharsString + 1) * sizeof(char));
            string[nCharsString] = character;
            nCharsString++;
      } while(character != '\n');
      string[nCharsString - 1] = '\0';
      return string;
}
