#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum option{
      exitPokedex,
      newPokemon,
      newAttack,
      printPokemon,
      printAttack
};

typedef struct{
      int hp;
      int atk;
      int def;
      int specialAtk;
      int specialDef;
      int velocity;
}stats;

typedef struct{
      char* attackName;
      int power;
      float accuracy;
      char class;
} attacks;

typedef struct{
      char* name;
      char* primaryType;
      char* secondaryType;
      stats atributes;
      attacks attack[4];
} pokemon;

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

void newPokemonFunction(pokemon* pokedex, int i){
      pokedex[i].name = readString();
      pokedex[i].primaryType = readString();
      pokedex[i].secondaryType = readString();
      scanf("%d\n", &(pokedex[i].atributes.hp));
      scanf("%d\n", &(pokedex[i].atributes.atk));
      scanf("%d\n", &(pokedex[i].atributes.def));
      scanf("%d\n", &(pokedex[i].atributes.specialAtk));
      scanf("%d\n", &(pokedex[i].atributes.specialDef));
      scanf("%d\n", &(pokedex[i].atributes.velocity));
}

void newAttackFunction(pokemon* pokedex){
      int i, attackIndex;
      scanf("%d\n", &i);
      scanf("%d\n", &attackIndex);
      pokedex[i].attack[attackIndex].attackName = readString();
      scanf("%d\n", &(pokedex[i].attack[attackIndex].power));
      scanf("%f\n", &(pokedex[i].attack[attackIndex].accuracy));
      scanf("%c\n", &(pokedex[i].attack[attackIndex].class));
}

void printPokemonFunction(pokemon* pokedex){
      int pokemonIndex;
      scanf("%d\n", &pokemonIndex);
      printf("Nome do Pokemon: %s\n", (pokedex[pokemonIndex].name));
      printf("Tipo primario: %s\n", (pokedex[pokemonIndex].primaryType));
      printf("Tipo secundario: %s\n", (pokedex[pokemonIndex].secondaryType));
      printf("Status:\n");
      printf("\tHP: %d\n", (pokedex[pokemonIndex].atributes.hp));
      printf("\tAtaque: %d\n", (pokedex[pokemonIndex].atributes.atk));
      printf("\tDefesa: %d\n", (pokedex[pokemonIndex].atributes.def));
      printf("\tAtaque Especial: %d\n", (pokedex[pokemonIndex].atributes.specialAtk));
      printf("\tDefesa Especial: %d\n", (pokedex[pokemonIndex].atributes.specialDef));
      printf("\tVelocidade: %d\n\n", (pokedex[pokemonIndex].atributes.velocity));
}

void printAttackFunction(pokemon* pokedex){
      int pokemonIndex, attackIndex;
      scanf("%d\n", &pokemonIndex);
      scanf("%d\n", &attackIndex);
      printf("Nome do Ataque: %s\n", pokedex[pokemonIndex].attack[attackIndex].attackName);
      printf("Poder base: %d\n", pokedex[pokemonIndex].attack[attackIndex].power);
      printf("Acuracia: %f\n", pokedex[pokemonIndex].attack[attackIndex].accuracy);
      printf("Classe: %c\n\n", pokedex[pokemonIndex].attack[attackIndex].class);
}

int main(){
      pokemon* pokedex = malloc(sizeof(pokemon));
      int option, nPokemons = 0;
      char aux;
      scanf("%d%c", &option, &aux);
      while(option != exitPokedex){
            if(option == newPokemon){
                  newPokemonFunction(pokedex, nPokemons);
                  nPokemons++;
            }else if(option == newAttack){
                  newAttackFunction(pokedex);
            }else if(option == printPokemon){
                  printPokemonFunction(pokedex);
            }else if(option == printAttack){
                  printAttackFunction(pokedex);
            }
            scanf("%d%c", &option, &aux);
      }
      free(pokedex);
      return 0;
}
