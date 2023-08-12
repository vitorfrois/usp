#include<stdio.h>
int main()
{
    FILE *fp;
    fp = fopen("test.txt", "r+");  //read and write mode
    char ch;
    while((ch=getc(fp))!=EOF)
        putchar(ch);
    rewind(fp); //rewind () function moves file pointer position to the beginning of the file.
    fprintf(fp, "penis \n");
    fclose(fp);
    return 0;
}