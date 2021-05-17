
#ifndef PGM_H
#define PGM_H



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include "matrix.h"

typedef enum _pgm_error {
    success, failure
} pgm_error;

typedef struct _pgm {
    int32_t max; // valeur maximale que peut prendre un pixel donc la valeur du niveau de gris maximale que l'on peut obtenir (coder sur un octet donc de 0 à 255)
    matrix pixels; // 512(longueur) * 512(hauteur) = Nombre de pixel total = 262144
} pgm;

pgm_error pgm_read_from_file(pgm *p, char *filename);
pgm_error pgm_write_to_file(pgm *p, char *filename);
pgm_error pgm_negative(pgm *neg, const pgm *const orig);
pgm_error pgm_symmetry_hori(pgm *sym, const pgm *const orig);
pgm_error pgm_symmetry_vert(pgm *sym, const pgm *const orig);
pgm_error pgm_symmetry_cent(pgm *sym, const pgm *const orig);
pgm_error pgm_photomaton(pgm *photomaton, const pgm *const orig);
pgm_error pgm_crop(pgm *crop, const pgm *const orig, int32_t x0, int32_t x1, int32_t y0, int32_t y1);
pgm_error pgm_conv(pgm *conv, const pgm *const orig, const matrix *const kernel, double norm);

#endif