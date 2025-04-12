#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
  int i, world_rank, world_size, *nums;
  float local_sum = 0, global_sum;

  MPI_Init(NULL, NULL);

  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  nums=(int*)malloc(world_size*(sizeof(int)));

  for (i = 0; i < world_size; i++) {
    nums[i]=i*world_rank;
    local_sum += nums[i];
  }
  printf("Local sum for process %d - %f\n",world_rank, local_sum);

  // Reduce all of the local sums into the global sum
  MPI_Scan(&local_sum, &global_sum, 1, MPI_FLOAT, MPI_SUM,MPI_COMM_WORLD);


  // Clean up
  free(nums);

  MPI_Barrier(MPI_COMM_WORLD);

  // Print the results
  printf("Process %d has Local sum = %f, Global sum = %f\n", world_rank, local_sum, global_sum);
  MPI_Finalize();
}
