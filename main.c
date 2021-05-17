#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include "pgm.h"
#include "quat.h"
#include "matrix.h"

int main() {
  pgm *p = malloc(sizeof(pgm)) ;
  pgm_read_from_file(p,"mandrill.pgm") ;
  
  pgm_write_to_file(p,"mandrill.pgm");
  printf ("tt") ;
 
 node *tree = tree_create(9); // on a 9 profondeur  2{}
 
 matrix2tree(&p -> pixels , tree)  ;
   print(tree , 5 , "");
   
   matrix_destroy(&p->pixels);
  arbre_destroy(tree , 9) ;
  free(p);
  
   
   
  



  
   return 0;
}