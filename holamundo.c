#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
 
int main(int argc, char *argv[])
{
  char mensajem[20];
  char mensajes[20];
  int numprocs;
  int myid;
  MPI_Status stat; 
 
  MPI_Init(&argc,&argv); 
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs); 
  MPI_Comm_rank(MPI_COMM_WORLD,&myid); 
 
  if(myid == 0)
  {

    printf("\nTenemos %d procesadores, soy el proceso %d\n", numprocs,myid);

    for(int i=1;i<numprocs;i++)
    {
      sprintf(mensajem, "mensaje del maestro");
      MPI_Send(mensajem, 20, MPI_CHAR, i, 0, MPI_COMM_WORLD);
    }
    sleep(1);
    for(int j=1;j<numprocs;j++)
    {
      MPI_Recv(mensajes, 20, MPI_CHAR, j, 0, MPI_COMM_WORLD, &stat);
      printf("\n %s \n", mensajes);
    }
  }
  else
  {
    MPI_Recv(mensajem, 20, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &stat);
    printf("\n %s \n", mensajem);
     sprintf(mensajes, "proceso esclavo %d",myid);
    MPI_Send(mensajes, 20, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
  }
 
  MPI_Finalize();
  return 0;
}
