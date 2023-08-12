#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum commandType {
      add = 1, show, next, previous, exportPlaylist, importPlaylist, exitPlaylist
}command;

typedef struct {
      char* name;
      char* artist;
      int lenght;
} playlistMusic;

typedef struct {
      playlistMusic* music;
      int nMusic;
      int currentMusic;
      char* playlistName;
      char* fileName;
} playlist;

char* readString(){
      char *string = malloc(sizeof(char));
      char character = ' ';
      int nCharsString = 0;
      do {
            character = getchar();
            string = realloc(string, (nCharsString + 1) * sizeof(char*));
            string[nCharsString] = character;
            nCharsString++;
      } while(character != '\n');
      string[nCharsString - 1] = '\0';
      return string;
}

void addFunction(playlist* library){
      if(library->nMusic > 14){
            printf("Playlist cheia!\n");
      }else{
            library->nMusic++;
            library->music = realloc(library->music, sizeof(playlistMusic) * library-> nMusic);
            library->music[library->nMusic - 1].name = readString();
            library->music[library->nMusic - 1].artist = readString();
            scanf(" %d", &library->music[library->nMusic - 1].lenght);
            printf("Musica %s de %s adicionada com sucesso.\n",
                  library->music[library->nMusic - 1].name,
                  library->music[library->nMusic - 1].artist
            );
      }
}

void showFunction(playlist* library){
      printf("---- Playlist: %s ----\n", library->playlistName);
      printf("Total de musicas: %d\n\n", library->nMusic);
      for(int i = 0; i < library->nMusic; i++){
            if(i == library->currentMusic)
                  printf("=== NOW PLAYING ===\n");
            printf("(%d). '%s'\n", i + 1, library->music[i].name);
            printf("Artista: %s\n", library->music[i].artist);
            printf("Duracao: %d segundos\n\n", library->music[i].lenght);
      }
}

void binaryToNum(char* binFilename) {
    FILE *fp = fopen(binFilename, "rb");
    double binValue = 0;
    double accumulator = 0.01;
    char ch;
    while (fread(&ch, sizeof(char), 1, fp)) {
        binValue += (double) ch * accumulator;
        accumulator += 0.01;
    }
    fclose(fp);
    printf("%lf\n", binValue);
}

void freeFunction(playlist* library){
      free(library->playlistName);
      for (int i = 0; i < library->nMusic; i++){
            free(library->music[i].name);
            free(library->music[i].artist);
      }
      free(library->music);
}

char* binaryReadFunction(FILE* playlistFile){
      int sizeOfChar;
      fread(&sizeOfChar, 4, 1, playlistFile);
      char* adress = malloc(sizeof(char) * (sizeOfChar+1));
      fread(adress, sizeof(char), sizeOfChar, playlistFile);
      adress[sizeOfChar] = '\0';
      return adress;
}

void binaryWriteFunction(char* adress, FILE* playlistFile){
      int sizeOfChar = strlen(adress);
      fwrite(&sizeOfChar, sizeof(int), 1, playlistFile);
      fwrite(adress, sizeof(char), sizeOfChar, playlistFile);
}

void exportFunction(playlist* library){
      library->fileName = readString();
      FILE* playlistFile = fopen(library->fileName, "wb");
      binaryWriteFunction(library->playlistName, playlistFile);
      fwrite(&(library->nMusic), sizeof(int), 1, playlistFile);
      for(int i = 0; i < library->nMusic; i++){
            binaryWriteFunction(library->music[i].name, playlistFile);
            binaryWriteFunction(library->music[i].artist, playlistFile);
            fwrite(&(library->music[i].lenght), sizeof(int), 1, playlistFile);
      }
      fclose(playlistFile);
      printf("Playlist %s salva com sucesso. \n", library->fileName);
      binaryToNum(library->fileName);
      free(library->fileName);
}

void importFunction(playlist* library){
      library->fileName = readString();
      FILE *playlistFile = fopen(library->fileName, "rb");
      if (playlistFile == NULL){
            printf("Arquivo %s nao existe. \n", library->fileName);
            exit(1);
      }
      freeFunction(library);
      library->playlistName = binaryReadFunction(playlistFile);
      fread(&(library->nMusic), 4, 1, playlistFile);
      library->music = malloc(sizeof(playlistMusic) * library-> nMusic);
      for(int i = 0; i < library->nMusic; i++){
            library->music[i].name = binaryReadFunction(playlistFile);
            library->music[i].artist = binaryReadFunction(playlistFile);
            fread(&library->music[i].lenght, 4, 1, playlistFile);
      }
      printf("Playlist %s carregada com sucesso. \n", library->fileName);
      binaryToNum(library->fileName);
      fclose(playlistFile);
      free(library->fileName);
}

int main(){
      playlist* library = malloc(sizeof(playlist));  //realloc(2*playlist) > library[2]
      library->playlistName = readString();
      library->music = malloc(sizeof(playlistMusic));
      library->nMusic = 0;
      library->currentMusic = 0;
      int command;
      char aux;
      scanf("%d%c", &command, &aux);
      while(command != exitPlaylist){
            if(command == add){
                  addFunction(library);
            }else if(command == show){
                  showFunction(library);
            }else if(command == next){
                  library->currentMusic++;
            }else if(command == previous){
                  library->currentMusic--;
            }else if(command == exportPlaylist){
                  exportFunction(library);
            }else if(command == importPlaylist){
                  importFunction(library);
            }
            scanf("%d%c", &command, &aux);
      }
      freeFunction(library);
      free(library);
      return 0;
}
