#include <stdio.h>
#include <time.h> //necessário para usar localtime() e struct tm
int main(void)
{
  //ponteiro para struct que armazena data e hora
  struct tm *data_hora_atual;

  //variável do tipo time_t para armazenar o tempo em segundos
  time_t segundos;

  //obtendo o tempo em segundos
  time(&segundos);

  //para converter de segundos para o tempo local
  //utilizamos a função localtime
  data_hora_atual = localtime(&segundos);

  //para acessar os membros de uma struct usando o ponteiro
  //utilizamos o operador -> no nosso caso temos:
  //data_hora_atual->membro_da_struct

  //Acessando dados convertidos para a struct data_hora_atual
  printf("\nDia..........: %d\n", data_hora_atual->tm_mday);
  printf("\nMes..........: %d\n", data_hora_atual->tm_mon+1);
  printf("\nAno..........: %d\n\n", data_hora_atual->tm_year+1900);
  printf("\nDia do ano...: %d\n", data_hora_atual->tm_yday);
  printf("\nDia da semana: %d\n\n", data_hora_atual->tm_wday);
  return 0;
}
