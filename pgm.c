#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "pgm.h"

pgm_error pgm_read_from_file(pgm *p, char *filename) {

    // Lire le fichier filename et écrire son contenu dans la variable p

    FILE *fr = fopen(filename, "r");

    if (fr == NULL) {
        fprintf(stderr, "Can't open output file %s ! (1)\n", filename); // affiche dans le canal d'erreur
        return failure;
    }

    // P5 (File Type)
  
    char fType[3];

    fscanf(fr, "%s", fType);// fscanf permets de scanner ligne par ligne, réutiliser la fonction pour passer à une autre ligne
    if (strcmp(fType, "P5") != 0) { // strcmp compare deux caractères => "P5" avec ceux du header, il n'a pas besoin qu'on lui précise le nombre de caractères à lire
    // différemment de strncmp qui fonctionne de la manière suivante strncmp(tableau de caractères, caractères à lire, nombre de caractères à lire) 
        fclose(fr);
        return failure;
    }
   

    // M et N (Size : Height x Length)
    int32_t pm;
    int32_t pn;
    fscanf(fr, "%d %d", &pn, &pm); // On remarque après avoir executé notre fonction crop, que le premier 512 correspond à la hauteur et le second à la longueur
    if (pm <= 0 || pn <= 0) {
        fclose(fr);
        return failure;
    }
   
    // Max (Pixel Value)
    int32_t pmax;
    fscanf(fr, "%d", &pmax);
    if (pmax <= 0) {
        fclose(fr);
        return failure;
    }
    p -> max = pmax;

    // \n
    fgetc(fr); // on parcourt => '\n' (1 caractère)
    
    // Allocation de la mémoire pour la matrice de l'image
    matrix_alloc(&(p -> pixels), pm, pn);
     
    // Ecriture de l'information du fichier image dans la matrice
    for (int i = 0; i < pm; i++) {
        for (int j = 0; j < pn; j++) {
            matrix_set((p -> pixels), i, j, fgetc(fr)); // fgetc prend les données caractère par caractère
        }  
    }
    
    fclose(fr);

    return success;
}

pgm_error pgm_write_to_file(pgm *p, char *filename) {

    // Ecrire le contenu de l’image p dans le le fichier filename

    FILE *fw = fopen(filename, "w");

    if (fw == NULL) {
        fprintf(stderr, "Can't open output file %s ! (2)\n", filename); // affiche dans le canal d'erreur
        return failure;
    }

    int32_t pm = p -> pixels.m; //
    int32_t pn = p -> pixels.n; // Magie noire
    int32_t pmax = p -> max;    //

    fprintf(fw, "P5\n");
    fprintf(fw, "%d %d\n", pn, pm);
    fprintf(fw, "%d\n", pmax);

    for (int i = 0; i < pm; i++) {
        for (int j = 0; j < pn; j++) {
            fputc(p -> pixels.data[i][j], fw);
        }
    }

    fclose(fw);

    return success;
}

pgm_error pgm_negative(pgm *neg, const pgm *const orig) {

    // Calculer le négatif de l'image orig et la stocker dans neg

    int32_t omax = orig -> max; //
    int32_t om = orig -> pixels.m; //   Magie noire
    int32_t on = orig -> pixels.n; //

    neg -> max = omax;

    matrix_alloc(&(neg -> pixels), om, on);

    for (int i = 0; i < om; i++) {
        for (int j = 0; j < on; j++) {
            neg -> pixels.data[i][j] = omax - 1 - (orig -> pixels.data[i][j]);
        }
    }

    if (orig == neg) {
        printf("ERREUR : L'image orig a pas été modifié !");
        return failure;
    }

    return success;
}

pgm_error pgm_symmetry_hori(pgm *sym, const pgm *const orig) {

    // Calculer la symetrie horizontale de l'image orig et la stocker dans sym

    int32_t omax = orig -> max; //
    int32_t om = orig -> pixels.m; //   Magie noire
    int32_t on = orig -> pixels.n; //

    sym -> max = omax;

    matrix_alloc(&(sym -> pixels), om, on);

    for (int i = 0; i < om; i++) {
        for (int j = 0; j < on; j++) {
            sym -> pixels.data[i][j] = orig -> pixels.data[i][on - 1 - j];
        }
    }

    if (orig == sym) {
        printf("ERREUR : L'image orig a été modifié !");
        return failure;
    }

    return success;
}

pgm_error pgm_symmetry_vert(pgm *sym, const pgm *const orig) {

    // Calculer la symetrie verticale de l'image orig et la stocker dans sym

    int32_t omax = orig -> max; //
    int32_t om = orig -> pixels.m; //   Magie noire
    int32_t on = orig -> pixels.n; //

    sym -> max = omax;

    matrix_alloc(&(sym -> pixels), om, on);

    for (int i = 0; i < om; i++) {
        for (int j = 0; j < on; j++) {
            sym -> pixels.data[i][j] = orig -> pixels.data[om - 1 - i][j];
        }
    }

    if (orig == sym) {
        printf("ERREUR : L'image orig a été modifié !");
        return failure;
    }

    return success;
}

pgm_error pgm_symmetry_cent(pgm *sym, const pgm *const orig) {

    // Calculer la symetrie centrale de l'image orig et la stocker dans sym

    int32_t omax = orig -> max; //
    int32_t om = orig -> pixels.m; //   Magie noire
    int32_t on = orig -> pixels.n; //

    sym -> max = omax;

    matrix_alloc(&(sym -> pixels), om, on);

    for (int i = 0; i < om; i++) {
        for (int j = 0; j < on; j++) {
            sym -> pixels.data[i][j] = orig -> pixels.data[om - 1 - i][on - 1 - j];
        }
    }

    if (orig == sym) {
        printf("ERREUR : L'image orig a été modifié !");
        return failure;
    }

    return success;
}

pgm_error pgm_photomaton(pgm *photomaton, const pgm *const orig) {

    // Calculer l'effet photomaton de l'image orig et le stocker dans photomaton

    int32_t omax = orig -> max; //
    int32_t om = orig -> pixels.m; //   Magie noire
    int32_t on = orig -> pixels.n; //

    photomaton -> max = omax;

    matrix_alloc(&(photomaton -> pixels), om, on);

    int32_t hOm = (om / 2); // Moitie de la valeur horizontale de orig
    int32_t hOn = (on / 2); // Moitie de la valeur verticale de orig
    // Nous permettra d'éviter les nombres à virgules car on précise qu'il est de type "int"

    // Algorithme à mettre en place :
    // 0  1  2  3    4  5  6  7     =>     On coupe en deux, on prend la moitié du nombre de cases totale pour chaque bloc, on met les nombres pairs bloc gauche,
    // 0  2  4  6  | 1  3  5  7            et impairs bloc droite, pour cela on fait ici 4 * (i % 2), pour savoir dans quel bloc la valeur ira,
    // [] [] [] [] | [] [] [] []           soit 4 * 0 = pair, soir 4 * 1 = impair, puis on ajoute (i / 2) pour savoir de combien avancer dans le bloc
    for (int i = 0; i < om; i++) { //      par exemple : 4 * (3 % 2) + (int : | 3 / 2 = 1.5 | -> 1) => 4 * (1) + (1) = 5, position 5 sur la première ligne
        for (int j = 0; j < on; j++) {
            photomaton -> pixels.data[(hOm * (i % 2)) + (i / 2)][(hOn * (j % 2)) + (j / 2)] = orig -> pixels.data[i][j];
        }
    }

    if (orig == photomaton) {
        printf("ERREUR : L'image orig a été modifié !");
        return failure;
    }

    return success;
}

pgm_error pgm_crop(pgm *crop, const pgm *const orig, int32_t x0, int32_t x1, int32_t y0, int32_t y1) {

    // Calculer la sous-image de orig aux coordonnées x0 à x1 (non-inclu), et y0 à y1 (non-inclu), puis stocker le résultat dans crop.

    crop -> max = orig -> max;

    matrix_extract_submatrix(&(crop -> pixels), orig -> pixels, x0, x1, y0, y1);

    return success;
}

pgm_error pgm_conv(pgm *conv, const pgm *const orig, const matrix *const kernel, double norm) {
    
    // Calculer la convolution entre orig et le noyau kernel ainsi que sa normalisation norm, puis stocker le résultat dans conv.

    int32_t omax = orig -> max;
    int32_t om = orig -> pixels.m;
    int32_t on = orig -> pixels.n;

    int32_t km = kernel -> m;
    int32_t kn = kernel -> n;
    
    conv -> max = omax;

    matrix_alloc(&(conv -> pixels), om, on);

    for (int32_t i = 0; i < om; i++) {
        for (int32_t j = 0; j < on; j++) {

            int sum = 0;

            int32_t kmHalf = km / 2; // Moitier de la longueur du kernel en int pour retourner sa partie entiere
            int32_t knHalf = kn / 2; // Moitier de la hauteur du kernel en int pour retourner sa partie entiere

            for (int x = -kmHalf; x <= kmHalf; x++) {
                for (int y = -knHalf; y <= knHalf; y++) {

                    if (i + x >= 0 && i + x < om && j + y >= 0 && j + y < on) {
                        sum += (kernel -> data[x + kmHalf][y + knHalf]) * (orig -> pixels.data[i + x][j + y]);
                    }
                }
            }

            int pixelValue = (int)((double)sum / norm);

            if (pixelValue < 0) {
                pixelValue = 0;
            }

            if (pixelValue > omax - 1) {
                pixelValue = omax - 1;
            }

            conv -> pixels.data[i][j] = pixelValue;
        }
    }

    if (orig == conv) {
        printf("ERREUR : L'image orig a été modifié !");
        return failure;
    }

    return success;
}

