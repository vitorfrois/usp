#include <stdio.h>
#include <stdlib.h>

int main(){

      FILE* fp;
      fp = fopen("jitBrainfuck.c", "w");

      fprintf(fp, "#include <stdio.h>\n");
      fprintf(fp, "int main() {\n");
      fprintf(fp, "\tchar mem[30000];\n");
      fprintf(fp, "\tint i = 0;\n");
      fprintf(fp, "\tfor (int j = 0; j < 30000; j++) {\n");
      fprintf(fp, "\t\tmem[j] = 0;\n");
      fprintf(fp, "\t}\n\n\t");

      char character;
      int nTabs = 1;
      while((character = getchar()) != EOF){

            switch (character) {
                  case '+':
                        fprintf(fp, "mem[i]++;\n");
                        break;
                  case '-':
                        fprintf(fp, "mem[i]--;\n");
                        break;
                  case '>':
                        fprintf(fp, "i++;\n");
                        break;
                  case '<':
                        fprintf(fp, "i--;\n");
                        break;
                  case '.':
                        fprintf(fp, "putchar(mem[i]);\n");
                        break;
                  case '[':
                        fprintf(fp, "while(mem[i]) {\n");
                        nTabs++;
                        break;
                  case ']':
                        nTabs--;
                        fprintf(fp, "}\n");
                        break;
            }
            for(int i = 0; i < nTabs; i++)
                  fprintf(fp, "\t");
      }

      fprintf(fp, "\n\tprintf(\"\\n\");\n");
      fprintf(fp, "\tfor (int j = 0; j < 30000; j++) {\n");
      fprintf(fp, "\t\tif (mem[j] != 0) {\n");
      fprintf(fp, "\t\t\tprintf(\"%%d \", mem[j]);\n");
      fprintf(fp, "\t\t}\n");
      fprintf(fp, "\t}\n");
      fprintf(fp, "\tprintf(\"\\n\");\n");
      fprintf(fp, "\treturn 0;\n");
      fprintf(fp, "}");

      fclose(fp);
      system("gcc jitBrainfuck.c -o jitExecutavel");
      system("./jitExecutavel");
      return 0;
}
