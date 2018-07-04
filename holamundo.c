#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
 
int main(int argc, char *argv[])
{
  char idstr[32];
  char buff[128];
  char hostname[128];
  int numprocs;
  int myid;
  MPI_Status stat; 
 
  MPI_Init(&argc,&argv); 
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs); 
  MPI_Comm_rank(MPI_COMM_WORLD,&myid); 
 
  if(myid == 0)
  {
    printf("\nTenemos %d procesadores\n", numprocs);
    for(int i=1;i<numprocs;i++)
    {
      sprintf(buff, "Hola proceso %d! ", i);
      MPI_Send(buff, 128, MPI_CHAR, i, 0, MPI_COMM_WORLD);
    }
	sleep(1);
    for(int j=1;j<numprocs;j++)
    {
      MPI_Recv(buff, 128, MPI_CHAR, j, 0, MPI_COMM_WORLD, &stat);
      printf("%s\n", buff);
    }
  }
  else
  {
    MPI_Recv(buff, 128, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &stat);
    gethostname(hostname,128);
    sprintf(idstr, "\nProcesador %d en %s  ", myid, hostname);
    strcat(buff, idstr);
    strcat(buff, "reportandose\n");
    MPI_Send(buff, 128, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
  }
 
  MPI_Finalize();
  return 0;
}
