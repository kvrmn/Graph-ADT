//Kavya Rammohan - krammoha
//FindPath.c
//Uses Graph ADT to find shortest paths between pairs
//:of vertices in given input file, then stores results in output file.


#include <stdlib.h>
#include<stdio.h>
#include "Graph.h"
#include<string.h>
#define MAX_LEN 256

int main(int argc, char* argv[]){
//Define variables
        int number = 0;
        List A;
        int t;
        char tokenlist[MAX_LEN];

//Check if argument number is correct
        if(argc!=3){
           printf("Correct usage: FindPath input_file output_file\n");
           exit(1);
        }

//Open files for reading and writing
        FILE* in = fopen(argv[1], "r");
        FILE* out = fopen(argv[2], "w");

//Read in number of vertices from out file
        fgets(tokenlist, MAX_LEN, in);
        sscanf(tokenlist, "%d", &number);

//Create new graph using vertices from file
        Graph C = newGraph(number);
        while(fgets(tokenlist,MAX_LEN,in)!=NULL){
           int c = 0;
           int d = 0;
           sscanf(tokenlist, "%d %d", &c,&d);
           if(c==0 && d==0){
                break;
           }
           addEdge(C,c,d);
        }
        printGraph(out,C);
        t=0;
        while(fgets(tokenlist, MAX_LEN, in)!=NULL){
           int a =0;
           int b = 0;
           sscanf(tokenlist,"%d %d", &a,&b);
           t++;
           if(a==0 && b==0){
                break;
           }
           if(t!=1){
                fprintf(out,"\n");
           }
//Use BFS and getDist() to print out proper distance between vertices

           BFS(C,a);
           int d = getDist(C,b);
           fprintf(out, "\nThe distance from %d to %d is ", a,b);
           if(d==-255){
                fprintf(out,"infinity.");
                fprintf(out,"\n");
           }
           else{
                fprintf(out,"%d",d);
                fprintf(out,"\n");
           }
           //Use getPath() to print out proper shortest path between vertices
           A=newList();
           getPath(A,C,b);
           if(front(A)==-254){
                fprintf(out,"No %d - %d path exists.",a,b);
           }
           else{
                fprintf(out,"A shortest %d - %d path is: ",a,b);
                printList(out,A);
           }
           freeList(&A);
        }
//Free memory and close files
        freeGraph(&C);
        fclose(in);
        fclose(out);

//End program
        return(0);
}
