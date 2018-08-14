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
int a,b;


MPI_Init(&argc,&argv); //Initialise the MPI
//mpi sets the program from here to end to slave processes

MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
MPI_Comm_size(MPI_COMM_WORLD,&p);


int n;

if(my_rank!=0){
//sprintf(message,"Greeting from process%d!",my_rank);

dest = 0;
int sz;
MPI_Recv(&sz,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
int vec1[sz], vec2[sz];
MPI_Recv(vec1,sz,MPI_INT,0,2,MPI_COMM_WORLD,&status);
MPI_Recv(vec2,sz,MPI_INT,0,3,MPI_COMM_WORLD,&status);
int ans[sz];
for(int k=0;k<sz;k++){
        ans[k] =  vec1[k]*vec2[k];
}

//MPI_Send(&sm,1,MPI_INT,dest,4,MPI_COMM_WORLD);
MPI_Send(&ans,sz,MPI_INT,dest,5,MPI_COMM_WORLD);

}else{

int vec1[] = {1,2,3,4,1,2,3,4};
int vec2[] = {5,6,7,8,5,6,7,8};

int vsize = sizeof(vec1)/sizeof(vec1[0]);

for(int i=0;i<vsize;i++) printf("%d ",vec1[i]);
printf("\n");
for(int i=0;i<vsize;i++) printf("%d ",vec2[i]);
printf("\nThe dot product is: \n");

int cosProd[vsize];
int sz = vsize/p; //size to be distributed to each process
int start = 0;
int limit = start + sz;
int ans=0;
int i=0;
for(;start<limit;start++){
cosProd[start] = (vec1[start] * vec2[start]);
}

int d;
for(d = 1;d<p;d++){
        MPI_Send(&sz,1,MPI_INT,d,1,MPI_COMM_WORLD);
        MPI_Send((vec1+start),sz,MPI_INT,d,2,MPI_COMM_WORLD);
                MPI_Send((vec2+start),sz,MPI_INT,d,3,MPI_COMM_WORLD);
                start = start+sz;
}
int r;

int res[sz];
int x = sz;

for(source=1;source<p;source++){
//MPI_Recv(&r,1,MPI_INT,source,4,MPI_COMM_WORLD,&status);
MPI_Recv(&res,sz,MPI_INT,source,5,MPI_COMM_WORLD,&status);
//printf("slave process's output is %d\n",r);

for(int y = 0;y<sz;y++){
cosProd[x] = res[y];
x++;
}
}

for(int p=0;p<vsize;p++){
printf("%d ",cosProd[p]);
}
printf("\n");
}



//comp rank: its a communicator...if two process have common commu
//nicator then two processes can communicate

//comm size: size of the data you wanna send


//!0 means slave processes only


//sending message...tag: differentiate multiple messages sent from single process...mpi_comm_world is communicator

//else is for master process


MPI_Finalize();

}
