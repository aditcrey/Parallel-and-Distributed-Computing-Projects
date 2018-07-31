#include<stdio.h>
#include<string.h>
#include "mpi.h"

main(int argc, char* argv[]){

int my_rank;
int p;
int source;
int dest;
int tag = 0;
char message[100];
MPI_Status status; //whats the status of what you communicated

MPI_Init(&argc,&argv); //Initialise the MPI
//mpi sets the program from here to end to slave processes

MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);//comp rank: its a communicator...if two process have common commu
//nicator only then two processes can communicate
MPI_Comm_size(MPI_COMM_WORLD,&p); //comm size: size of the data you wanna send
if(my_rank!=0){ //!0 means slave processes only
sprintf(message,"Greeting from process%d!",my_rank);
dest = 0;
MPI_Send(message,strlen(message)+1,MPI_CHAR,dest,tag,MPI_COMM_WORLD); //sending message...tag: differentiate multiple messages sent from single process...mpi_comm_world is communicator
}else{ //else is for master process

for(source=1;source<p;source++){

MPI_Recv(message,100,MPI_CHAR,source,tag,MPI_COMM_WORLD,&status);
printf("%s\n",message);
}
}

MPI_Finalize();//finalise //release all the memory

}
