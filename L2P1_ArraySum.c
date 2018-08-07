#include<stdio.h>
#include<string.h>
#include "mpi.h"

main(int argc, char* argv[]){

int my_rank;
int p;
int source;
int dest;
int tag = 0;
MPI_Status status; //whats the status of what you communicated
int a,b;


MPI_Init(&argc,&argv); //Initialise the MPI
//mpi sets the program from here to end to slave processes

MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
MPI_Comm_size(MPI_COMM_WORLD,&p);


int n;

if(my_rank!=0){
//sprintf(message,"Greeting from process%d!",my_rank);

dest = 0;
n = my_rank;
int sz;
MPI_Recv(&sz,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
int a[sz];
MPI_Recv(a,sz,MPI_INT,0,2,MPI_COMM_WORLD,&status);
int sm=0;
for(int k=0;k<sz;k++){
	sm+= a[k];
}

MPI_Send(&sm,1,MPI_INT,dest,tag,MPI_COMM_WORLD);
}else{

int arr[] = {10,20,30,40,50,60,70,80,90,100};
int sz = 10/p;
int start;
for(int d = 1;d<p;d++){
	start = d*2;
	MPI_Send(&sz,1,MPI_INT,d,1,MPI_COMM_WORLD);
	MPI_Send((arr+start),sz,MPI_INT,d,2,MPI_COMM_WORLD);
}
int sm = arr[0] + arr[1];
int z;
for(source=1;source<p;source++){
MPI_Recv(&z,1,MPI_INT,source,tag,MPI_COMM_WORLD,&status);
sm+=z;
printf("slave process no %d's output is %d\n",source,z);
}
printf("The final sum is : %d\n",sm);
}



//comp rank: its a communicator...if two process have common commu
//nicator then two processes can communicate

//comm size: size of the data you wanna send

//!0 means slave processes only


//sending message...tag: differentiate multiple messages sent from single process...mpi_comm_world is communicator

//else is for master process


MPI_Finalize();
}
