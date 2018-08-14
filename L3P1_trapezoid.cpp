#include<stdio.h>
#include<string.h>
#include "mpi.h"

float f(int x){
return (float)x*x;
}

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
dest = 0;
int a;
MPI_Recv(&a,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
int n;
MPI_Recv(&n,1,MPI_INT,0,2,MPI_COMM_WORLD,&status);


float ans = (0.5)*(n)*(f(a+n-1) + f(a));

MPI_Send(&ans,1,MPI_FLOAT,dest,3,MPI_COMM_WORLD);
}else{

int a =0, b = 4;

int  n = (b-a)/p;  //height for each trapezoid
float ans = (0.5)*(n)*(f(a+n-1) + f(a));
printf("The first computation is %f\n", ans);
a = a+n;
for(int d = 1; d<p; d++){
MPI_Send(&a,1,MPI_INT,d,1,MPI_COMM_WORLD);
MPI_Send(&n,1,MPI_INT,d,2,MPI_COMM_WORLD);
a += n;
}
float r;
for(source=1;source<p;source++){

MPI_Recv(&r,1,MPI_FLOAT,source,3,MPI_COMM_WORLD,&status);
printf("slave process's output is %f\n",r);
ans += r;
}

printf("Final area is :%f \n",ans);
}


MPI_Finalize();

}
