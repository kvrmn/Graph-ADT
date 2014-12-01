//Kavya Rammohan - krammoha
//Graph.c


#include <stdlib.h>
#include "Graph.h"
#define white 1
#define gray 0
#define black -1

//Create GraphObj
struct GraphObj {
	List *nbrs;
  	int *color;
  	int *parent;
  	int *distance;
  	int order;
  	int size;
 	int source; 
};

//Makes a new Graph with n vertices
Graph newGraph(int n){ 
	Graph G = malloc(sizeof(struct GraphObj)); 
	G->nbrs = calloc (n + 1, sizeof(List)); 
	G->color = calloc(n + 1, sizeof(int)); 
	G->distance = calloc(n + 1, sizeof(int)); 
	G->parent = calloc(n + 1, sizeof(int));
	G->source = NIL;
	G->order = n;
  	G->size = 0;
  	for (int i = 0; i < n + 1; i++){
    	   G->nbrs[i] = newList();
    	   G->color[i] = white;
    	   G->parent[i] = NIL;
    	   G->distance[i] = INF; // chagne to 0?
  	}
  	return G;
} 
 
//Function to free allocated Graph
void freeGraph(Graph* pG){
  	Graph G = *pG; 
  	for(int i=0;i<(G->order)+1;i++){
    	   freeList(&(G->nbrs[i]));
  	}
  	free(G->nbrs); 
  	free(G->color); 
  	free(G->distance); 
  	free(G->parent); 
  	free(*pG);
  	*pG = NULL; 
} 

//Define function used later in code
static void addVertex(List L, int x);

//Get number of vertices
int getOrder(Graph G){
 	return G->order;
}

//Get number of edges
int getSize(Graph G){
  	return G->size;
}
//Get source node
//Pre: 1<=u<getOrder(G)
int getSource(Graph G){
  	return G->source;
}
//Get parent node
//Pre: 1<=u<getOrder(G)
int getParent(Graph G, int u){
  	if(u>getOrder(G) || u<1){
    	   return 0;
  	}
  	return G->parent[u];
}

//Get distance from source to vertex u
//Pre: 1<=u<getSource(G)
int getDist(Graph G, int u){
  	if(getSource(G) == NIL){
    	   return INF;
  	} 
  	if(u<1 || u>getOrder(G)){
    	   return 0;
  	}
  	return G->distance[u];
} 
//Get the shortest path from source to vertex
//Pre: getSource(G)!=NIL && 1<=u<getOrder(G)
void getPath(List L, Graph G, int u){
  	if(getSource(G) == NIL){
 	   return;
	} 
  	if(u<1 || u>getOrder(G)){
    	   return;
  	}
  	if (u == G->source){
    	   prepend(L, G->source);
    	   return;
  	}
	else if(G->parent[u]==NIL){
    	   append(L, NIL);
  	} 
	else{
    	   prepend(L,u);
    	   getPath(L, G, G->parent[u]);
  	}
} 

//Nulls graph G
void makeNull(Graph G){
  	int i;
  	for(i=0; i<(G->order+1);i++){
    	   clear(G->nbrs[i]);
  	} 
}

//Adds edge in between two vertices 
void addEdge(Graph G, int u, int v){
  	if(u<1 || u>getOrder(G)){
    	   return;
  	}
	if(v<1 || v>getOrder(G)){
	   return;
	}
  	List A = G->nbrs[u];
  	List B = G->nbrs[v];
  	addVertex(B,u);
  	addVertex(A,v);
}

//Adds a directed edge
void addArc(Graph G, int u, int v){
  	if(u<1 || u>getOrder(G)){
	   return; 
	}
	if(v<1 || v>getOrder(G)){
    	   return;
  	}
  	List L = G->nbrs[u];
  	addVertex(L, v);
}
 
//Function that carries out Breadth-First Search
void BFS(Graph G, int s){
	int i;
  	for(i=0;i<(1+G->order);i++){
    	   if(i!=s){
      	      G->color[i] = white;
      	      G->distance[i] = INF;
      	      G->parent[i] = NIL;
    	   }
  	}
  	G->source = s;
  	G->color[s] = gray;
  	G->distance[s] = 0;
  	G->parent[s] = NIL;
  	List A = newList();
  	prepend(A, s);
	
	int j;
  	while(length(A)!=0){
    	   j = back(A);
    	   deleteBack(A);
    	   List B = G->nbrs[j];
    	   for(moveTo(B, 0);getIndex(B)>=0;moveNext(B)){
      		int k = getElement(B);
      		if(G->color[k] == white){
		   G->color[k] = gray;
		   G->distance[k] = 1+G->distance[j];
		   G->parent[k] = j;
		   prepend(A,k);
      		}
    	   }
    	   G->color[j] = black;
  	}
  	freeList(&A);
} 

//Print graph to FILE*out
void printGraph(FILE* out, Graph G){
  if(out == NULL || G == NULL){
    return;
  }
  for (int x=1; x<getOrder(G)+1; x++){
    fprintf(out, "%d: ", x);
    printList(out, G->nbrs[x]);
    fprintf(out, "\n");
  }
}

//Add a vertex x into List L
static void addVertex(List L, int x){
        if(length(L)==0){
           append(L,x);
           return;
        }
        for(moveTo(L, 0);getIndex(L)>=0;moveNext(L)){
           int y = getElement(L);
           if(x<y){
              insertBefore(L,x);
              break;
           }
        }
        if(getIndex(L) == -1){
           append(L,x);
        }
}
