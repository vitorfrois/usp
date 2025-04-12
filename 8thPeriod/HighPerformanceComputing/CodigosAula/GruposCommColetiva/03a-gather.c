#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define TAM 16

int main(int argc, char **argv) {
  int rank, size, rec_size, i, *vetor_env, *vetor_rec, root = 0;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  rec_size = TAM / size;
  vetor_env = (int *)malloc(rec_size * sizeof(int));

  // vetor_rec so e necessario no processo root
  if (rank == root)
    vetor_rec = (int *)malloc(TAM * sizeof(int));

  // Atribuindo dados ao vetor de envio.
  // Todos os processos que rodam este programa
  // executam este for.
  for (i = 0; i < rec_size; i++) {
    vetor_env[i] = (rank * rec_size) + i;
  }

  // Todos os processos que pertencem ao MPI_COMM_WORLD
  // executam o MPI_Gather.
  MPI_Gather(
    vetor_env, 
    rec_size, 
    MPI_INT, 
    vetor_rec, 
    rec_size, 
    MPI_INT, 
    root,
    MPI_COMM_WORLD
  );

  printf("Eu sou o processo de rank %d\n", rank);

  if (rank == root) {
    for (i = 0; i < TAM; i++) {
      printf("recebeu %d\n", vetor_rec[i]);
    }
    free(vetor_rec);
  }

  free(vetor_env);
  MPI_Finalize();
}
