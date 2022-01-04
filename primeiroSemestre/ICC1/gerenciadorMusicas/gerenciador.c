#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum commandType {
      add = 1, show, next, previous, exitPlaylist
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
} playlist;

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
                  library->currentMusic > library->nMusic?
                        library->currentMusic = 0:
                        library->currentMusic;
            }else if(command == previous){
                  library->currentMusic--;
                  library->currentMusic < 0?
                        library->currentMusic = library->nMusic:
                        library->currentMusic;
            }

            scanf("%d%c", &command, &aux);
      }


      free(library->playlistName);
      for (int i = 0; i < library->nMusic; i++){
            free(library->music[i].name);
            free(library->music[i].artist);
      }
      free(library->music);
      free(library);
      return 0;
}
