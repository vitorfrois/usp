#include <stdio.h>

int main(){

    char char_mensagem;
    int quantidade_linhas = 0;
    int quantidade_palavras = 0;
    int quantidade_caracteres = 0;
    char ultimo_caractere;

    while((char_mensagem = getchar()) != EOF){
        quantidade_caracteres++;
        if(char_mensagem == '\n'){
            if(ultimo_caractere == '\r'){
                quantidade_linhas--;
                quantidade_palavras--;
            }
            quantidade_linhas++;
            quantidade_palavras++;
      }else if((char_mensagem == '\r')){
            quantidade_linhas++;
            quantidade_palavras++;
      }else if((char_mensagem == ' ' || char_mensagem == '\t')){
            quantidade_palavras++;
      }
      else{

      }

        ultimo_caractere = char_mensagem;
    }

    printf("Linhas\tPalav.\tCarac.\n");
    printf("%d\t%d\t%d", quantidade_linhas, quantidade_palavras, quantidade_caracteres);
    printf("\n");

    return 0;
}
