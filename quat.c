#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include "matrix.h"
#include "quat.h"




bool is_leaf(node* nd) {
   
   return (NULL == nd->child[0]); 
}

node* tree_create(int depth) {
  
   node* a = calloc(1,sizeof(node));
   if (depth > 0) {
      for (int i=0;i<CHILDREN;i++) {
         a->child[i] = tree_create(depth-1);
         
      }
   }
   
   return a;
}

void arbre_destroy(node *arbre , int d  ) {
 
   if (d > 0)
    {        
        for (int i = 0; i < CHILDREN; i++)
        {
            
            arbre_destroy(arbre->child[i], d - 1);
        }
        free(arbre);
    }
}

int max(int x,int y) {

   return  (x >= y ? x : y);
}

int array_max(int size,int tab[size]) {
   
   int m = INT_MIN;
   for (int i=0;i<size;i++) {
      m = max(m,tab[i]);
   }
  
   return m;
}

int depth(node* a) {
    
   int p[CHILDREN] ;
  
   
    if (is_leaf(a)) {
       
        return 0;
    } else {
        for (int i = 0; i < CHILDREN; i++) {
            p[i] = 1 + depth(a->child[i]);
            
        }
        
         return array_max(CHILDREN,p);
         printf("e");
     
           
        }
   
   
}


void print(node* arbre,int decal,char* sep) {
  printf("adfadsad");
   if (NULL != arbre) {
      for (int i=0;i<decal;i++) { 
         printf("%s",sep);
      }
      printf("%f\n",arbre->ave);
      decal++;
      if (!is_leaf(arbre)) {
         for (int i=0;i<CHILDREN;i++) {
            print(arbre->child[i],decal,sep);
         }
      }
   } 
}

// Fonction utile pour les symétries
void swap(void** ptr1,void** ptr2) {
   
   void* tmp = *ptr1;
   *ptr1 = *ptr2;
   *ptr2 = tmp;
}

void sum(node* arbre) {
   if (!is_leaf(arbre)) {
      for (int i=0;i<CHILDREN;i++) {
         
         sum(arbre->child[i]);
         
      }
      for (int i=0;i<CHILDREN;i++) {
         arbre->ave += arbre->child[i]->ave;
      }
   }
}
/*Enter a decimal number: 19
Step 1: 19/2, Remainder = 1, Quotient = 9
Step 2: 9/2, Remainder = 1, Quotient = 4
Step 3: 4/2, Remainder = 0, Quotient = 2
Step 4: 2/2, Remainder = 0, Quotient = 1
Step 5: 1/2, Remainder = 1, Quotient = 0
19 in decimal = 10011 in binary*/

long long convert(int n) {
    long long bin = 0;
    int rem, i = 1, step = 1;
    while (n != 0) {
        rem = n % 2;
        n /= 2;
        bin += rem * i;
        i *= 10;
    }
    return bin;
}

int indice_bit(int n, int m, int d) {
    int n_bit = (convert(n)>> d) & 1;
    int m_bit = (convert(m)>> d) & 1;
    return (n_bit << 1)  | m_bit;
}



node* position(int m,int n,node* a,int d) {
  
   m = m ;
   n = n ;
   node* crt = a;
   
   do {
      int index =  indice_bit(n,m,d);//choisir le sous-cadran de <li> et <co>
     
      crt = crt->child[index]; // descendre tt que c pas un noeud terminal
      d--;
       
     

   } while (!is_leaf(crt)); // crt devien un noeud terminal
   return crt;
}

void matrix2tree(matrix * mat,node* arbre) {
   int d = depth(arbre)-1;
   
   for (int32_t li=0; li < mat->m; li++) {
      for (int32_t co=0; co < mat->n ; co++) {
         node* crt = position(li,co,arbre,d); // la position des pixels qui se trouve dans les noeud terminal
         crt->ave = mat->data[li][co];
         crt -> ave_2 = mat->data[li][co] * mat->data[li][co];
      }
   }   
}

void trre2matrix(matrix * mat,node* arbre) {
   int d = depth(arbre)-1;
   
   for (int32_t li=0; li < mat->m; li++) {
      for (int32_t co=0; co < mat->n ; co++) {
         node* crt = position(li,co,arbre,d); // la position des pixels qui se trouve dans les noeud terminal
         mat->data[li][co] = crt->ave ;
         
      }
   }   
}

void symetrie_v (node *arbre ) {
   if (!is_leaf(arbre)){
      swap(&(arbre->child[0] ) , &(arbre->child[1])); 
      swap(&(arbre->child[2] ) , &(arbre->child[4])); 
      for (int i = 0; i < CHILDREN ; i++)
      {
         symetrie_v(arbre->child[i]) ;
      }
      
      
   }
}















