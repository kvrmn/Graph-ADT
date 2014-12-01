// Kavya Rammohan - krammoha
// List.c
//
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "List.h"

   // Define class Node
typedef struct NodeObj{
        int data;
        struct NodeObj* next;
        struct NodeObj* prev;
}NodeObj;

typedef NodeObj* Node;

Node newNode(int data){
        Node N = malloc(sizeof(NodeObj));
        assert(N!=NULL);
        N->data = data;
        N->next = NULL;
        N->prev = NULL;
        return(N);
}

void freeNode(Node* pN){
        if( pN!=NULL && *pN!=NULL){
          free(*pN);
          *pN=NULL;
        }
}

   // Define variables
typedef struct ListObj{
        Node front;
        Node back;
        Node cursor;
        int numItems;
        int index;
} ListObj;

   // Creates a new empty list
List newList(void){
        List L = malloc(sizeof(ListObj));
        assert(L!=NULL);
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->index = -1;
        L->numItems = 0;
        return L;
   }

void freeList(List* pL){
        if(pL!=NULL && *pL!=NULL){
          if(length(*pL)!=0) clear(*pL);
          free(*pL);
          *pL=NULL;
        }
}
  // Returns number of elements in this list
  int length(List L){
        return(L->numItems);
  }

  // Returns the index of the cursor element in this list, or returns -1
  // if the cursor element is undefined
  int getIndex(List L){
        return(L->index);
  }

  // Returns front element in this list. Pre: length() > 0
  int front(List L){
        if(L->numItems == 0 ){
          printf("List Error: front() called on empty List\n");
          exit(1);
        } else{
          return L->front->data;
        }
  }

  // Returns back element in this list. Pre: length()>0
  int back(List L){
        if(length(L) == 0){
          printf("List Error: back() called on empty List\n");
        }
          return L->back->data;
  }

  // Returns cursor element in this list. Pre: length()>0, getIndex()>=0
  int getElement(List L){
        if(length(L) == 0){
          printf("List Error: getElement() called on empty List\n");
          exit(1);
        }
        if(getIndex(L) < 0){
          printf("List Error: getElement() called on invalid cursor\n");
          exit(1);
        }
        if(L->numItems >0 && L->index >=0){
        return L->cursor->data;
        }
        return -1;
  }

  // Returns true if this List and L are the same integer sequence. The
  // cursor is ignored in both lists.
  int equals(List A, List B){
        int flag = 1;
        Node N = NULL;
        Node M = NULL;

        if( A==NULL || B==NULL ){
        printf("List Error: calling equals() on NULL List reference\n");
        exit(1);
        }
        N = A->front;
        M = B->front;
        if( A->numItems != B->numItems ) { return 0; }
        while( flag && N!=NULL){
          flag = (N->data==M->data);
          N = N->next;
          M = M->next;
        }
        return flag;
}

  // Manipulation procedures


  // Re-sets this List to the empty state
  void clear(List L){
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->numItems = 0;
  }

  // If 0<=i<=length()-1, moves the cursor to the element at index i,
  // otherwise the cursor becomes undefined
  void moveTo(List L, int i){
        if(L->cursor == NULL){
          L->cursor = L->front;
          L->index = 0;
        }
        if(i>=0 && i<=(length(L)-1)){
          while(i!=L->index && L->index>i){
             L->cursor = L->cursor->prev;
             L->index--;
          }
          while(i!=L->index && L->index<i){
             L->cursor = L->cursor->next;
             L->index++;
          }
        }
   }

   // If 0<getIndex()<=length()-1, moves the cursor one step toward the
   // front of the list. If getIndex()==0, cursor becomes undefined. 
   // If getIndex()==-1, cursor remains undefined. This operation is
   // equivalent to moveTo(getIndex()-1).
   //
   void movePrev(List L){
        if(0<getIndex(L) && getIndex(L)<=(length(L)-1)){
          L->cursor = L->cursor->prev;
          L->index--;
        }
        else if(getIndex(L)==0){
          L->cursor = NULL;
          L->index = -1;
        }
        else if(getIndex(L)==-1){
          L->cursor = NULL;
          L->index = -1;
        }
   }

 // If 0<=getIndex()<length()-1, moves the cursor one step toward the
   // back of the list. If getIndex()==length()-1, cursor becomes
   // undefined. If index==-1, cursor remains undefined. This
   // operation is equivalent to moveTo(getIndex()+1).
   //
   void moveNext(List L){
        if(getIndex(L)== length(L)-1 || L->index==-1){
          L->cursor = NULL;
          L->index = -1;
        }
        else if(0<=getIndex(L) && getIndex(L)<(length(L)-1)){
          L->cursor = L->cursor->next;
          L->index++;
        }

   }

   //Inserts new element before front element in this List.
   //
   void prepend(List L, int data){
        Node N = newNode(data);
        if(length(L)==0){
             L->front = N;
             L->back = N;
        }
        else{
             L->front->prev = N;
             N->next = L->front;
             L->front = N;
             N->prev = NULL;

             L->index++;
        }
        L->numItems++;
   }

   // Inserts new element after back element in this List.
   //
   void append(List L, int data){
        Node N = newNode(data);
        if(length(L)==0){
             L->front = N;
             L->back = N;
        }
        else{
             L->back->next = N;
             N->prev = L->back;
             L->back = N;
             N->next = NULL;

        }
        L->numItems++;
   }

  // Inserts new element before cursor element in this
  // List. Pre: length()>0, getIndex()>=0
  //
   void insertBefore(List L, int data){
        Node N = newNode(data);
        if(length(L)==0 && getIndex(L)>=0){
            printf("List Error: Function called on empty list.\n");
            exit(1);
        }
        else if(length(L) == 1 || L->index==0){
            L->front->prev = N;
            N->next = L->front;
            L->front = N;
            N->prev = NULL;

            L->index++;
            L->numItems++;
        }
        else{
            N->next = L->cursor;
            N->prev = L->cursor->prev;
            L->cursor->prev->next = N;
            L->cursor->prev = N;

            L->index++;
            L->numItems++;
        }
   }
// Inserts new element after cursor element in this 
   // List. Pre: length()>0, getIndex()>=0
   //
   void insertAfter(List L, int data){
        Node N = newNode(data);
        if(length(L)==0){
            printf("List Error: Function called on empty list.\n");
            exit(1);
        }
        if(getIndex(L)<0){
            printf("List Error: Cursor is not defined.\n");
            exit(1);
        }
        else if(length(L)==1){
            L->back->next = N;
            N->prev = L->back;
            L->back = N;
            N->next = NULL;

            L->index++;
            L->numItems++;
        }
        else{
            N->prev = L->cursor;
            N->next = L->cursor->next;
            L->cursor->next->prev = N;
            L->cursor->next = N;

            L->index++;
            L->numItems++;
        }
   }

   // Deletes the front element in this List. Pre: length()>0   
   void deleteFront(List L){
        if(length(L) == 0){
            printf("List Error: deleteFront() called on empty list.\n");
            exit(1);
        }
        if(length(L) == 1){
            L->front = NULL;
            L->back = NULL;
            L->numItems = 0;
            L->index = -1;
        }
        else{
            L->front = L->front->next;
            L->front->prev = NULL;

            L->numItems--;
        }
   }

   // Deletes the back element in this List. Pre: length()>0
   //
   void deleteBack(List L){
        if(length(L)==0){
            printf("List Error: deleteBack() called on empty list.\n");
            exit(1);
        }
        if(length(L) ==1){
            L->front = NULL;
            L->back = NULL;
            L->numItems = 0;
            L->index = -1;
        }
        else{
            L->back = L->back->prev;
            L->back->next = NULL;

            L->numItems--;
        }
   }

//  Deletes cursor element in this List. Cursor is undefined after this 
   //  operation. Pre: length()>0, getIndex()>=0
   //
   void delete(List L){
        if(length(L)==0){
            printf("List Error: delete() called on empty list.\n");
        }
        if(getIndex(L)<0){
            printf("List Error: cursor is not defined.\n");
        }
        else if(getIndex(L)==0){
            L->front = L->front->next;
            L->front->prev = NULL;
            L->numItems--;
        }
        else if(getIndex(L) == (length(L)-1)){
            L->back = L->back->prev;
            L->back->next = NULL;
            L->numItems--;
        }
        else if(length(L)==1){
            L->front = NULL;
            L->back = NULL;
            L->cursor = NULL;
            L->numItems = 0;
            L->index = -1;
        }
        else{
            L->cursor->next->prev = L->cursor->prev;
            L->cursor->prev->next = L->cursor->next;
            L->cursor = NULL;
            L->numItems = 0;
            L->index = -1;
        }
   }

   //  Overides Object's toString method. Creates a string 
   //  consisting of a space separated sequence of integers
   //  with front on the left and back on the right.
   //
   void printList(FILE* out, List L){
        Node N;
        if(L==NULL){
          printf("List Error: calling printList() on NULL List reference\n");
          exit(1);
        }
        for(N = L->front; N!=NULL; N=N->next){
            fprintf(out, "%d ", N->data);
        }
   }

   // Returns a new list representing the same integer sequence as this
   // list. 
   List copyList(List L){
        List A = newList();
        Node N = L->front;
        while(N!=NULL){
            append(A,N->data);
            N= N->next;
        }
        return A;
   }
              
