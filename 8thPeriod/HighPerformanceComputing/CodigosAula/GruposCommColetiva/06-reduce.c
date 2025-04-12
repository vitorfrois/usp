#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <assert.h>
#include <time.h>

// Creates an array of random numbers. Each number has a value from 0 - 1
float *create_rand_nums(int num_elements) {
  int i;
  float *rand_nums = (float *)malloc(sizeof(float) * num_elements);

  assert(rand_nums != NULL); // interrompe exec do programa se assert for falsa. Se for verdadeira, continua.

  for (i = 0; i < num_elements; i++) {
    rand_nums[i] = (rand() / (float)RAND_MAX);
  }

  return rand_nums;
}

int main(int argc, char** argv) 
{
  int num_elements_per_proc, root = 0;
  int i, world_rank, world_size;

  float local_sum = 0, *rand_nums = NULL, global_sum;
  
  
  if (argc != 2) 
  {
    printf("Usage: <exec-file-name> <num_elements_per_proc>\n");
    exit(1);
  }
  num_elements_per_proc = atoi(argv[1]);

  MPI_Init(NULL, NULL);

  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Create a random array of elements on all processes.
  srand(time(NULL)*world_rank);   // Seed the random number generator to get different results each time for each processor
  rand_nums = create_rand_nums(num_elements_per_proc);

  // Sum the numbers locally
  for (i = 0; i < num_elements_per_proc; i++) 
  {
    local_sum += rand_nums[i];
  }

  // Print the random numbers on each process
  printf("Local sum for process %d - %f, avg = %f\n",
         world_rank, local_sum, local_sum / num_elements_per_proc);

  // Reduce all of the local sums into the global sum
  MPI_Reduce(&local_sum, &global_sum, 1, MPI_FLOAT, MPI_SUM, root, MPI_COMM_WORLD);

  // Print the result
  if (world_rank == root) {
    printf("Total sum = %f, avg = %f\n", global_sum,
           global_sum / (world_size * num_elements_per_proc));
  }

  // Clean up
  free(rand_nums);

  //MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
}
