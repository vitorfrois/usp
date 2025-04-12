/*
 ============================================================================
 Author        : G. Barlas
 Version       : 1.0
 Last modified : December 2014
 License       : Released under the GNU GPL 3.0
 Description   : 
 To build use  : mpicc broadcast2.c -o broadcast2
 ============================================================================
 */
#include <mpi.h>
#include <stdio.h>

//*****************************************

int main(int argc, char **argv) 
{

    int rank, num, root = 0;
	double data;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num);

   
    if (rank == 0) 
    {
        data = 3.14159265358979323846;
        MPI_Bcast(&data, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    } 
    else {

        printf("Before ==> Node #%i, data %lf\n", rank, data);

        MPI_Bcast(&data, 1, MPI_DOUBLE, root, MPI_COMM_WORLD);

        printf("After ==> Node #%i, data %lf\n", rank, data);
       
   }
        
    MPI_Finalize();
    return 0;
}
