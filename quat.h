
#include<stdbool.h>
#include"matrix.h"
#include"pgm.h"

#define CHILDREN 4

typedef struct _node {
    int info ;
     double ave;    //moyenne
     double ave_2;  //moyenne des carrés
     struct _node* child[4];
     } node;


bool is_leaf(node* nd) ;
node* tree_create(int depth);
int max(int x,int y) ;
int array_max(int size,int tab[]) ;
int depth(node* a) ;
void print(node* arbre,int decal,char* sep);
void swap(void** ptr1,void** ptr2) ;
void sum(node* arbre);
int idx_from_d_bit(int m, int n, int d);
node* position(int li,int col,node* a,int d) ;
void matrix2tree(matrix * mat,node* arbre) ;
void trre2matrix(matrix * mat,node* arbre);
void symetrie_v (node *arbre ) ; 
void symetrie_H (node *arbre ) ; 
void symetrie_C (node *arbre ) ; 
void arbre_destroy(node *arbre , int d  ) ;
long long convert(int n);
int indice_bit(int n, int m, int d);



